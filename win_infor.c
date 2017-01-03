//win_infor.c
//-----------

#include <gtk/gtk.h>
#include "support.h"
#include "misc.h"
#include "win_infor.h"
#include "interface.h"

//Variables globales
static GtkWidget *win_infor=NULL;

//Funcion que saca por pantalla un mensage de informacion y no deja continuar
//  hasta que no se presiona el boton de aceptar.
//Parametros:
//	message:Mensaje que saldra en la ventana.
void wininfor_msg(char *message)
{	

    GtkWidget *label,*fixed;
    
    //Si todavía no se ha creado la ventana, se creara la ventana.
    
    if (win_infor==NULL){
	win_infor=create_win_infor();
	
    }
    //Si ya estaba creada la ventana, simplemente se enseñara
    
    fixed=lookup_widget(win_infor,"fixed13");
    label=lookup_widget(fixed,"label69");

    gtk_widget_show_all(win_infor);    

    gtk_label_set_text(GTK_LABEL(label),message);

    //Se hace que el proceso que ha llamado la funcion tenga que esperar
    //hasta que la ventana sea cerrada.
    gtk_main();
}


//Se le llama siempre para cerrar.
void wininfor_close()
{
    //Cerrando ventana.
    gtk_widget_hide_all(win_infor);
    gtk_main_quit();
}