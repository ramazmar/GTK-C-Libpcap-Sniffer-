//proc_icmp.c
//-----------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "misc.h"
#include "proc_icmp.h"
#include "win_error.h"
#include "win_ini.h"
#include "proc_frame.h"

//Prototipos estaticos
static void get_icmp_type(guint8 type,char **str_pp);
static void get_icmp_code(guint8 type,guint code,char **str_pp);

//Devuelve una cadena con el tipo de mensage ICMP correspondiente al codigo
//  que se le pasa.
//Parametros:
//	type:Entero con el codigo del tipo.
//	str_pp:Puntero a puntero donde se almacenara la cadena del tipo.
void get_icmp_type(guint8 type,char **str_pp)
{
        
    if((*str_pp=(char *)malloc(100))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };
    
    switch(type){
	case ICMP_TYP_ECHO_REPLY:
	    sprintf(*str_pp,"Echo respuesta(ping)");
	    break;
	case ICMP_TYP_DEST_UNREA:
	    sprintf(*str_pp,"Destinatario no encontrado");
	    break;
	case ICMP_TYP_SOURCE_QUENCH:
	    sprintf(*str_pp,"Router sin espacio en cola para encolar datagrama.");
	    break;
	case ICMP_TYP_REDIRECT:
	    sprintf(*str_pp,"Redireccion");
	    break;
	case ICMP_TYP_ALT_HOST_ADDR:
	    sprintf(*str_pp,"Alternate host address");
	    break;
	case ICMP_TYP_ECHO:
	    sprintf(*str_pp,"Echo (ping)");
	    break;    
	case ICMP_TYP_ROUTER_ADVIRT:
	    sprintf(*str_pp,"Router advertisement");
	    break;
	case ICMP_TYP_ROUTER_SELECT:
	    sprintf(*str_pp,"Router selection");
	    break;
	case ICMP_TYP_TIMEOUT:
	    sprintf(*str_pp,"Time exceeded.");
	    break;
	case ICMP_TYP_PARAMET_PROB:
	    sprintf(*str_pp,"Problemas de parametro.");
	    break;
	case ICMP_TYP_TIMESTAMP:
	    sprintf(*str_pp,"Timestamp");
	    break;
	case ICMP_TYP_TIMESTAMP_REPLY:
	    sprintf(*str_pp,"Timestamp reply");
	    break;
	case ICMP_TYP_INFOR_REQUEST:
	    sprintf(*str_pp,"Information request");
	    break;
	case ICMP_TYP_INFOR_REPLY:
	    sprintf(*str_pp,"Information reply");
	    break;
	case ICMP_TYP_ADDR_MASK_REQUEST:
	    sprintf(*str_pp,"Address mask request");
	    break;
	case ICMP_TYP_ADDR_MASK_REPLY:
	    sprintf(*str_pp,"Address mask reply");
	    break;
	case ICMP_TYP_TRACEROUTE:
	    sprintf(*str_pp,"Traceroute");
	    break;
	case ICMP_TYP_DATAG_CONV_ERROR:
	    sprintf(*str_pp,"Datagram conversion error");
	    break;
	case ICMP_TYP_MOBILE_HOST_REDI:
	    sprintf(*str_pp,"Mobile host redirect");
	    break;
	case ICMP_TYP_IPV6_WHERE:
	    sprintf(*str_pp,"IPv6 where-are-you");
	    break;
	case ICMP_TYP_IPV6_IMHERE:
	    sprintf(*str_pp,"IPv6 I-am-here");
	    break;
	default:
	    sprintf(*str_pp,"Desconocido.");
	    break;
    }
}

