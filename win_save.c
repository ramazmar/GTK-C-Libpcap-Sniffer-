//win_save.c
//----------

#include <pcap.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "support.h"
#include "misc.h"
#include "win_save.h"
#include "win_sure.h"
#include "interface.h"
#include "pkt_mem_list.h"
#include "win_error.h"
#include "win_options.h"
#include "win_ini.h"
#include "win_cap.h"
#include "win_infor.h"
#include "node.h"

//Prototipos estaticos
static int winsave_open_fileordir(char *dir_str);
static void winsave_open_file(char *dir_str);
static void pkt_callback_offline(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet);


//Variables globales
static GtkWidget *win_save=NULL;
static GtkWidget *winsave_clist;
static GtkWidget *winsave_entry;
static GtkWidget *winsave_label;
static char winsave_mode;
static char *actua_dir=NULL;
static pcap_t *save_descr=NULL;

//Variables globales externas
//extern pcap_t *descr;

//Funcion para abrir la ventana de abrir/guardar sesion.
//Parametros:
//	savemode:El modo en el que se abrirá la ventana.
//			savemode 1:Abrir sesion.
//			savemode 2:Guardar sesion.
void winsave_open(char savemode)
{	

    GtkWidget *fixed;
    GtkWidget *scrolled;
    char *str_temp;
    
    winsave_mode=savemode;
    
    //Si el usuario ha elegido guardar, se comprueba antes si hay algo 
    //  que guardar.
    if (savemode==2){
	//Si no hay paquetes en memoria no hay nada que guardar.
	if (pkt_mem_list_length()==0){
	    //No hay nada que guardar
	    wininfor_msg("No hay nada que guardar.");
	    return;
	}
    }    
	//Se obtiene el directorio raiz a partir de la variable de entorno $HOME
	str_temp=getenv("HOME"); //Tiene que acabar en "/"


	if(str_temp==NULL){
	    actua_dir=malloc(2);
	    sprintf(actua_dir,"/");
	}else{	
	    //Se pone "/" al final.
	    actua_dir=malloc(strlen(str_temp)+2);
	    sprintf(actua_dir,str_temp);
	    actua_dir[strlen(actua_dir)+1]='\0';
	    actua_dir[strlen(actua_dir)]='/';
	}

    if (win_save==NULL){
	//Si aun no se ha abierto la ventana de grabar
	win_save=create_win_save();
	fixed=lookup_widget(win_save,"fixed5");
	winsave_entry=lookup_widget(fixed,"entry1");
	scrolled=lookup_widget(fixed,"scrolledwindow3");
	winsave_label=lookup_widget(fixed,"label19");
	winsave_clist=lookup_widget(scrolled,"clist2");
    }

    if (savemode==1) gtk_label_set_text(GTK_LABEL(winsave_label),"ABRIR");
    else gtk_label_set_text(GTK_LABEL(winsave_label),"GUARDAR");

    gtk_widget_show_all(win_save);
    winsave_open_fileordir(actua_dir);
}

//Funcion que oculta la ventana de abrir/guardar.
void winsave_close()
{
    gtk_widget_hide_all(win_save);
}

//Se le pasa un directorio o un archivo. Si es un archivo lo abre,
//  y si es un directorio tambien.
//  Devuelve 0 si fue bien, 1 si fue mal
//Parametros:
//	dir_str:Cadena con el directorio/archivo a abrir.
int winsave_open_fileordir(char *dir_str)
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat buffer;
    char *str_dir[1];

    //Se obtienen atributos del archivo/directorio
    stat(dir_str,&buffer);

    if (S_ISDIR(buffer.st_mode)){ 
	//Si es un directorio
	if ( (dirp=opendir(dir_str))==NULL){
	    winerror_msg("No se puede abrir directorio.");
	    return 1;
        }
	//Se actualiza la variable global actua_dir con el nuevo directorio
	actua_dir=(char *)malloc(strlen(dir_str)+1);
	strcpy(actua_dir,dir_str);
	
	gtk_clist_clear(GTK_CLIST(winsave_clist));
	
	//Se actualiza la lista con los nombres de archivos/directorios del nuevo
	// directorio introducido.
	while ( (direntp=readdir(dirp))!=NULL ){
	    str_dir[0]=direntp->d_name;
	    gtk_clist_append(GTK_CLIST(winsave_clist),str_dir);
	}	    
    }else{

	//Si es una ruta a un archivo
	winsave_open_file(dir_str);
    }    
    return 0;
}

