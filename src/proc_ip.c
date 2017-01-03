//proc_ip.c
//---------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "misc.h"
#include "proc_ip.h"
#include "win_error.h"
#include "win_ini.h"
#include "proc_frame.h"
#include "proc_tcp.h"
#include "proc_udp.h"
#include "proc_icmp.h"
#include "win_options.h"

//Prototipos estaticos
static guint8 get_ip_vers(const struct ip_header *ip_ptr);
static guint8 get_ip_hlen(const struct ip_header *ip_ptr);
static void get_ip_protocol(guint8 type,char **str_pp);

//Funcion que devuelve la version de la cabecera de un paquete IP.
//Parametros:
//	ip_ptr:Puntero a la estructura de la cabecera del paquete IP.
//	Devuelve:Entero con la version IP.
guint8 get_ip_vers(const struct ip_header *ip_ptr)
{
    return ((ip_ptr->vers_hlen & 0xf0) >> 4);
}

//Funcion que devuelve el tamaño de la cabecera de un paquete IP.
//Parametros:
//	ip_ptr:Puntero a la estructura de la cabecera del paquete IP.
//	Devuelve:Numero de bytes del tamaño.
guint8 get_ip_hlen(const struct ip_header *ip_ptr)
{
    return ((ip_ptr->vers_hlen & 0x0f)*4); 
    //Se multiplica por 4 para que lo devuelva en bytes
}

//Devuelve una cadena con el protocolo correspondiente al codigo que se le pasa.
//Parametros:
//	type:Entero con el codigo del protocolo que se esta usando.
//	str_pp:Puntero a puntero donde se almacenara la cadena del protocolo.
void get_ip_protocol(guint8 type,char **str_pp)
{

    if((*str_pp=(char *)malloc(40))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };

    switch(type){

	case ICMP:
	    sprintf(*str_pp,"ICMP");
	    break;
	case IGMP:
	    sprintf(*str_pp,"IGMP");
	    break;
	case GGP:
	    sprintf(*str_pp,"GGP");
	    break;
	case IP:
	    sprintf(*str_pp,"IP");
	    break;
	case STREAM:
	    sprintf(*str_pp,"STREAM");
	    break;
	case TCP:
	    sprintf(*str_pp,"TCP");
	    break;
	case UDP:
	    sprintf(*str_pp,"UDP");
	    break;
	case CBT:
	    sprintf(*str_pp,"CBT");
	    break;
	case EGP:
	    sprintf(*str_pp,"EGP");
	    break;
	case IGP:
	    sprintf(*str_pp,"IGP");
	    break;
	case BBNRCCMON:
	    sprintf(*str_pp,"BBNRCCMON");
	    break;
	case BVPII:
	    sprintf(*str_pp,"BVPII");
	    break;
	case PUP:
	    sprintf(*str_pp,"PUP");
	    break;
	case ARGUS:
	    sprintf(*str_pp,"ARGUS");
	    break;
	case EMCON:
	    sprintf(*str_pp,"EMCOM");
	    break;
	case XNET:
	    sprintf(*str_pp,"XNET");
	    break;
	case CHAOS:
	    sprintf(*str_pp,"CHAOS");
	    break;
	case MUX:
	    sprintf(*str_pp,"MUX");
	    break;	
	case DCNMEANS:
	    sprintf(*str_pp,"DCNMEANS");
	    break;
	case HMP:
	    sprintf(*str_pp,"HMP");
	    break;
	case PRM:
	    sprintf(*str_pp,"PRM");
	    break;
	case XNSIDP:
	    sprintf(*str_pp,"XNSIDP");
	    break;
	case TRUNK1:
	    sprintf(*str_pp,"TRUNK 1");
	    break;
	case TRUNK2:
	    sprintf(*str_pp,"TRUNK 2");
	    break;
	case LEAF1:
	    sprintf(*str_pp,"LEAF 1");
	    break;
	case LEAF2:
	    sprintf(*str_pp,"LEAF 2");
	    break;
	case RFP:
	    sprintf(*str_pp,"RFP");
	    break;
	case IRTP:
	    sprintf(*str_pp,"IRTP");
	    break;
	case ISOTP4:
	    sprintf(*str_pp,"ISOTP4");
	    break;
	case NETBLT:
	    sprintf(*str_pp,"NETBLT");
	    break;
	default:
	    sprintf(*str_pp,"Desconocido");
	    break;
    }
}

