//win_options.c
//-------------

#include <gtk/gtk.h>
#include "misc.h"
#include "support.h"
#include "win_options.h"
#include "interface.h"
#include "win_ini.h"

//Variables globales
static GtkWidget *win_options=NULL;
static gchar option_ip=1;
static gchar option_tcp=0;
static gchar option_ascii=0;
static gchar option_reset=1;

//Funcion que crea/abre la ventana de opciones avanzadas de captura.
void winoptions_open()
{	
    
    GtkWidget *fixed;
    GtkWidget *checkbutton_ip;
    GtkWidget *checkbutton_tcp;
    GtkWidget *checkbutton_ascii;
    GtkWidget *checkbutton_reset;
    
    if (win_options==NULL){	
	//Si no esta creada, se crea la ventana de opciones
	win_options=create_win_options();
    }	
    
    fixed=lookup_widget(win_options,"fixed8");
    checkbutton_ip=lookup_widget(fixed,"checkbutton_ip");
    checkbutton_tcp=lookup_widget(fixed,"checkbutton_tcp");
    checkbutton_ascii=lookup_widget(fixed,"checkbutton_ascii");
    checkbutton_reset=lookup_widget(fixed,"checkbutton_reset");
	
    //Se actualizan los checkbuttons con los datos de las variables globales    
    if (option_ip==1) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_ip),1);
    else gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_ip),0);

    if (option_tcp==1) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_tcp),1);
    else gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_tcp),0);

    if (option_ascii==1) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_ascii),1);
    else gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_ascii),0);

    if (option_reset==1) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_reset),1);
    else gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton_reset),0);
    
    gtk_widget_show_all(win_options);
}

//Funcion que actualiza las variables globales de opciones y cierra la ventana.
void winoptions_accept()
{
    GtkWidget *fixed;
    GtkWidget *checkbutton_ip;
    GtkWidget *checkbutton_tcp;
    GtkWidget *checkbutton_ascii;
    GtkWidget *checkbutton_reset;

    fixed=lookup_widget(win_options,"fixed8");
    checkbutton_ip=lookup_widget(fixed,"checkbutton_ip");
    checkbutton_tcp=lookup_widget(fixed,"checkbutton_tcp");
    checkbutton_ascii=lookup_widget(fixed,"checkbutton_ascii");
    checkbutton_reset=lookup_widget(fixed,"checkbutton_reset");
    
    //Primero actualizar datos
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_ip))) option_ip=1;
    else option_ip=0;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_tcp))) option_tcp=1;
    else option_tcp=0;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_ascii))) option_ascii=1;
    else option_ascii=0;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton_reset))) option_reset=1;
    else option_reset=0;
    
    winoptions_cancel();

    //Se actualiza lista de paquetes.
    winini_update_packet_mem_list();
    
}

//Funcion que oculta la venana de error, sin actualizar datos.
void winoptions_cancel()
{
    gtk_widget_hide_all(win_options);
}

char winoptions_option_ip()
{
    return option_ip;
}

char winoptions_option_tcp()
{
    return option_tcp;
}

char winoptions_option_ascii()
{
    return option_ascii;
}

char winoptions_option_reset()
{
    return option_reset;
}