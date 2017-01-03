//proc_arp.c
//----------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "misc.h"
#include "proc_arp.h"
#include "win_error.h"
#include "win_ini.h"
#include "proc_frame.h"

//Prototipos estaticos
static void get_proto_type(guint16 type, char **str_pp);
static void get_operation(guint16 op,char **str_pp);

//Devuelve una cadena con el protocolo correspondiente al codigo que se le pasa.
//Parametros:
//	type:Entero con el codigo del protocolo que se esta usando.
//	str_pp:Puntero a puntero donde se almacenara la cadena del protocolo.
void get_proto_type(guint16 type, char **str_pp)
{
    if((*str_pp=(char *)malloc(40))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit(-1);
    };

    switch(type){

	case XEROX_PUP:
	    sprintf(*str_pp,"XEROX PUP");
	    break;
	case XEROX_NS_IDP:
	    sprintf(*str_pp,"XEROX NS IDP");
	    break;
	case INTERNET_PROTO:
	    sprintf(*str_pp,"IP");
	    break;
	case X_75:
	    sprintf(*str_pp,"X 75");
	    break;
	default:
	    sprintf(*str_pp,"Desconocido");
	    break;
    }
    
}


//Devuelve una cadena con la operacion correspondiente al codigo que se le pasa.
//Parametros:
//	op:Entero identificador de la operacion que se esta usando.
//	str_pp:Puntero a puntero donde se almacenara la cadena de codigo.
void get_operation(guint16 op,char **str_pp)
{

    if((*str_pp=(char *)malloc(40))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    }
    
    switch(op){
	case REQUEST:
	    sprintf(*str_pp,"ARP Peticion");
	    break;
	case REPLY:
	    sprintf(*str_pp,"ARP Respuesta");
	    break;
	case REV_REQUEST:
	    sprintf(*str_pp,"RARP Peticion");
	    break;
	case REV_REPLY:
	    sprintf(*str_pp,"RARP Respuesta");
	    break;
	case InREQUEST:
	    sprintf(*str_pp,"InARP Peticion");
	    break;
	case InREPLY:
	    sprintf(*str_pp,"InARP Respuesta");
	    break;
	case NAK:
	    sprintf(*str_pp,"(ATM)ARP NAK");
	    break;
	default:	
	    sprintf(*str_pp,"Desconocido");
	    break;
    }

}


//Funcion que actualiza los datos relacionados con el protocolo ARP
//   de una trama determinada..
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio de la trama ARP.(para saltar los
//		datos de los protocolos anteriores).

void arp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset)
{    
    GtkWidget *treeitem,*subtree;
    struct arp_header *arp_ptr;
    struct in_addr src_ip,dest_ip;
    guint16 operation,proto_type;
    gchar *operation_str,*type_str,*temporal,*data_ptr,truncated=0;
    gint maxdata;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;

    //Se averigua si la cabecera esta truncada.
    if (pkt_hdr->caplen < (sizeof(struct arp_header)+offset))	truncated=1;

    //Se apunta a la cabecera de la trama ARP saltando la de la ethernet.
    arp_ptr=(struct arp_header *)(pkt+offset);
    
    //Se inserta lo que es independiente de si esta truncado o no.
    if (mode==2){
        sprintf(str_buf_run,"ARP");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_get_text(pos,3,&temporal);
	sprintf(str_buf_run,"%s / ARP",temporal);
	winini_clist_set_text(pos,3,str_buf_run);	
	//free(temporal);
    }
    
    if (truncated){
	if(mode==2){
	    sprintf(str_buf_run,"Paquete truncado.");
    	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	}
	return;
    }
        
    //Se obtiene la informacion común a los 2 modos.        
    src_ip.s_addr=*((bpf_u_int32 *)arp_ptr->arp_spa);
    dest_ip.s_addr=*((bpf_u_int32 *)arp_ptr->arp_tpa);


    operation=ntohs(arp_ptr->op);
    get_operation(operation,&operation_str);
	
    proto_type=ntohs(arp_ptr->proto_type);

    get_proto_type(proto_type,&type_str);

    
    if (mode==2){

	    sprintf(str_buf_run,"Tipo de operacion: %s",operation_str);
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	    
	    sprintf(str_buf_run,"Direccion MAC origen: %s",ether_ntoa(arp_ptr->arp_sha));
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	    
	    sprintf(str_buf_run,"Direccion MAC destino: %s",ether_ntoa(arp_ptr->arp_tha));
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	    
	    sprintf(str_buf_run,"Protocolo de direcciones usado: %s",type_str);
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);

	    if (proto_type==INTERNET_PROTO){
	        sprintf(str_buf_run,"Direccion IP origen: %s",inet_ntoa(src_ip));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		if ((operation==REQUEST) || (
		operation==REV_REQUEST) || (operation==InREQUEST)){
		    sprintf(str_buf_run,"Direccion IP buscada: %s",inet_ntoa(dest_ip));
		}else{
		    sprintf(str_buf_run,"Direccion IP de respuesta: %s",inet_ntoa(dest_ip));
		}
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
	    }
	    
	    //Se añaden los datos.
	    if ( pkt_hdr->caplen > (offset+sizeof(struct arp_header)) ){
		data_ptr=(char *)(pkt+offset+sizeof(struct arp_header));
		maxdata=pkt_hdr->caplen-(offset+sizeof(struct arp_header));
		data_tree(subtree,data_ptr,maxdata);
	    }
    }

    offset=offset+sizeof(struct arp_header);
    //ARP no encapsula a nada mas
}


