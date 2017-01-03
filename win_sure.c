//win_sure.c 
//----------

//*********************************************************************************
//Ventana utilizada para operaciones que son necesarios que el usuario las 
//  confirme antes de hacerlas.
//  La manera de usarla será llamando a win_suremsg(msg) y mirar la variable global
//  sure_answer donde estara el resultado:
//	1:Si el usuario acepta
//	0:Si el usuario cancela
//*********************************************************************************

#include <gtk/gtk.h>
#include "misc.h"
#include "win_sure.h"
#include "interface.h"
#include "support.h"

//Variables globales
static GtkWidget *win_sure=NULL;
static char sure_answer;		//Variable donde se almacenara la respuesta de la ventana.

//Funcion que muestra una ventana donde sale un mensaje y 2 opciones a elegir por
//  el usuario. Bloquea la ejecucion hasta que el usuario elige una respuesta.
//Parametros:
//	message:Mensaje/Pregunta a mostrar
void winsure_msg(char *message)
{	
    
    GtkWidget *label,*fixed;    
    
    //Si todavia no se ha creado la ventana, se crea.
    if (win_sure==NULL){
	//Se crea la ventana aseguradora en caso de que aun no se haya creado
	win_sure=create_win_sure();
    }
    
    sure_answer=2;
    
    fixed=lookup_widget(win_sure,"fixed6");
    label=lookup_widget(fixed,"label20");
    
    gtk_widget_show_all(win_sure);    
        
    gtk_label_set_text(GTK_LABEL(label),message);
    
    //Se llama a gtk_main() para que el proceso que la llamo tenga que esperar
    //	a una respuesta.
    gtk_main();

}

//Funcion llamada cuando el usuario confirma la pregunta de la ventana.
void winsure_accept()
{

    sure_answer=1;
    gtk_main_quit();
    winsure_close();

}

//Funcion llamada cuando el usuario cancela la pregunta de la ventana.
void winsure_cancel()
{

    sure_answer=0;
    gtk_main_quit();
    winsure_close();

}

//Funcion llamada para ocultar la ventana.
void winsure_close()
{
    gtk_widget_hide_all(win_sure);
}

char winsure_answer()
{
    return sure_answer;
}