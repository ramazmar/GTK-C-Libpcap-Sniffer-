//proc_udp.c 
//----------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include "misc.h"
#include "proc_udp.h"
#include "win_ini.h"
#include "win_options.h"
#include "proc_frame.h"

//Funcion que actualiza los datos relacionados con el protocolo UDP
//   de una trama determinada..
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio del paquete UDP.(para saltar los
//		datos de los protocolos anteriores).
void udp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset)
{
    GtkWidget *treeitem,*subtree;
    struct udp_header *udp_ptr;
    gchar *data_ptr,*temporal,truncated=0;
    gint maxdata;
    guint16 src_port,dest_port;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    //Se mira si está truncado.    
    if (pkt_hdr->caplen< (offset+sizeof(struct udp_header)) ){
	truncated=1;
    }else{
	truncated=0;
	udp_ptr=(struct udp_header *)(pkt+offset);
    };
    
    
    //Se inserta lo que es independientemente de que este truncado o no
    if (mode==2){
    	sprintf(str_buf_run,"UDP");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_get_text(pos,3,&temporal);
	sprintf(str_buf_run,"%s / UDP",temporal);
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
    src_port=ntohs(udp_ptr->src_port);
    dest_port=ntohs(udp_ptr->dest_port);
    
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
		
		sprintf(str_buf_run,"Tamaño: %u bytes",ntohs(udp_ptr->length));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);		
		
		sprintf(str_buf_run,"Checksum: 0x%x",ntohs(udp_ptr->checksum));		
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
		
		//Datos
		if ( pkt_hdr->caplen > (offset+sizeof(struct udp_header)) ){
		    data_ptr=(char *)(pkt+offset+sizeof(struct udp_header));
		    maxdata=pkt_hdr->caplen-(offset+sizeof(struct udp_header));
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

    offset+=sizeof(struct udp_header);
}



