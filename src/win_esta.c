//esta.c  
//------

#include <gtk/gtk.h>
#include <pcap.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "time.h"
#include "misc.h"
#include "win_esta.h"
#include "interface.h"
#include "support.h"
#include "win_cap.h"
#include "pkt_mem_list.h"
#include "win_error.h"

//Prototipos estaticos
static void refresh_lan();
static guint mac_esta_of(char *macaddr,char mode);
static char new_mac_addres(char *macaddr,GList *list);
static char ether_ok(int frame);
static char* pkt_get_time(struct pcap_pkthdr *pkthdr);
static void refresh_wan();
static guint ip_esta_of(char *ipaddr,char mode);
static char new_ip_addres(char *ipaddr,GList *list);
static char ip_ok(int frame);
static void free_frames_list(GList *list);

//Variables globales
static GtkWidget *clist_estalocal;
static GtkWidget *clist_estaip;
static GtkWidget *esta_fixed;
static GList *macframes_list=NULL; //Lista donde se tendran los ids de los frames que se pueden analizar las direcciones MAC
static GList *ipframes_list=NULL;  //Lista donde se tendran los ids de los frames que se pueden analizar las direcciones IP

//Variable global externa
extern GtkWidget *win_ini;		//Puntero a ventana principal necesario para referenciar widgets de la pagina

//Funcion que hace refrescar las estadisticas de una captura.Llamará a las funciones
// refresh_esta_lan() y refresh_esta_ip() que son las funciones que refrescan las
// las estadisticas de la LAN y de la red IP.
//Se le llama cada vez que se entra en la pagina del notebook correspondiente.
void winesta_refresh()
{
    
    GtkWidget *label_estainicio,*label_estafin,*label_estanumtram;
    GtkWidget *scrolledwin_lan,*scrolledwin_ip;
    GtkWidget *label_estalaf,*label_estaltf;
    GtkWidget *label_estaiaf,*label_estaitf;
    GtkWidget *notebookx;
    GtkWidget *table1;
    GList *runner;
    guint num_of_frames;
    struct packet_list_node *node;
    
    table1=lookup_widget(win_ini,"table1");
    notebookx=lookup_widget(table1,"notebook");
    esta_fixed=lookup_widget(notebookx,"fixed7");
    scrolledwin_ip=lookup_widget(esta_fixed,"scrolledwindow5");
    clist_estaip=lookup_widget(scrolledwin_ip,"clist4");
    scrolledwin_lan=lookup_widget(esta_fixed,"scrolledwindow4");
    clist_estalocal=lookup_widget(scrolledwin_lan,"clist3");

    label_estaltf=lookup_widget(esta_fixed,"label_estaltf");
    label_estalaf=lookup_widget(esta_fixed,"label_estalaf");
    label_estaitf=lookup_widget(esta_fixed,"label_estaitf");
    label_estaiaf=lookup_widget(esta_fixed,"label_estaiaf");    

    label_estainicio=lookup_widget(esta_fixed,"label_estainicio");
    label_estafin=lookup_widget(esta_fixed,"label_estafin");
    label_estanumtram=lookup_widget(esta_fixed,"label_estanumtram");

    num_of_frames=pkt_mem_list_length();

    sprintf((char *)str_buf,"%u",num_of_frames);
    gtk_label_set_text(GTK_LABEL(label_estanumtram),(char *)str_buf);

    //Se libera la lista de memoria macframes_list e ipframes_list, en caso de 
    //que ya se hayan usado anteriormente.
    if (macframes_list!=NULL){
    	g_list_free(macframes_list);
    }
    if (ipframes_list!=NULL){
	g_list_free(ipframes_list);
    }
    
    macframes_list=NULL;
    ipframes_list=NULL;
    
    //Se borran las entradas de las listas de las estadisticas.    
    gtk_clist_clear(GTK_CLIST(clist_estalocal));
    gtk_clist_clear(GTK_CLIST(clist_estaip));
    
    if (num_of_frames>0){
	//Se haya el tiempo de inicio de captura y el tiempo del fin de la captura.
	runner=pkt_mem_list_nth(0);
	node=(struct packet_list_node *)runner->data;
	gtk_label_set_text(GTK_LABEL(label_estainicio),pkt_get_time(node->pkthdr));
	
	runner=pkt_mem_list_nth(num_of_frames-1);
	node=(struct packet_list_node *)runner->data;
	gtk_label_set_text(GTK_LABEL(label_estafin),pkt_get_time(node->pkthdr));
	
	//Se refrescan las estadisticas de la LAN y luego de la red IP.	
	refresh_lan();
	refresh_wan();
	
    }else{
	//Si no hay frames capturados así que se limpia la pantalla.
	gtk_label_set_text(GTK_LABEL(label_estainicio),"");
	gtk_label_set_text(GTK_LABEL(label_estafin),"");
	gtk_label_set_text(GTK_LABEL(label_estaltf),"0");
	gtk_label_set_text(GTK_LABEL(label_estalaf),"0");    
	gtk_label_set_text(GTK_LABEL(label_estaitf),"0");
	gtk_label_set_text(GTK_LABEL(label_estaiaf),"0");    
    }
    
}