//Devuelve una cadena con el codigo de error correspondiente al codigo que se le pasa.
//Parametros:
//	type:Entero con el codigo del codigo de error.
//	str_pp:Puntero a puntero donde se almacenara la cadena del codigo de error.
void get_icmp_code(guint8 type,guint code,char **str_pp)
{
    
    if((*str_pp=(char *)malloc(100))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };
    
    switch(type){
	case ICMP_TYP_DEST_UNREA:
	    switch(code){
		case 0:
		    sprintf(*str_pp,"Red inalcanzable");
		case 1:
		    sprintf(*str_pp,"Host inalcanzable");
		    break;
		case 2:
		    sprintf(*str_pp,"Protocolo inalcanzable");
		    break;
		case 3:
		    sprintf(*str_pp,"Puerto inalcanzable");
		    break;
		case 4:
		    sprintf(*str_pp,"Necesaria fragmentacion pero prohibida.");
		    break;
		case 5:
		    sprintf(*str_pp,"Fallo en ruter de origen");
		    break;
		case 6:
		    sprintf(*str_pp,"Red destinataria desconocida");
		    break;
		case 7:
		    sprintf(*str_pp,"Host destinatario desconocido");
		    break;
		case 8:
		    sprintf(*str_pp,"Host origen aislado");
		    break;
		case 9:
		    sprintf(*str_pp,"Red destinataria prohibida administrativamente");
		    break;
		case 10:
		    sprintf(*str_pp,"Host destinatario prohibido administrativamente");
		    break;
		case 11:
		    sprintf(*str_pp,"Red inalcanzable para este tipo de servicio");
		    break;
		case 12:
		    sprintf(*str_pp,"Host inalcanzable para este tipo de servicio");
		    break;
		case 13:
		    sprintf(*str_pp,"Comunicacion prohibida administrativamente por filtros");
		    break;
		case 14:
		    sprintf(*str_pp,"Prioridad de host violada");
		    break;
		case 15:
		    sprintf(*str_pp,"Atajo de prioridad en vigor.");
		    break;
		default:
		    sprintf(*str_pp,"Desconocido");
		    break;
	    }
	    break;

	case ICMP_TYP_REDIRECT:
	    switch(code){
		case 0:
		    sprintf(*str_pp,"Redireccion de red");
		    break;
		case 1:
		    sprintf(*str_pp,"Redireccion de host");
		    break;   
		case 2:
		    sprintf(*str_pp,"Redireccino de red para este tipo de servicio");
		    break;
		case 3:
		    sprintf(*str_pp,"Redireccion de host para este tipo de servicio");
		    break;
		default:
		    sprintf(*str_pp,"Desconocido");
		    break;
	    }
	    break;

	case ICMP_TYP_TIMEOUT:
	    switch(code){
		case 0:
		    sprintf(*str_pp,"TTL exceeded en el transito");
		    break;
		case 1:
		    sprintf(*str_pp,"TTL excedido en el reensamblaje");
		    break;
		default:
		    sprintf(*str_pp,"Desconocido");
		    break;
	    }
	    break;

	case ICMP_TYP_PARAMET_PROB:
	    switch(code){
		case 0:
		    sprintf(*str_pp,"El puntero indica el error");
		    break;
		case 1:
		    sprintf(*str_pp,"Fallo en una opcion requerida");
		    break;
		case 2:
		    sprintf(*str_pp,"Tamaño erroneo");
		    break;
		default:
		    sprintf(*str_pp,"Desconocido");
	    }
	    break;

	default:
	    sprintf(*str_pp,"Sin uso");
	    break;
    }
}

