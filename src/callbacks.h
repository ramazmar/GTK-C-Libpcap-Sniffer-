#include <gtk/gtk.h>


void
on_archivo1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data); 

void
on_window1_show                        (GtkWidget       *widget,
                                        gpointer         user_data);

gboolean
on_window1_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button1_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_window2_show                        (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_entry_dev_changed                   (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_entry_dev_focus_in_event            (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_entry_dev_focus_out_event           (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_numofpkt_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_maxtime_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_check_maxbytes_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_window2_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_window2_button_press_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_window2_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_clist1_select_row                   (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_ok_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_reset_button_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_del_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_abrir_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_guardar_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_salir_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_aceptar_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_clist2_select_row                   (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_save_win_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_nuevo1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button_cancelar_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_surebutton_aceptar_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_surebutton_cancelar_clicked         (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_surewin_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_clist2_select_row                   (GtkCList        *clist,
                                        gint             row,
                                        gint             column,
                                        GdkEvent        *event,
                                        gpointer         user_data);

GtkDirectionType
on_fixed7_focus                        (GtkContainer    *container,
                                        GtkDirectionType direction,
                                        gpointer         user_data);

void
on_notebook1_switch_page               (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        gint             page_num,
                                        gpointer         user_data);

void
on_edit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_empezar1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_opciones_avanzadas1_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_win_ini_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_win_cap_delete_event                (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_error_win_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_win_error_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_win_save_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_win_sure_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_eliminar_paquete1_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_acerca_de1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_notebook_switch_page                (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        gint             page_num,
                                        gpointer         user_data);

void
on_eliminar_todos_paquetes1_activate   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_win_goto_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_goto_go_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_goto_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_ir_a_trama1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_win_find_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button_find_go_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_find_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buscar_trama1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_buscar_siguiente_trama1_activate    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_win_options_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_win_about_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button8_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_check_maxtime_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_win_delfil_delete_event             (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button9_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_button10_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_eliminar_tramas_por_filtro1_activate
                                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_win_infor_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_button11_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_stopchild_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_win_cap_draw                        (GtkWidget       *widget,
                                        GdkRectangle    *area,
                                        gpointer         user_data);

void
on_win_ini_draw                        (GtkWidget       *widget,
                                        GdkRectangle    *area,
                                        gpointer         user_data);

gboolean
on_win_ini_configure_event             (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

void
on_win_ini_drag_data_get               (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data);