//Se le pasa una ruta de un archivo (puede ser valida o no)  y la funcion hará
// lo necesario para abrirlo/guardarlo correctamente en caso de ser archivo.
//Parametros:
//	dir_str:Ruta al archivo a abrir.
void winsave_open_file(char *dir_str)
{    
    pcap_dumper_t *f;
    int cnt,length;
    GList *run_list;
    struct packet_list_node *node;
    FILE *openfile;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    //Se quita el ultimo caracter (/) para tener una ruta de fichero valida
    if (dir_str[strlen(dir_str)-1]=='/'){
	dir_str[strlen(dir_str)-1]='\0';
    }

    if (winsave_mode==1){
	//Si hay que abrir
        if ( (save_descr=pcap_open_offline(dir_str,errbuf))==NULL){
    	    //Algo fue mal leyendo el archivo
	    winerror_msg("Error leyendo archivo de paquetes.");
	    return;
	}

	//Se actualiza el descriptor de sesion abierto
	wincap_set_pcap_descr(save_descr);

	//Antes de cargar en memoria los paquetes del archivo,se borran los que hay
	// en caso de que este esa opcion avanzada seleccionada.
	if (winoptions_option_reset()){
	    pkt_mem_list_reset();
	}
	
	//Se llama a pkt_callback_offline que cargara en memoria los paquetes
	//  del fichero.    
	if(pcap_loop(save_descr,-1,pkt_callback_offline,NULL)==-1){
	    sprintf(str_buf_run,"Error leyendo una trama:%s",pcap_geterr(save_descr));
	    winerror_msg(str_buf_run);
	    return;
	}

	//Se cierra y actuliza lista de paquetes.
	winsave_close();
	winini_update_packet_mem_list();

    }else{
	//Hay que guardar en el archivo

	//Primero comprobar que ese archivo no existe y si existe dar 
	// un aviso al usuario de si quiere sobreescribir.
	openfile=fopen(dir_str,"r");
	if (openfile!=NULL){
	    winsure_msg("¿Esta seguro de sobreescribir ese fichero?");
	    if (winsure_answer()==0){
		fclose(openfile);
		return;
	    }
	}
	
	//Se obtiene el descriptor de sesion actualmente abierto para
	// poder guardar la sesion
	save_descr=wincap_get_pcap_descr();
	
	if ((f=pcap_dump_open(save_descr,dir_str))==NULL){
	    //Error al abrir para escribir.
	    sprintf(str_buf_run,"Error al intentar abrir para escribir:%s",pcap_geterr(save_descr));
	    winerror_msg(str_buf_run);
	    return;
	}
	
	length=pkt_mem_list_length();
	
	//Guardando
	if (length>0){
	    for(cnt=0;cnt!=length;cnt++){
		run_list=pkt_mem_list_nth(cnt);
		node=(struct packet_list_node *)run_list->data;
		pcap_dump(f,node->pkthdr,node->pkt);
	    }
	}
	pcap_dump_close(f);
	winsave_close();	
    }
}


//Callback que se llama para cargar en memoria los datos de un archivo.
void pkt_callback_offline(u_char *args,const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    pkt_mem_list_append(pkthdr,packet);

}


//Funcion llamada cuando se selecciona un archivo/dir de la lista.
void winsave_select_file(gint row)
{
    char *read_dir;

    gtk_clist_get_text(GTK_CLIST(winsave_clist),row,0,&read_dir);
    gtk_entry_set_text(GTK_ENTRY(winsave_entry),read_dir);

}


//Funcion llamada cuando se pulsa el boton de Abrir/Guardar
void winsave_open_button()
{
    char *dir,*file;

    //Se obtiene el nb del archivo/directorio introducida por el usuario 
    file=gtk_entry_get_text(GTK_ENTRY(winsave_entry));

    if (strlen(file)>0){
	//Si no es un nb vacio	
	if (file[0]!='/'){
	    //En caso de no ser una ruta global,
	    //se añade el nb del archivo/directorio al final de la ruta actual.
	    dir=malloc(strlen(actua_dir)+strlen(file)+2);
	    strcpy(dir,actua_dir);	
	    strcat(dir,file);
	    strcat(dir,"/");
	}else{
	    //Si es una ruta global
	    dir=malloc(strlen(file)+2);
	    strcpy(dir,file);	
	    strcat(dir,"/");
	}

	winsave_open_fileordir(dir);
	free(dir);
    }else{
	wininfor_msg("Debe de especificar el nombre del archivo/directorio.");
    }
}