//Funcion que actualiza los datos relacionados con el protocolo IP
//   de una trama determinada.
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
//	offset:Desplazamiento que hay que avanzar con el puntero a la trama
//		para situarse en el principio del paquete IP.(para saltar los
//		datos de los protocolos anteriores).
void ip_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset)
{    
    GtkWidget *treeitem,*subtree;
    struct ip_header *ip_ptr;
    struct in_addr src_ip,dest_ip;
    guint16 mflag,dflag;
    gchar *data_ptr, *temporal,truncated=0;
    guint8 header_len;
    gint maxdata;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;

    //Se mira si se puede acceder al primer byte(donde esta el tamaño de cabecera).
    if (pkt_hdr->caplen < (offset+1)){
	truncated=1;
    }else{
	//Se apunta al primer byte de la cabecera IP
	ip_ptr=(struct ip_header*)(pkt+offset);	
	//Se obtiene el tamaño de la cabecera.
	header_len=get_ip_hlen(ip_ptr);
	//Se mira sí está truncado
	if(pkt_hdr->caplen < (offset+header_len)){
	    truncated=1;
	}
    }

    //Se inserta lo que es independiente de si esta truncado o no.
    if (mode==2){
        sprintf(str_buf_run,"IP");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
    }else{
	winini_clist_get_text(pos,3,&temporal);
	sprintf(str_buf_run,"%s / IP",temporal);
	winini_clist_set_text(pos,3,str_buf_run);
	//free(temporal);
    }
    
    if (truncated){
	//Si esta truncado
	if(mode==2){
	    sprintf(str_buf_run,"Paquete truncado.");
    	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	}
	return;
    }
    
    
    //Se sale si no es la version IPv4
    if(get_ip_vers(ip_ptr)!=4){
	if (mode==2){
	    sprintf(str_buf_run,"Version IP(%u) desconodica.",get_ip_vers(ip_ptr));
	    treeitem=gtk_tree_item_new_with_label(str_buf_run);
	    gtk_tree_append(GTK_TREE(subtree),treeitem);
	    gtk_widget_show(treeitem);
	}
	return;
    }
    
    //Se obtiene la informacion común a los 2 modos.
    src_ip.s_addr=*((bpf_u_int32 *)ip_ptr->src_addr);
    dest_ip.s_addr=*((bpf_u_int32 *)ip_ptr->dest_addr);
	
    
    if (mode==2){

	sprintf(str_buf_run,"IP Version: %u",get_ip_vers(ip_ptr));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	    
	sprintf(str_buf_run,"Tamaño de cabecera: %u",header_len);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Tamaño total(con datos): %u",ntohs(ip_ptr->tlen));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"ID: %u",ntohs(ip_ptr->id));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	//Flags
	mflag=(ntohs(ip_ptr->offset) & MF_FLAG_MASK);
	if (mflag > 0) mflag=1;
	dflag=(ntohs(ip_ptr->offset) & DF_FLAG_MASK);
	if (dflag > 0) dflag=1;
	
	sprintf(str_buf_run,"Flags: DF(prohibe fragmentacion):%u MF(ultimo fragmento):%u",dflag,mflag);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Offset: %u",(ntohs(ip_ptr->offset) & OFFSET_MASK));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Tiempo de vida (TTL): %u",ip_ptr->ttl);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	get_ip_protocol(ip_ptr->protocol,&temporal);
	sprintf(str_buf_run,"Protocolo encapsulado: %s",temporal);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	//free(temporal);
	
	sprintf(str_buf_run,"Header checksum: 0x%x",ntohs(ip_ptr->checksum));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
        sprintf(str_buf_run,"Direccion IP origen: %s",inet_ntoa(src_ip));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	sprintf(str_buf_run,"Direccion IP destino: %s",inet_ntoa(dest_ip));
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);	
	
	//Datos
	if(pkt_hdr->caplen > (offset+header_len) ){
	    data_ptr=(char *)(pkt+offset+header_len);
	    maxdata=pkt_hdr->caplen-(offset+header_len)    ;
	    data_tree(subtree,data_ptr,maxdata);
	}
	
    }else{
	//Si esta selecciona la opcion adecuada en las opciones avanzadas, se 
	//  sobreescriben las direcciones MAC de la lista con las IP
	if (winoptions_option_ip()){
	    sprintf(str_buf_run,"%s",inet_ntoa(src_ip));
	    winini_clist_set_text(pos,1,str_buf_run);	
	    sprintf(str_buf_run,"%s",inet_ntoa(dest_ip));
	    winini_clist_set_text(pos,2,str_buf_run);
	}
    }    
    
    offset=offset+header_len;

    switch(ip_ptr->protocol){	
	case ICMP:
	    icmp_handler(pos,pkt_hdr,pkt,mode,offset);	    
	    break;
	case IGMP:
	    break;
	case IP:
	    break;
	case STREAM:
	    break;
	case TCP:
	    tcp_handler(pos,pkt_hdr,pkt,mode,offset);
	    break;
	case UDP:
	    udp_handler(pos,pkt_hdr,pkt,mode,offset);
	    break;
	default:
	    break;
    }
}

