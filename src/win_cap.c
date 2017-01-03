//win_cap.c
//---------

#include <pcap.h>
#include <gtk/gtk.h>
#include <netinet/in.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "support.h"
#include "misc.h"
#include "win_cap.h"
#include "win_ini.h"
#include "win_error.h"
#include "win_options.h"
#include "pkt_mem_list.h"
#include "interface.h"

//Prototipos estaticos
static void child_stoping_capture(int signal);
static void father_stop_capture();
static void pkt_callback(u_char *args,const struct pcap_pkthdr* pkthdr, const u_char* packet);
static void *thread_function(void *args);

//Variables globales
static GtkWidget *win_cap;
static GtkWidget *entry_dev;
static GtkWidget *entry_filter;
static GtkWidget *spin_numofpkt;
static GtkWidget *spin_maxtime;
static GtkWidget *spin_maxbytes;
static GtkWidget *check_numofpkt;
static GtkWidget *check_maxtime;
static GtkWidget *check_maxbytes;
static GtkWidget *check_promis;

static int thread_pid=0;	//PID del hilo para poder mandar señales y para saber si esta en ejecucion
static int father_pid=0;	//PID del padre para poder mandar señales desde el hijo
static int pkts_captured=0;	//Numero de paquetes capturados en el momento
static guint32 netp=0,maskp=0; 	//Enteros para almacenar IP y Mascara de red

static pcap_t *cap_descr=NULL;  //Descriptor de captura abierto en todo momento,
				//tambien en caso de ser abierto "offline"

//Funcion utilizada para obtener el descriptor de sesion abierto actualmente
pcap_t *wincap_get_pcap_descr()
{
    return cap_descr;
}

//Funcion utilizada para actualizar el descriptor de sesion abierto
void wincap_set_pcap_descr(pcap_t *new_descr)
{
    cap_descr=new_descr;
}

//Funcion que ejecuta el hilo cuando recibe la señal (SIGUSR1) de que tiene que parar
//de ejecutar o tb en caso de llegar al limite de paketes.
void child_stoping_capture(int signal)
{

    thread_pid=0; 

    //Se envía la señal para que actualice el padre la ventana
    kill(father_pid,SIGUSR2);

    //Se autodestruye el hilo
    pthread_exit(NULL);
    
}

//Funcion ejecutada por el proceso padre una vez le es llegada la señal SIGUSR2
// es decir, una vez el hilo termina de parar la captura y va a morir.
void father_stop_capture()
{
    //Al padre le llega SIGUSR2
    gtk_widget_hide_all(win_cap);
    gtk_widget_destroy(win_cap);

    winini_update_packet_mem_list();
    
}

//Funcion llamada cuando el usuario aprieta el boton de parar captura
//Funcion que debe ejecutar el padre para parar de capturar.
//En caso de estar capturando, para la captura llamando a la señal SIGUSR1 que hara
//que el hilo cierre la ventana y se pare.
//Esta función la ha de ejecutar el padre siempre para poder terminar bien la captura.
void wincap_stop_capture()
{
    
    if (thread_pid!=0){
	//Si el hijo esta capturando
	//el padre lanza señal de parar/matar al hijo
	kill(thread_pid,SIGUSR1);
	
	//El padre espera a que termine el hijo.
	for(;thread_pid!=0;){
	    sleep(1);
	}
	
    }

}

//Funcion que cierra la ventana en caso de que el hilo no este capturando
void wincap_close_window()
{
    if(thread_pid==0){
        gtk_widget_hide_all(win_cap);
	gtk_widget_destroy(win_cap);
    }
}

//Callback que llama pcap_open_live cuando se captura un paquete.
//Esta funcion inserta en la lista de memoria el paquete y la estructura del paquete
//que se le pasa como un nodo en memoria.
void pkt_callback(u_char *args,const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    
    pkts_captured+=1;
    
    pkt_mem_list_append(pkthdr,packet);
    
}


//Funcion que ejecuta el hilo al ser creado.
//Para matarlo desde otro proceso se hará llamando a SIGUSR1
void *thread_function(void *args)
{
    int num_of_pkt;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_numofpkt))){
	num_of_pkt=atoi(gtk_entry_get_text(GTK_ENTRY(spin_numofpkt)));
    }else num_of_pkt=0;

    //Se asigna una la funcion de parar captura(y matar al hilo) a la señal adecuada
    signal(SIGUSR1,child_stoping_capture);

    //Se obtiene el id de proceso del hilo.(para poder matarlo desde el padre)
    // y para poder saber desde fuera si el hilo esta en ejecucion o no.
    thread_pid=getpid(); 

    if(pcap_loop(cap_descr,num_of_pkt,pkt_callback,NULL)==-1){
	sprintf(str_buf_run,"Error leyendo un paquete:%s",pcap_geterr(cap_descr));
	winerror_msg(str_buf_run);
    }

    //El hilo ha capturado todos los paquetes y tiene que parar.
    child_stoping_capture(0);
}

