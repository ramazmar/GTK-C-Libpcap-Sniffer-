//proc_ethernet.c
//---------------
 
#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/if_ether.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include "misc.h"
#include "proc_ethernet.h"
#include <stdlib.h>
#include "win_error.h"
#include "win_ini.h"
#include "proc_frame.h"
#include "proc_ip.h"
#include "proc_arp.h"

//Prototipos estaticos
static void get_proto(guint16 type,char **str_pp);

//Devuelve una cadena con el protocolo correspondiente al codigo que se le pasa.
//Parametros:
//	type:Entero con el codigo del protocolo que se esta usando.
//	str_pp:Puntero a puntero donde se almacenara la cadena del protocolo.
void get_proto(guint16 type,char **str_pp)
{
    
    if((*str_pp=(char *)malloc(40))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };
    
    switch(type){
	case ETHERTYPE_IP:
	    sprintf(*str_pp,"IP");	
	    break;
	case ETHERTYPE_ARP:
	    sprintf(*str_pp,"ARP");
	    break;
	case ETHERTYPE_REVARP:
	    sprintf(*str_pp,"RARP");
	    break;
	case ETHERTYPE_PUP:
	    sprintf(*str_pp,"Xerox PUP");
	    break;
	default:
	    sprintf(*str_pp,"Desconocido");
	    break;
    }

}

//Handler para tramas ethernet.
//Funcion que actualiza los datos relacionados con el protocolo Ethernet
//   de una trama determinada..
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio de la trama Ethernet.(para saltar los
//		datos de los protocolos anteriores).
void ether_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset)
{    
    GtkWidget *treeitem,*subtree;
    struct ether_header *eptr;
    GString *gcadena;    
    gchar *src_addr,*dest_addr,truncated=0;
    guint16 proto_type;
    gchar *type_str,*data_ptr;
    gint maxdata;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    //Se averigua si la trama está truncada.
    if (pkt_hdr->caplen>=sizeof(struct ether_header)){
	truncated=0;
    }else truncated=1;
    
    //Se apunta con eptr a donde empieza la trama ethernet.
    eptr=(struct ether_header *)pkt;//No será necesario usar el offset ya que es siempre cero.
    
    //Se inserta en el arbol/lista lo que se va a insertar independientemente de que este truncado o no...
    if (mode==2){
	//Si es el modo 2, se insertan datos en el arbol de ethernet frame.
    	sprintf(str_buf_run,"Ethernet II");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_set_text(pos,3,"Ethernet II");
	
    }
    
    if (truncated){ 
	//Si está truncado se actualiza solo el arbol y se sale.
	if(mode==2){
	    sprintf(str_buf_run,"Trama cortada.");	
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);	
	}
	return;
    }

    //Se averiguan los datos comunes a los dos modes.
    gcadena=g_string_new(ether_ntoa(eptr->ether_shost));
    src_addr=gcadena->str;

    gcadena=g_string_new(ether_ntoa(eptr->ether_dhost));
    dest_addr=gcadena->str;    
	
    proto_type=ntohs(eptr->ether_type);

    get_proto(proto_type,&type_str);
    
    //Se mira si la trama ethernet es del tipo deseado(solo se trataran tramas EthernetII)
    if (proto_type<=1500){
	//Todos los protocolos que encapsula estan definidos por encima de
	//1500 por lo que si es menor será que es otro tipo de trama ethernet de las posibles que hay...
	if (mode==2){
	    sprintf(str_buf_run,"Trama ethernet no valida.");	
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	}
	
	return;
    }	
    
    if (mode==2){
	//Se insertan datos en el arbol.
    	//Se añade la direccion origen
    	sprintf(str_buf_run,"Direccion de origen:%s",src_addr);	
    	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);	
	//Se añade la direccion de destino
	sprintf(str_buf_run,"Direccion de destino:%s",dest_addr);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Tamaño de cabecera:%d bytes",sizeof(struct ether_header));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Tamaño de datos:%d bytes",((int)pkt_hdr->len - sizeof(struct ether_header)));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
		
	sprintf(str_buf_run,"Protocolo encapsulado:%s",type_str);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	//free(type_str);
	
	//Se insertan datos posteriores a la trama.
	if ( pkt_hdr->caplen > (offset+sizeof(struct ether_header))){
	    data_ptr=(char *)(pkt+sizeof(struct ether_header));
	    maxdata=pkt_hdr->caplen-(offset+sizeof(struct ether_header));
	    data_tree(subtree,data_ptr,maxdata);
	}
		
    }else{
        //Se actualiza la lista de tramas capturados con la direcciones ethernet.
        winini_clist_set_text(pos,1,src_addr);
        winini_clist_set_text(pos,2,dest_addr);
    }
    
    
    //Aqui dependiendo del protocolo que encapsula se llamara al handler correspondiente.
    offset=sizeof(struct ether_header);
    switch(proto_type){
        case ETHERTYPE_IP:
	    ip_handler(pos,pkt_hdr,pkt,mode,offset);
	    break;
        case ETHERTYPE_ARP:
	    arp_handler(pos,pkt_hdr,pkt,mode,offset);
	    break;
        case ETHERTYPE_REVARP:
	    arp_handler(pos, pkt_hdr, pkt,mode,offset);
	    break;
    }
}