//Funcion que actualiza los datos relacionados con el protocolo ICMP
//   de una trama determinada..
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio de los datos ICMP.(para saltar los
//		datos de los protocolos anteriores).
void icmp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset)
{    
    GtkWidget *treeitem,*subtree;
    struct icmp_header *icmp_ptr;
    struct icmp_echo_header *echo_ptr;
    struct icmp_redirect_header *redirect_ptr; 
    struct in_addr temp_addr;
    gchar *temporal,*temp_ptr,*data_ptr,truncated=0;
    gint maxdata,header_len;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    header_len=sizeof(struct icmp_header); 
    
    if (pkt_hdr->caplen < (offset+sizeof(struct icmp_header))){
	truncated=1;
    }else{
	icmp_ptr=(struct icmp_header*)(pkt+offset);
    }

    //Se insertan datos independientes de si esta truncada la trama o no.
    if (mode==2){
        sprintf(str_buf_run,"ICMP");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_get_text(pos,3,&temporal);
	sprintf(str_buf_run,"%s / ICMP",temporal);
	winini_clist_set_text(pos,3,str_buf_run);	
	//free(temporal);
    }
    
    if (truncated){
	//Si esta truncada
	if(mode==2){
	    sprintf(str_buf_run,"Paquete truncado.");
    	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	}
	return;
    }
    
    if (mode==2){
	//Si es mode 2 se actualiza el arbol de la trama.
	get_icmp_type(icmp_ptr->type,&temporal);
	sprintf(str_buf_run,"ICMP tipo: %s",temporal);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	//free(temporal);
	
	get_icmp_code(icmp_ptr->type,icmp_ptr->code,&temporal);
	sprintf(str_buf_run,"ICMP codigo: %s",temporal);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	//free(temporal);
	
	sprintf(str_buf_run,"Checksum: 0x%x",ntohs(icmp_ptr->checksum));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
 	//Dependiendo del tipo del paquete ICMP se analizara de distinta manera.
	if ((icmp_ptr->type==ICMP_TYP_ECHO_REPLY)||(icmp_ptr->type==ICMP_TYP_ECHO)||(icmp_ptr->type==ICMP_TYP_TIMESTAMP)||(icmp_ptr->type==ICMP_TYP_TIMESTAMP_REPLY)||(icmp_ptr->type==ICMP_TYP_INFOR_REQUEST)||(icmp_ptr->type==ICMP_TYP_INFOR_REPLY)||(icmp_ptr->type==ICMP_TYP_ADDR_MASK_REQUEST)||(icmp_ptr->type==ICMP_TYP_ADDR_MASK_REPLY)){

		temp_ptr=(char *)(icmp_ptr);
		temp_ptr=temp_ptr+sizeof(struct icmp_header);
		echo_ptr=(struct icmp_echo_header *)temp_ptr;

		sprintf(str_buf_run,"ID: 0x%x",ntohs(echo_ptr->id));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		sprintf(str_buf_run,"Numero de secuencia: 0x%x",ntohs(echo_ptr->seq_num));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
		
	}else if(icmp_ptr->type==ICMP_TYP_REDIRECT){

		temp_ptr=(char *)(icmp_ptr);
		temp_ptr=temp_ptr+sizeof(struct icmp_header);
		redirect_ptr=(struct icmp_redirect_header *)temp_ptr;
		
		temp_addr.s_addr=*((bpf_u_int32 *)redirect_ptr->router_addr);

	    	sprintf(str_buf_run,"IP del ruter a direccionar: %s",inet_ntoa(temp_addr));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
	}
	if ((icmp_ptr->type==ICMP_TYP_ADDR_MASK_REQUEST)||(icmp_ptr->type==ICMP_TYP_ADDR_MASK_REPLY)){
	
		//Se usa la misma estructura que para REDIRECT
		temp_ptr=(char *)(icmp_ptr);
		temp_ptr=temp_ptr+sizeof(struct icmp_header)+4; //4bytes de ID y NumSeq
		redirect_ptr=(struct icmp_redirect_header *)temp_ptr;
		
		temp_addr.s_addr=*((bpf_u_int32 *)redirect_ptr->router_addr);

	    	sprintf(str_buf_run,"Mascara de subred: %s",inet_ntoa(temp_addr));
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
	}
	//Fin de tipos

	//Datos que van a continuacion del paquete ICMP.
	//Se consideran los datos todo por encima de los primeros 32 bits.
	if (pkt_hdr->caplen > (offset+header_len) ){
	    data_ptr=(char *)(pkt+offset+header_len);
	    maxdata=pkt_hdr->caplen-(offset+header_len);
	    data_tree(subtree,data_ptr,maxdata);
	}
	
    }
    offset=offset+header_len;
}



