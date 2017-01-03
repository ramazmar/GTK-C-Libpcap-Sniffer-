//win_goto.c
//----------

#include <gtk/gtk.h>
#include <stdlib.h>
#include "support.h"
#include "misc.h"
#include "win_goto.h"
#include "interface.h"
#include "pkt_mem_list.h"
#include "win_error.h"
#include "win_ini.h"
#include "win_goto.h"


//Variables globales
static GtkWidget *win_goto=NULL;

//Funcion para abrir/crear la ventana de ir a trama.
void wingoto_open()
{	

    if (pkt_mem_list_length()==0){
	wininfor_msg("No hay tramas para buscar.");
	return;
    }
    
    if (win_goto==NULL){
	win_goto=create_win_goto();	
    }    
    
    gtk_widget_show_all(win_goto);
    // Se hace que el proceso que ha llamado la funcion tenga que esperar
    //hasta que la ventana sea cerrada.
}


//Se le llama siempre para cerrar.
void wingoto_close()
{
    //Cerrando ventana de ir a.
    gtk_widget_hide_all(win_goto);
}

//Funcion que lleva a una trama determinada a partir de su campo id.
void wingoto_go()
{
    GtkWidget *fixed;
    GtkWidget *spinbutton_id;
    int id_to_go;

    fixed=lookup_widget(win_goto,"fixed9");
    spinbutton_id=lookup_widget(fixed,"spinbutton_gotonum");    

    id_to_go=atoi(gtk_entry_get_text(GTK_ENTRY(spinbutton_id)));

    if (id_to_go>pkt_mem_list_length()){
	wininfor_msg("No se puede ir a esa trama porque no existe.");
	return;
    }
    winini_clist_select_row(id_to_go-1);
    gtk_widget_hide_all(win_goto);
}