//Funcion que actualiza las estadisticas de la LAN
void refresh_lan()
{
    GtkWidget *label_estalaf,*label_estaltf;
    GList *macaddress_list=NULL; //Lista con las diferentes direcciones de maquinas MAC
    GList *runner;
    int cnt,*temp;
    char *macaddress;
    struct packet_list_node *node;
    struct ether_header *eptr;
    gchar *mac_clist[5];	//Estructura para insertar una linea en la lista de estadisticas de LAN.
    
    //Se hayan las referencias de las labels
    label_estaltf=lookup_widget(esta_fixed,"label_estaltf");
    label_estalaf=lookup_widget(esta_fixed,"label_estalaf");
    
    //Primero son introducidos en el macframes_list los ids de las tramas capturadas
    //  que se pueden analizar para esta funcion, es decir, las tramas a las que
    //  se puede tener acceso a sus direcciones MAC.
    for (cnt=0;cnt<pkt_mem_list_length();cnt++){
	if (ether_ok(cnt)){
	    //Si es una trama valida se mete su id en la lista.
	    if ((temp=(int *)malloc(sizeof(int)))==NULL){
		winerror_msg("No hay suficiente memoria.");
		gtk_main_quit();
		exit (-1);
	    }
	    *temp=cnt;
	    macframes_list=g_list_append(macframes_list,(gpointer)temp);
	}
    }

    //Se actualizan las labels con el numero total de tramas de la captura y 
    //con el número de tramas que se pueden analizar..
    sprintf((char *)str_buf,"%d",pkt_mem_list_length());
    gtk_label_set_text(GTK_LABEL(label_estaltf),(char *)str_buf);
    sprintf((char *)str_buf,"%d",g_list_length(macframes_list));
    gtk_label_set_text(GTK_LABEL(label_estalaf),(char *)str_buf);

    //Ya se tiene una lista con los frames validos para el analisis.
    //Ahora se hace una lista con todas las direcciones distintas de la red LOCAL.
    //Se recorre la lista de tramas válidas y se guardan todas las direcciones
    //  MAC distintas.
    for(cnt=0;cnt<g_list_length(macframes_list);cnt++){
	//Se recorre toda la lista de memoria de tramas capturados.
	runner=g_list_nth(macframes_list,cnt);
	temp=(int *)runner->data;
	runner=pkt_mem_list_nth(*temp);
	node=(struct packet_list_node *)runner->data;
	eptr=(struct ether_header *)node->pkt;	
	
	//Primero se analiza la direccion de origen.
	//Se guarda  la direccion origen de la trama en macaddres
	if((macaddress=(char *)malloc(18))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit (-1);
	    
	};
	sprintf(macaddress,"%s",ether_ntoa(eptr->ether_shost));
	
	//Si macaddress es nueva y no es la direccion de broadcast
	//  entonces se inserta en la lista de direcciones MAC
	if (strcmp(macaddress,"ff:ff:ff:ff:ff:ff")!=0){
	    //Si no es direccion de broadcast se mira si es nueva.
	    if (new_mac_addres(macaddress,macaddress_list)){
		//En caso de ser una direccion nueva, se inserta en la lista
		//  macaddres_list.
		macaddress_list=g_list_append(macaddress_list,(gpointer)macaddress);
	    }
	}	
	
	//Se hace el mismo analisis con la direccion MAC destino de la trama.
	if((macaddress=(char *)malloc(18))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit (-1);
	}
	//Si macaddress es nueva y no es la direccion de broadcast
	//  entonces se inserta en la lista de direcciones MAC
	sprintf(macaddress,"%s",ether_ntoa(eptr->ether_dhost));
	if (strcmp(macaddress,"ff:ff:ff:ff:ff:ff")!=0){
	    if (new_mac_addres(macaddress,macaddress_list)){
		//En caso de ser una direccion nueva, se inserta en la lista
		//  macaddres_list.
		macaddress_list=g_list_append(macaddress_list,(gpointer)macaddress);
	    }
	}		
    }
    //Ahora se tiene en macaddres_list todas las direcciones MAC distintas 
    //  que se han usado durante la sesion.
    
    //Se insertan todas las direcciones MAC en la lista de direcciones MAC
    //y se analizaran sus estadisticas una por una.
    for(cnt=0;cnt<g_list_length(macaddress_list);cnt++){
	runner=g_list_nth(macaddress_list,cnt);
	macaddress=(char *)runner->data;
	mac_clist[0]=macaddress;	
	
	//Se van hayando las estadisticas por separado de la direccion MAC
	
	//Primero se hayan los bytes emitidos por esa direccion
	sprintf((char *)str_buf,"%u",mac_esta_of(macaddress,1));
	if((mac_clist[1]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(mac_clist[1],(char *)str_buf);
	
	//Luego se hayan los bytes recibidos por esa dirccion.
	sprintf((char *)str_buf,"%u",mac_esta_of(macaddress,2));
	if ((mac_clist[2]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit (-1);
	};
	strcpy(mac_clist[2],(char *)str_buf);
	
	//Ahora se haya el numero de tramas recibidas por esa direccion
	sprintf((char *)str_buf,"%u",mac_esta_of(macaddress,3));
	if ((mac_clist[3]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit (-1);
	};
	strcpy(mac_clist[3],(char *)str_buf);
	
	//Finalmente se haya el numero de tramas emitidas.
	sprintf((char *)str_buf,"%u",mac_esta_of(macaddress,4));
	if((mac_clist[4]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(mac_clist[4],(char *)str_buf);
	
	//Una vez hayadas todas las estadisticas, se insertan en la lista de
	//  estadisticas.
	gtk_clist_append(GTK_CLIST(clist_estalocal),mac_clist);
	
	
    }
    
    //Si se ha utilizado macaddres_list, se liberará la memoria utilizada.
    if (macaddress_list!=NULL){
	free_frames_list(macaddress_list);
    }
}

//Funcion que devuelve estadisticas de la direccion MAC que se le pasa
//Segun el mode devolvera una cosa u otra.
//Parametros:
//	macaddr:Puntero a la cadena que contiene la direccion a analizar.
//	mode:El modo de analisis.
//  		mode 1:Devuelve bytes emitidos en esa direccion
//  		mode 2:Devuelve bytes recibidos en esa direccion
//  		mode 3:Devuelve tramas emitidas
//  		mode 4:Devuelve tramas recibidas
//	Devuelve un unsigned int que depende del mode.
guint mac_esta_of(char *macaddr,char mode)
{
    guint cnt,*temp,bytes=0,frames=0;
    GList *runner;
    struct pcap_pkthdr *pkthdr;
    struct ether_header *eptr;
    struct packet_list_node *node;
    
    //Se recorre la lista de todas las direcciones MAC en busca
    //de coincidencias con la direccion MAC pasada.
    for(cnt=0;cnt<g_list_length(macframes_list);cnt++){
	runner=g_list_nth(macframes_list,cnt);
	temp=(int *)runner->data;
	runner=pkt_mem_list_nth(*temp);
	node=(struct packet_list_node *)runner->data;
	eptr=(struct ether_header *)node->pkt;
	
	if ((mode==1)||(mode==3)){
	    if(strcmp(ether_ntoa(eptr->ether_shost),macaddr)==0){
		pkthdr=node->pkthdr;
		bytes+=pkthdr->caplen;
		frames++;
	    }
	}else{	
	    if(strcmp(ether_ntoa(eptr->ether_dhost),macaddr)==0){
		pkthdr=node->pkthdr;
		bytes+=pkthdr->caplen;
		frames++;
	    }
	}
		
    }

    if ((mode==1)||(mode==2)){
	return(bytes);
    }else return(frames);

}

//Funcino para analizar si una direccion MAC es nueva o no.
//Parametros:
//	macaddr:Puntero a la cadena con la direccion MAC a analizar
//	list:Puntero a la lista donde se tiene que buscar la direccion MAC.
//	Devuelve True si la direccion MAC es nueva y False si no.
char new_mac_addres(char *macaddr,GList *list)
{
    guint cnt;
    char *str;
    GList *runner;
    
    for (cnt=0;cnt<g_list_length(list);cnt++){
	runner=g_list_nth(list,cnt);
	str=(char *)runner->data;
	//Se comprar macaddr con str
	if (strcmp(str,macaddr)==0) {	    
	    //Si las direcciones son iguales
	    return 0;
	}
    }
    //Si no se han hayado coincidencias.
    return 1;
}

//Funcion que dice si una trama MAC es apta o no para el analisis, es decir si
//  se han capturado las direcciones origen y destino.
//Parametros:
//	frame:Entero que tiene el id de la trama a analizar
//	Devuelve:
//		1:Si la trama es apta
//		0:Si la trama no es apta
char ether_ok(int frame)
{
    struct packet_list_node *node;
    struct pcap_pkthdr *pkthdr;
    GList *runner;    

    if (frame<pkt_mem_list_length()){
	runner=pkt_mem_list_nth(frame);
	node=(struct packet_list_node *)runner->data;
	pkthdr=node->pkthdr;
	//Si se han capturado mas de 12 bytes quiere decir que se tiene acceso
	//  a las 2 direcciones de la trama (ya que una direccion MAC es de 
	//  6 bytes, y van al principio de la trama).
    	if (pkthdr->caplen>=12) return 1;
	else return 0;
	
    }else return 0;
}

//Funcion para hayar el tiempo de llegada de una trama
//Parametro:
//	pkthdr:Puntero a estructura con datos del paquete capturado.
//	Devuelve:Puntero  a cadena con el tiempo de llegada.
char* pkt_get_time(struct pcap_pkthdr *pkthdr)
{
    return  ctime((const time_t*)&pkthdr->ts.tv_sec);
}


//Funcion que actualiza las estadisticas de la LAN
void refresh_wan()
{
    GtkWidget *label_estaiaf,*label_estaitf;
    GList *ipaddress_list=NULL;
    GList *runner;
    GString *gcadena;
    int cnt,*temp;
    gchar *ipaddress,*strbroadcastaddress=NULL;
    gchar *ip_clist[5];    
    guint32 broadcastaddress;
    struct packet_list_node *node;
    struct ipaddr_header *ip_ptr;
    struct in_addr ip_addr;    
    
    label_estaitf=lookup_widget(esta_fixed,"label_estaitf");
    label_estaiaf=lookup_widget(esta_fixed,"label_estaiaf");    
    
    //Primero son introducidos en el ipframes_list los ids de las tramas capturadas
    //  que se pueden analizar para esta funcion, es decir, las tramas a las que
    //  se puede tener acceso a sus direcciones IP origen y destino.
    for (cnt=0;cnt<pkt_mem_list_length();cnt++){
	if (ip_ok(cnt)){
	    temp=malloc(sizeof(int));
	    *temp=cnt;
	    ipframes_list=g_list_append(ipframes_list,(gpointer)temp);
	}
    }
    
    //Se actualizan las labels con el numero total de tramas de la captura y 
    //con el número de tramas que se pueden analizar..
    sprintf((char *)str_buf,"%d",pkt_mem_list_length());
    gtk_label_set_text(GTK_LABEL(label_estaitf),(char *)str_buf);
    sprintf((char *)str_buf,"%d",g_list_length(ipframes_list));
    gtk_label_set_text(GTK_LABEL(label_estaiaf),(char *)str_buf);    
    
    //Una vez esta la lista con las tramas validas, se hace otra con todas las 
    //  direcciones IP utilizadas durante la captura.
    for(cnt=0;cnt<g_list_length(ipframes_list);cnt++){
	runner=g_list_nth(ipframes_list,cnt);
	temp=(int *)runner->data;

	runner=pkt_mem_list_nth(*temp);
	node=(struct packet_list_node *)runner->data;
	ip_ptr=(struct ipaddr_header *)(node->pkt+14);
	
	//Se saca de la trama la direccion IP origen y se almacena en la 
	//  variable ipaddress.
	ip_addr.s_addr=*((bpf_u_int32 *)ip_ptr->src_addr);
	gcadena=g_string_new(inet_ntoa(ip_addr));
	ipaddress=gcadena->str;

	//Si se ha abierto la ventana de captura y el usuario ha introducido
	// la interfaz a usar, se podra averiguar la direccion de la red, y por lo
	// tanto se podrá averiguar la direccion broadcast.
	if ((wincap_get_netp()!=0)&&(wincap_get_maskp()!=0)){
	    broadcastaddress=~wincap_get_maskp();
	    broadcastaddress=(broadcastaddress | wincap_get_netp());
	    ip_addr.s_addr=broadcastaddress;
	    //16 es el maximo numero de bytes que puede ocupar
	    if ((strbroadcastaddress=(gchar *)malloc(16))==NULL){
		winerror_msg("No hay suficiente memoria.");
		gtk_main_quit();
		exit(-1);
	    };
	    //Se almacena en strbroadcastaddres una cadena con la direccion
	    //  broadcast de la red local.
	    sprintf(strbroadcastaddress,"%s",inet_ntoa(ip_addr));
	}

	//Si la IP origen  es nueva y no es una IP de broadcast, se inserta en la lista de direcciones
	if ((strbroadcastaddress==NULL)||(strcmp(ipaddress,strbroadcastaddress)!=0)){
	    if (new_ip_addres(ipaddress,ipaddress_list)){
		//Nueva direccion ipaddres
		ipaddress_list=g_list_append(ipaddress_list,(gpointer)ipaddress);
	    }
	}

	//Se saca de la trama la direccion IP destino y se almacena en la 
	//  variable ipaddress.	
	ip_addr.s_addr=*((bpf_u_int32 *)ip_ptr->dest_addr);	
	gcadena=g_string_new(inet_ntoa(ip_addr));
	ipaddress=gcadena->str;	
	
	//Si IP destino  es nueva y no es una IP de broadcast, se inserta en la lista de direcciones	
	if ((strbroadcastaddress==NULL)||(strcmp(ipaddress,strbroadcastaddress)!=0)){
	    if (new_ip_addres(ipaddress,ipaddress_list)){
		ipaddress_list=g_list_append(ipaddress_list,(gpointer)ipaddress);
	    }
	}		

    }

    //Ahora se tiene en la lista ipcaddres_list todas las direcciones IP que
    //  han sido utilizadas durante la captura.
    
    //Se insertan todas las direcciones distintas en la lista  y serán analizadas
    //  una por una
    for(cnt=0;cnt<g_list_length(ipaddress_list);cnt++){
	runner=g_list_nth(ipaddress_list,cnt);
	ipaddress=(char *)runner->data;
	ip_clist[0]=ipaddress;	
	
	sprintf((char *)str_buf,"%u",ip_esta_of(ipaddress,1));
	if((ip_clist[1]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(ip_clist[1],(char *)str_buf);
	
	sprintf((char *)str_buf,"%u",ip_esta_of(ipaddress,2));
	if((ip_clist[2]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(ip_clist[2],(char *)str_buf);
	
	sprintf((char *)str_buf,"%u",ip_esta_of(ipaddress,3));
	if((ip_clist[3]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(ip_clist[3],(char *)str_buf);
	
	sprintf((char *)str_buf,"%u",ip_esta_of(ipaddress,4));
	if((ip_clist[4]=(char *)malloc(strlen((char *)str_buf+1)))==NULL){
	    winerror_msg("No hay suficiente memoria.");
	    gtk_main_quit();
	    exit(-1);
	};
	strcpy(ip_clist[4],(char *)str_buf);
	
	gtk_clist_append(GTK_CLIST(clist_estaip),ip_clist);	
	
    }
    
    if (ipaddress_list!=NULL){
	free_frames_list(ipaddress_list);
    }
    
}

//Funcion que devuelve estadisticas de la direccion IP que se le pasa
//Segun el mode devolvera una cosa u otra.
//Parametros:
//	ipaddr:Puntero a la cadena que contiene la direccion IP a analizar.
//	mode:El modo de analisis.
//  		mode 1:Devuelve bytes emitidos en esa direccion
//  		mode 2:Devuelve bytes recibidos en esa direccion
//  		mode 3:Devuelve tramas emitidas
//  		mode 4:Devuelve tramas recibidas
//	Devuelve un unsigned int que depende del mode.
guint ip_esta_of(char *ipaddr,char mode)
{
    guint cnt,*temp,bytes=0,frames=0;
    GList *runner;
    struct pcap_pkthdr *pkthdr;
    struct packet_list_node *node;
    struct ipaddr_header *ip_ptr;
    struct in_addr ip_srcaddr,ip_destaddr;
    
    //Se recorre la lista de tramas validas de IP en busca de la direccion
    //  que se le ha pasado a la funcion, en caso de coincidencia, esta trama
    //  entrará al analisis.
    for(cnt=0;cnt<g_list_length(ipframes_list);cnt++){
	runner=g_list_nth(ipframes_list,cnt);
	temp=(int *)runner->data;
	runner=pkt_mem_list_nth(*temp);
	node=(struct packet_list_node *)runner->data;
	ip_ptr=(struct ipaddr_header *)(node->pkt+14);
	ip_srcaddr.s_addr=*((bpf_u_int32 *)ip_ptr->src_addr);
	ip_destaddr.s_addr=*((bpf_u_int32 *)ip_ptr->dest_addr);
	
	
	if ((mode==1)||(mode==3)){
	    if(strcmp((char *)inet_ntoa(ip_srcaddr),ipaddr)==0){
		pkthdr=node->pkthdr;
		bytes+=pkthdr->caplen;
		frames++;
	    }
	}else{
	    if(strcmp((char *)inet_ntoa(ip_destaddr),ipaddr)==0){
		pkthdr=node->pkthdr;
		bytes+=pkthdr->caplen;
		frames++;
	    }
	}
    }
    if ((mode==1)||(mode==2)){
	return(bytes);
    }else return(frames);

}


//Funcino para analizar si una direccion IP es nueva o no.
//Parametros:
//	macaddr:Puntero a la cadena con la direccion IP a analizar
//	list:Puntero a la lista donde se tiene que buscar la direccion IP.
//	Devuelve True si la direccion IP es nueva y False si no.
char new_ip_addres(char *ipaddr,GList *list)
{
    guint cnt;
    char *str;
    GList *runner;

    for (cnt=0;cnt<g_list_length(list);cnt++){
	runner=g_list_nth(list,cnt);
	str=(char *)runner->data;
	if (strcmp(str,ipaddr)==0) {
	    //Si las direcciones son igualees.
	    return 0;
	}
    }
    //No ha habido coincidencias.
    return 1;
    
}

//Funcion que dice si una trama  es apta o no para el analisis de la red IP, 
//  es decir si se han capturado las direcciones IP origen y destino.
//Parametros:
//	frame:Entero que tiene el id de la trama a analizar
//	Devuelve:
//		1:Si la trama es apta
//		0:Si la trama no es apta
char ip_ok(int frame)
{
    struct packet_list_node *node;
    struct pcap_pkthdr *pkthdr;
    struct ether_header *eptr;
    GList *runner;   
        
    if (frame<pkt_mem_list_length()){

	runner=pkt_mem_list_nth(frame);
	node=(struct packet_list_node *)runner->data;
	pkthdr=node->pkthdr;
	eptr=(struct ether_header *)node->pkt;	
    	if ((pkthdr->caplen>=26)&&(ntohs(eptr->ether_type)==ETHERTYPE_IP)) return 1; //Las direcciones son de 6 bytes.
	else return 0;	

    }else return 0;
}

//Se le pasa una lista de frames válidos (lista de punteros a enteros) y la libera
//  de memoria.
void free_frames_list(GList *list)
{
    GList *runner;
    gint length,cnt;
    gint *int_to_free;
    
    length=g_list_length(list);
    
    for(cnt=0;cnt!=length;cnt++){
	runner=g_list_nth(list,cnt);
	int_to_free=(gint *)runner->data;
	free(int_to_free);
    }
    
    g_list_free(list);
    list=NULL;
}

