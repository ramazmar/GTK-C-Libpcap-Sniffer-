//proc_tcp.c 
//----------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "proc_tcp.h"
#include "win_options.h"
#include "proc_frame.h"
#include "win_ini.h"
#include "win_error.h"

//Prototipos estaticos
static guint16 get_tcp_offset(const struct tcp_header *tcp_ptr);
static char get_urg_flag(const struct tcp_header *tcp_ptr);
static char get_ack_flag(const struct tcp_header *tcp_ptr);
static void get_tcp_flags(const struct tcp_header *tcp_ptr,char **str_pp);


//Devuelve el offset en bytes (el offset es el header len)
//Parametros:
//    	tcp_ptr:Puntero a la estructura de la cabecera del paquete TCP.
//	Devuelve:El offset
guint16 get_tcp_offset(const struct tcp_header *tcp_ptr)
{
    //Se multiplica por 4 para devulverlo en bytes.
    return( ((tcp_ptr->offset_reser & TCP_OFFSET_MASK) >> 4)*4);
}

//Funcion para saber el valor de la bandera URG.
//Parametros:
//	tcp_ptr:Puntero a la estructura de la cabecera del paquete TCP.
//	Devuelve: 1 si la bandera esta activa, 0 si no.
//Las banderas URG y ACK se usaran de manera especial para añadir o no nuevos campos
//al arbol.
char get_urg_flag(const struct tcp_header *tcp_ptr)
{    
    if ((tcp_ptr->reser_flags & TCP_FLAG_URG_MASK) != 0) return 1;
    else return 0;
}
//Funcion para saber el valor de la bandera ACK.
//Parametros:
//	tcp_ptr:Puntero a la estructura de la cabecera del paquete TCP.
//	Devuelve: 1 si la bandera esta activa, 0 si no.
char get_ack_flag(const struct tcp_header *tcp_ptr)
{    
    if ((tcp_ptr->reser_flags & TCP_FLAG_ACK_MASK) != 0) return 1;
    else return 0;
}

//Funcion que devuelve una cadena de texto con el valor de todas las banderas de
//  la cabecera IP.
//Parametros:
//	tcp_ptr:Puntero a la estructura de la cabecera del paquete TCP.
//	str_pp:Puntero a puntero donde se almacenara la cadena con el valor de
//		todas las banderas.
void get_tcp_flags(const struct tcp_header *tcp_ptr,char **str_pp)
{

    if((*str_pp=(char *)malloc(50))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };
    
    if ((tcp_ptr->reser_flags & TCP_FLAG_URG_MASK) != 0) strcpy(*str_pp,"URG:1 ");
    else strcpy(*str_pp,"URG:0 ");
    
    if ((tcp_ptr->reser_flags & TCP_FLAG_ACK_MASK) != 0) strcat(*str_pp,"ACK:1 ");
    else strcat(*str_pp,"ACK:0 ");

    if ((tcp_ptr->reser_flags & TCP_FLAG_PSH_MASK) != 0) strcat(*str_pp,"PSH:1 ");
    else strcat(*str_pp,"PSH:0 ");
    
    if ((tcp_ptr->reser_flags & TCP_FLAG_RST_MASK) != 0) strcat(*str_pp,"RST:1 ");
    else strcat(*str_pp,"RST:0 ");

    if ((tcp_ptr->reser_flags & TCP_FLAG_SYN_MASK) != 0) strcat(*str_pp,"SYN:1 ");
    else strcat(*str_pp,"SYN:0 ");
    
    if ((tcp_ptr->reser_flags & TCP_FLAG_FIN_MASK) != 0) strcat(*str_pp,"FIN:1 ");
    else strcat(*str_pp,"FIN:0 ");

}


