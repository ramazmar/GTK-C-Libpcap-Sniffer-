 //win_about.c
//-----------

#include <gtk/gtk.h>
#include "interface.h"
#include "win_about.h"

//Variables globales
static GtkWidget *win_about=NULL;

//Funcion para abrir la ventana Acerca de..
void winabout_open()
{	

    if (win_about==NULL){
	win_about=create_win_about();
	
    }
    gtk_widget_show_all(win_about);
}


//Se le llama siempre para cerrar.
void winabout_close()
{
    //Cerrando ventana de acerca.
    gtk_widget_hide_all(win_about);
}