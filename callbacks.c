//callbacks.c
//-----------
   
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <pcap.h>
#include <sys/types.h>
#include <signal.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "misc.h"
#include "win_delfil.h"
#include "win_infor.h"
#include "win_about.h"
#include "win_find.h"
#include "win_goto.h"
#include "win_ini.h"
#include "win_sure.h"
#include "win_options.h"
#include "win_save.h"
#include "win_esta.h"
#include "pkt_mem_list.h"
#include "win_error.h"
#include "win_cap.h"

void
on_archivo1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

//Salir de la aplicacion.
gboolean
on_win_ini_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    //Saliendo de la aplicación
    
    winsure_msg("¿Desea cerrar la aplicación?");
    if (winsure_answer()){
	//Primero se libera la memoria de paquetes.
	pkt_mem_list_reset();
	gtk_main_quit();
    }
    return TRUE;
    
    
}

//Boton de abrir ventana de win_options
void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    wincap_ini();
}


//Boton de empezar a capturar de la ventana win_cap
void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    
    wincap_start_capture();

}


//Se pierde el focus del cuadro de texto de obtener el dispositivo
//Por lo que hay q actualizar la IP y la Mascara
gboolean
on_entry_dev_focus_out_event           (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
    wincap_update_ip_mask();
    return FALSE;
}


//Boton de parar captura (solo puede ser presionado en caso de que se este capturando)
void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

    wincap_stop_capture();

}


void
on_check_numofpkt_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

    wincap_check_numofpkt_toggled();

}


void
on_check_maxtime_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    wincap_check_maxtime_toggled();
}


void
on_check_maxbytes_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

    wincap_check_maxbytes_toggled();

}


//Delete evente de win_cap
gboolean
on_win_cap_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
 //Se llama a la funcion de cerrar ventana de capwin, la cual solo cerrara si no esta en proceso de captura. 
  wincap_close_window();   
  
  //No hay que cerrar desde aqui, si no q lo debe cerrar el hilo.
  //Por eso se devuelve true.
  return TRUE; 
}


//Señal emitida cuando se selecciona un paquete de la packet list
void
on_clist1_select_row                   (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    
    winini_row_selected(row);
}


//Boton de ok de la ventana win_error message
void
on_button_ok_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    winerror_close();
}

void
on_abrir_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winsave_open(1);
}


void
on_guardar_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winsave_open(2);
}


//Boton de salir de menu
void
on_salir_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    on_win_ini_delete_event(NULL,NULL,NULL);
}


//Boton de aceptar de win_save
void
on_button_aceptar_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    winsave_open_button();
}

//Menú->Nuevo
void
on_nuevo1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winini_delete_all_rows();
}


//Boton cancelar de la win_save
void
on_button_cancelar_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
    winsave_close();
}


//Presionado boton aceptar de win_sure
void
on_surebutton_aceptar_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    winsure_accept();
}


//Presionado boton cancelar de win_sure
void
on_surebutton_cancelar_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    winsure_cancel();
}


//Seleccionada fila de la lista de archivos de la pantalla de abrir
void
on_clist2_select_row                   (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    winsave_select_file(row);
}


void
on_edit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

//Menu->Capturar->Empezar
void
on_empezar1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    wincap_ini();
}

//Menú->Capturar->Opciones avanzadas
void
on_opciones_avanzadas1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winoptions_open();
}

//Presionado boton aceptar de la ventana de opciones avanzadas
void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    winoptions_accept();
}


//Presionado boton cancelar de la ventana de opciones avanzadas
void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    winoptions_cancel();
}




//Delete event de la ventana win_error
gboolean
on_win_error_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    winerror_close();
    return TRUE;
}


//Delete event de la ventana win_save
gboolean
on_win_save_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  winsave_close();
  return TRUE;
}

//Delete event de la ventana win_sure
gboolean
on_win_sure_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
  winsure_close();
  return FALSE;
}

//Menu->Edit->Eliminar paquete
void
on_eliminar_paquete1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winini_delete_row_selected();
}


void
on_acerca_de1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winabout_open();
}


//Se cambia de pagina en el notebook
void
on_notebook_switch_page                (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        gint             page_num,
                                        gpointer         user_data)
{
    if (page_num==1){
	//Mostrar estadísticas.
	winesta_refresh();
    }
}


void
on_eliminar_todos_paquetes1_activate   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winini_delete_all_rows();
}


gboolean
on_win_goto_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    wingoto_close();
    return TRUE;
}


void
on_button_goto_go_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    wingoto_go();
}


void
on_button_goto_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    wingoto_close();
}


void
on_ir_a_trama1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    wingoto_open();
}


gboolean
on_win_find_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    winfind_close();
    return TRUE;
}


void
on_button_find_go_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    winfind_go(1);
}


void
on_button_find_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    winfind_close();
}


void
on_buscar_trama1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winfind_open();
}


void
on_buscar_siguiente_trama1_activate    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    winfind_go(2);
}


gboolean
on_win_options_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    winoptions_cancel();
    return TRUE;
}


gboolean
on_win_about_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    winabout_close();
    return TRUE;
}


void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    winabout_close();
}



gboolean
on_win_delfil_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    windelfil_close();
    return TRUE;
}


void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    windelfil_close();
}


//Boton de realizar la eliminacion por filtro
void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    windelfil_start();
}


void
on_eliminar_tramas_por_filtro1_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    windelfil_open();
}


gboolean
on_win_infor_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
    wininfor_close();
    return TRUE;
}


void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    wininfor_close();
}