//Funcion que actualiza los datos relacionados con el protocolo TCP
//   de una trama determinada..
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio del paquete TCP.(para saltar los
//		datos de los protocolos anteriores).
void tcp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset)
{
    GtkWidget *treeitem,*subtree;
    struct tcp_header *tcp_ptr;
    gchar *data_ptr,*temporal,truncated=0;
    gint maxdata,header_len;
    guint16 src_port,dest_port;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    //Se mira si está truncado.    
    if (pkt_hdr->caplen< (offset+sizeof(struct tcp_header)) ){
	truncated=1;
    }else{
	truncated=0;
	tcp_ptr=(struct tcp_header *)(pkt+offset);
    };
    
    
    //Se inserta lo que es independientemente de que este truncado o no
    if (mode==2){
	//Si es el modo 2, se inserta el arbol.
    	sprintf(str_buf_run,"TCP");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_get_text(pos,3,&temporal);
	sprintf(str_buf_run,"%s / TCP",temporal);
	winini_clist_set_text(pos,3,str_buf_run);
	//free(temporal);
    }
    
    if (truncated){ 
	//Si está truncado se informa y se sale
	if(mode==2){
	    sprintf(str_buf_run,"Paquete truncado.");	
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);	
	}
	return;
    }
    
    //Datos relevantes a los dos modes.
    src_port=ntohs(tcp_ptr->src_port);
    dest_port=ntohs(tcp_ptr->dest_port);
    
    if (mode==2){
		//Se inserta el arbol.
        	sprintf(str_buf_run,"Puerto origen:%u",src_port);	
        	treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);	

		sprintf(str_buf_run,"Puerto destino:%u",dest_port);
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		sprintf(str_buf_run,"Numero de sequecia: %u",ntohl(tcp_ptr->seq_num));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		if (get_ack_flag(tcp_ptr)==1){
		    sprintf(str_buf_run,"Numero ACK: %u",ntohl(tcp_ptr->ack_num));
		    treeitem=gtk_tree_item_new_with_label(str_buf_run);
		    gtk_tree_append(GTK_TREE(subtree),treeitem);
		    gtk_widget_show(treeitem);
		}
		
		header_len=get_tcp_offset(tcp_ptr);
		sprintf(str_buf_run,"Offset: %u bytes",header_len);
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		get_tcp_flags(tcp_ptr,&temporal);
		sprintf(str_buf_run,"Flags: %s",temporal);
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		//free(temporal);
		
		sprintf(str_buf_run,"Tamaño de ventana: %u bytes",ntohs(tcp_ptr->window));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		sprintf(str_buf_run,"Checksum: 0x%x",ntohs(tcp_ptr->checksum));		
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		if (get_urg_flag(tcp_ptr)==1){
		    sprintf(str_buf_run,"Puntero URG: %u",ntohs(tcp_ptr->urg_ptr));
		    treeitem=gtk_tree_item_new_with_label(str_buf_run);
		    gtk_tree_append(GTK_TREE(subtree),treeitem);
		    gtk_widget_show(treeitem);		
		}
		
		//Datos
		if ( pkt_hdr->caplen > (offset+header_len) ){
		    data_ptr=(char *)(pkt+offset+header_len);		    
		    maxdata=pkt_hdr->caplen-(offset+header_len);
		    data_tree(subtree,data_ptr,maxdata);
		}
		//Fin de datos.
		
	}else{
	    //Si esta la opcion avanzada requerida, se actualiza la lista de 
	    // paquetes capturados con los numeros de puertos.
	    if (winoptions_option_tcp()){
	        winini_clist_get_text(pos,1,&temporal);
		sprintf(str_buf_run,"%s(%u)",temporal,src_port);
		winini_clist_set_text(pos,1,str_buf_run);
		//free(temporal);

		winini_clist_get_text(pos,2,&temporal);
		sprintf(str_buf_run,"%s(%u)",temporal,dest_port);
		winini_clist_set_text(pos,2,str_buf_run);
		//free(temporal);
	    }
	}

    offset+=sizeof(struct tcp_header);
}