//Funcion llamada cuando se le da al boton para empezar la captura de paquetes.
void wincap_start_capture()
{
    char *device,*str_filter,*str_buf_run;
    struct bpf_program filter_program;
    int thread_id;
    int maxbytes,maxtime,promis;    
    pthread_t pthread;
    
    str_buf_run=(char *)str_buf;
    
    device=(char *)gtk_entry_get_text(GTK_ENTRY(entry_dev));
    
    //Se obtienen los valores de opciones de captura para poder abrir bien el dispositivo.
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_maxtime))){
	maxtime=atoi(gtk_entry_get_text(GTK_ENTRY(spin_maxtime)));
    }else maxtime=0;

    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_maxbytes))){
	maxbytes=atoi(gtk_entry_get_text(GTK_ENTRY(spin_maxbytes)));
    }else maxbytes=BUFSIZ;//(BUFSIZ=8192byt es el tamaño del buffer interno que usa pcap)
    
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_promis))){
	promis=1;
    }else promis=0;

    //Se intenta abrir la interfaz con las opciones elegidas por el usuario.
    cap_descr=pcap_open_live(device,maxbytes,promis,-1,errbuf);
    if (cap_descr==NULL){
	winerror_msg("Error abriendo dispositivo para capturar.");
	return;
    }
    
    //Se mira si la interfaz corresponde a una red del tipo ETHERNETII
    //en caso contrario se informa al usuario de que ese tipo de dispositivo no
    //es apto para la captura.
    if(pcap_datalink(cap_descr)!=DLT_EN10MB){
	winerror_msg("Dispositivo no permitivo para la captura.");
	return;
    }
    
    //En caso de que el usuario haya introducido un filtro, se intenta aplicar.
    str_filter=gtk_entry_get_text(GTK_ENTRY(entry_filter));

    if (strcmp(str_filter,"")!=0){
    
	if (pcap_compile(cap_descr,&filter_program,str_filter,1,maskp)==-1){
	    //Hubo error al compilar el filtro.
	    sprintf(str_buf_run,"%s:%s","Error compilando filtro",pcap_geterr(cap_descr));
	    winerror_msg(str_buf_run);
	    return;
	}else{
	    if(pcap_setfilter(cap_descr,&filter_program)==-1){
		//Hubo error al aplicar el filtro.
		sprintf(str_buf_run,"%s:%s","Error aplicando filtro",pcap_geterr(cap_descr));
		winerror_msg(str_buf_run);
		return;
	    }
	}
    }
    
    //Se borran los paquetes anteriormente capturados en caso de que esa opcion
    //avanzada este seleccionada.
    if (winoptions_option_reset()){
	pkt_mem_list_reset();
    }
    
    //Se ponde la ventana en modo de captura para empezar a capturar
    wincap_mode_capture();
    
    //Se asigna al proceso padre la funcion de parar la captura en caso de que le
    //llegue la señal SIGALRM, que llegará en caso de que el usuario haya elegido
    //parar la aplicación pasados x segundos.
    signal(SIGALRM,wincap_stop_capture);
    
    father_pid=getpid();
    signal(SIGUSR2,father_stop_capture);
    
    //Se crea el hilo que se encargará de leer y meter en memoria los paquetes
    //capturados.
    thread_id=pthread_create(&pthread,NULL,thread_function,NULL);
    if (thread_id!=0){
	winerror_msg("Error creando al hilo");
	return;
    }

    //Se indica que no se quiere guardar el resultado del hilo, y así no se guardara
    //  una referencia del hilo en memoria una vez terminada su ejecucion.
    pthread_detach(thread_id);
    
    //Se hace que se le envie la señal SIGALRM pasados los segundos elegidos en caso
    //  de que el usuario lo haya querido asi
    if (maxtime!=0){
	alarm(maxtime);
    }
    
    return;
}

//Se le llama al darle al boton de abrir la ventana de opciones de captura.
void wincap_ini()
{
    GtkWidget *button4;
    GtkWidget *fixed;
    GtkWidget *label_cap1;
    char *dispo,*str_buf_run;
    
    str_buf_run=(char *)str_buf;
    //Se crea la ventaa de captura.
    win_cap=create_win_cap();
    
    fixed=lookup_widget(win_cap,"fixed2");
    spin_numofpkt=lookup_widget(fixed,"spin_numofpkt");
    spin_maxtime=lookup_widget(fixed,"spin_maxtime");
    spin_maxbytes=lookup_widget(fixed,"spin_maxbytes");
    entry_dev=lookup_widget(fixed,"entry_dev");
    entry_filter=lookup_widget(fixed,"entry_filter");    
    check_numofpkt=lookup_widget(fixed,"check_numofpkt");;
    check_maxtime=lookup_widget(fixed,"check_maxtime");;
    check_maxbytes=lookup_widget(fixed,"check_maxbytes");;
    check_promis=lookup_widget(fixed,"check_promis");;
    button4=lookup_widget(fixed,"button4");
    label_cap1=lookup_widget(fixed,"label_cap1");    
    
    gtk_widget_set_sensitive(button4,0);
    gtk_widget_set_sensitive(spin_numofpkt,0);
    gtk_widget_set_sensitive(spin_maxtime,0);
    gtk_widget_set_sensitive(spin_maxbytes,0);

    gtk_label_set_text(GTK_LABEL(label_cap1),"");
    
    pkts_captured=0;
    
    if((dispo=pcap_lookupdev(errbuf))!=NULL){
	gtk_entry_set_text(GTK_ENTRY(entry_dev),(gchar *)dispo);	
    }else{ 
	sprintf(str_buf_run,"No encontrado dispositivo para la captura:%s",errbuf);
	winerror_msg(str_buf_run);
    }
    
    gtk_widget_show_all(win_cap);
    
    wincap_update_ip_mask();
     
    //Abierta la ventana de opciones de captura

};

