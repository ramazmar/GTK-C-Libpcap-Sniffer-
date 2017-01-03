//win_error.c
//-----------

#include <gtk/gtk.h>
#include "misc.h"
#include "win_error.h"
#include "interface.h"
#include "support.h"

//Variables globales
static GtkWidget *win_error=NULL;

//Funcion que nos saca por pantalla un mensage de error y no deja continuar
//  hasta que no se presiona el boton de aceptar.
//Parametros:
//	message:Mensage de error que saldra en la ventana.
void winerror_msg(char *message)
{	

    GtkWidget *label_error,*fixed;
    
    //Si todavía no se ha creado la ventana de error, se creara la ventana.
    
    if (win_error==NULL){
	win_error=create_win_error();
	
    }
    //Si ya estaba creada la ventana, simplemente se mostrara
    
    fixed=lookup_widget(win_error,"fixed4");
    label_error=lookup_widget(fixed,"label_error");

    gtk_widget_show_all(win_error);    

    gtk_label_set_text(GTK_LABEL(label_error),message);

    //Se hace que el proceso que ha llamado la funcion tenga que esperar
    //hasta que la ventana sea cerrada.
    gtk_main();
}


//Se le llama siempre para cerrar.
void winerror_close()
{
    //Cerrando ventana de error.
    gtk_widget_hide_all(win_error);
    gtk_main_quit();
}