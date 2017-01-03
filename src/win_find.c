//win_find.c
//----------

#include <gtk/gtk.h>
#include <string.h>
#include "misc.h"
#include  "support.h"
#include "win_find.h"
#include "interface.h"
#include "win_error.h"
#include "pkt_mem_list.h"
#include "win_ini.h"
#include "win_infor.h"

//Variables gloables
static GtkWidget *win_find=NULL;

//Funcion que habre/crea la ventana de buscar.
void winfind_open()
{	
    //Primero se comprueba que hay tramas sobre las que poder buscar.
    if(pkt_mem_list_length()==0){
	wininfor_msg("No hay tramas para buscar.");
	return;
    }
    
    //Si la ventana aun no se ha creado, se crea. Si se había creado antes
    //  simplemente se enseña.
    if (win_find==NULL){
	win_find=create_win_find();
    }    
    
    gtk_widget_show_all(win_find);
}


//Funcion a la cual se le llama siempre para cerrar.
void winfind_close()
{
    //Cerrando ventana.
    gtk_widget_hide_all(win_find);
}


//Funcion llamada al apretar el boton de realizar la busqueda  o 
//  cuando se llaama a 'Buscar siguiente trama'
//El mode especifica como se ha de buscar, si desde el principio, o si desde
//  la ultima búsqueda
//Parametros:
//	Mode:	1:Desde el principio
//  		2:Desde la ultima búsqueda
//		El mode 2 se usa cuando se aprieta a 'Buscar siguiente trama'
void winfind_go(int mode)
{
    GtkWidget *fixed;
    GtkWidget *entry_srcaddr,*entry_destaddr,*entry_proto;
    gchar *srcaddr,*destaddr,*proto;
    char *clist_srcaddr,*clist_destaddr,*clist_proto;
    guint cnt,row_to_begin;
    gchar cmp1,cmp2,cmp3;
    
    if (win_find==NULL){
	wininfor_msg("No se ha realizado ninguna búsqueda antes.");
	return;
    }
    if (pkt_mem_list_length()==0){
	wininfor_msg("No hay tramas para buscar.");
	return;
    }
    
    fixed=lookup_widget(win_find,"fixed10");
    entry_srcaddr=lookup_widget(win_find,"entry_srcaddr");
    entry_destaddr=lookup_widget(win_find,"entry_destaddr");
    entry_proto=lookup_widget(win_find,"entry_proto");
    
    srcaddr=gtk_entry_get_text(GTK_ENTRY(entry_srcaddr));
    destaddr=gtk_entry_get_text(GTK_ENTRY(entry_destaddr));
    proto=gtk_entry_get_text(GTK_ENTRY(entry_proto));
    
    if ((strcmp(srcaddr,"")==0)&&(strcmp(destaddr,"")==0)&&(strcmp(proto,"")==0)){
	wininfor_msg("Debe rellenar algun campo para poder realizar la busqueda.");
	return;
    }
    
    //Dependiendo del modo se empezara a recorrer la lista desde el principio
    //  o desde la ultima busqueda.
    if (mode==1) row_to_begin=0;
    else row_to_begin=winini_get_row_selected()+1;
    
    for(cnt=row_to_begin;cnt!=pkt_mem_list_length();cnt++){
	//Se recorre toda la lista de paquetes y se van comparando uno a uno
	//  con las cadenas metidas por el usuario.
	winini_clist_get_text(cnt,1,&clist_srcaddr);
	winini_clist_get_text(cnt,2,&clist_destaddr);
	winini_clist_get_text(cnt,3,&clist_proto);
	
	
	if(strcmp(srcaddr,"")!=0){ 
	    //Si se ha introducido algo se compara.	
	    if (strcmp(clist_srcaddr,"")!=0){
		//Si ninguna de las cadenas direccion origen estan vacias..
		if (strstr(clist_srcaddr,srcaddr)!=NULL){
		    //Si la primera cadena origen coincide con la buscada
		    cmp1=1;
		}else cmp1=0;
	    }else cmp1=0; //Si en la lista esta vacia, no coinciden.
	}else cmp1=1; //Si no se ha introducido nada por el usuario, coincien.
	
	//Si la cadena origen coincide con la introducida por el usuario o
	// no se ha introducido nada, cmp1 será 1. Si cmp1 no es 1, no se podrá
	// seguir con la busqueda.
	
	if (cmp1==1){
	    if(strcmp(destaddr,"")!=0){ 
		//Se pasa a la segunda comparacion.
	        //Si se ha introducido algo se compara.	
		if (strcmp(clist_destaddr,"")!=0){
		    //Si ninguna de las cadenas direccion origen estan vacias..
		    if (strstr(clist_destaddr,destaddr)!=NULL){
			//Si la primera cadena origen coincide
			cmp2=1;
		    }else cmp2=0;
		}else cmp2=0;
	    }else cmp2=1; 
	}else cmp2=0;

	//Si la cadena destino coincide con la introducida por el usuario o
	// no se ha introducido nada, cmp2 será 1.Si cmp2 y cmp2 no son 1, no se
	// podrá seguir con la búsqueda.
	
	if(cmp2==1){
	    if(strcmp(proto,"")!=0){ 
		//Si se ha introducido algo se compara.	
		//Se pasa a la tercera comparacion
		if (strcmp(clist_proto,"")!=0){
		    //Si ninguna de las cadenas direccion origen estan vacias..
		    if (strstr(clist_proto,proto)!=NULL){
			//Si la primera cadena origen coincide
			cmp3=1;
		    }else cmp3=0;
		}else cmp3=0;
	    }else cmp3=1;
	}else cmp3=0;
	
	if (cmp3==1){
	    //Si cmp3 es 1, quiere decir que tambien lo son cmp1 y cmp2 por lo que
	    //  coinciden, así que se sale del for y se selecciona la fila
	    // de la lista seleccionada
	    break;
	}
	
    }
    
    if (cmp3==1){
	//Se actualiza el valor de la ultima fila seleccionada y se selecciona
	// la trama adecuada de la lista.
	//winini_set_row_selected(cnt);
	winini_clist_select_row(cnt);
	//winini_clist_moveto(cnt);

	gtk_widget_hide_all(win_find);
    }else{
	wininfor_msg("No se han encontrado tramas.");
    }
}