//Actualiza los cuadros de texto de IP y MASCARA apartir del dispositivo
//Se le llama cada vez que se actualiza el campo de dispositivo (o al iniciar la
//pantalla de captura).
//En caso de error, pone los campos mascara y direccion de red vacios y emite un 
//  mensage de error
void wincap_update_ip_mask()
{

    GtkWidget *fixed,*label_net_ip,*label_net_mask;
    struct in_addr addr;
    char *iptemp;
    char *dispo;

    dispo=gtk_entry_get_text(GTK_ENTRY(entry_dev));
    
    fixed=lookup_widget(GTK_WIDGET(win_cap),"fixed2");
    label_net_ip=lookup_widget(fixed,"label_net_ip");
    label_net_mask=lookup_widget(fixed,"label_net_mask");
    
    if(pcap_lookupnet(dispo,&netp,&maskp,errbuf)==-1){
	//No se encuentran la IP y la Mascara
	winerror_msg("No se encuenta IP y Mascara de red");
	gtk_label_set_text(GTK_LABEL(label_net_ip),"");
	gtk_label_set_text(GTK_LABEL(label_net_mask),"");
	return;
    }else{
	addr.s_addr=netp;
	iptemp=inet_ntoa(addr);
	if (iptemp==NULL){
	    //No se puede convertir
	    winerror_msg("Problemas en la conversion de la IP y Mascara de red");
	    gtk_label_set_text(GTK_LABEL(label_net_ip),"");
	    gtk_label_set_text(GTK_LABEL(label_net_mask),"");
	    return;
	}else{
	    gtk_label_set_text(GTK_LABEL(label_net_ip),iptemp);
	}
	
	addr.s_addr=maskp;
	iptemp=inet_ntoa(addr);
	if (iptemp==NULL){
	    //Nose puede convertir
	    winerror_msg("Problemas en la conversion de la IP y Mascara de red");
	    gtk_label_set_text(GTK_LABEL(label_net_ip),"");
	    gtk_label_set_text(GTK_LABEL(label_net_mask),"");
	    return;
	}else{
	    gtk_label_set_text(GTK_LABEL(label_net_mask),iptemp);
	}
    }
    return;
    
};


//Funcion para cambiar la ventana a modo de captura.
void wincap_mode_capture()
{

    GtkWidget *button_stop;
    GtkWidget *button_cap;
    GtkWidget *fixed;
    GtkWidget *label_cap1;
    
    fixed=lookup_widget(win_cap,"fixed2");        
    button_stop=lookup_widget(fixed,"button4");
    button_cap=lookup_widget(fixed,"button1");
    label_cap1=lookup_widget(fixed,"label_cap1");    
    
    gtk_widget_set_sensitive(entry_dev,0);
    gtk_widget_set_sensitive(entry_filter,0);
    gtk_widget_set_sensitive(check_numofpkt,0);
    gtk_widget_set_sensitive(check_maxtime,0);
    gtk_widget_set_sensitive(check_maxbytes,0);
    gtk_widget_set_sensitive(check_promis,0);
    gtk_widget_set_sensitive(spin_numofpkt,0);
    gtk_widget_set_sensitive(spin_maxtime,0);
    gtk_widget_set_sensitive(spin_maxbytes,0);
    gtk_widget_set_sensitive(button_cap,0);
    
    gtk_widget_set_sensitive(button_stop,1);   
    
    gtk_label_set_text(GTK_LABEL(label_cap1),"CAPTURANDO PAQUETES...");

};


//3 Funciones llamadas por los distintos botones de checkbox que activaran o no
//el uso de entrada de diferentes opciones.
void wincap_check_numofpkt_toggled()
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_numofpkt))){
	gtk_widget_set_sensitive(spin_numofpkt,1);
    }else{
	gtk_widget_set_sensitive(spin_numofpkt,0);
    }

};

void wincap_check_maxtime_toggled()
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_maxtime))){
	gtk_widget_set_sensitive(spin_maxtime,1);
    }else{
	gtk_widget_set_sensitive(spin_maxtime,0);
    }

};

void wincap_check_maxbytes_toggled()
{
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_maxbytes))){
	gtk_widget_set_sensitive(spin_maxbytes,1);
    }else{
	gtk_widget_set_sensitive(spin_maxbytes,0);
    }

};

//Funcion para obtener la direccion de red
guint32 wincap_get_netp()
{
    return netp;
};

//Funcion para obtener la direccion de la mascara de red
guint32 wincap_get_maskp()
{
    return maskp;
};

