#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

GtkWidget*
create_win_ini (void)
{
  GtkWidget *win_ini;
  GtkWidget *table1;
  GtkWidget *menubar1;
  GtkWidget *archivo1;
  GtkWidget *archivo1_menu;
  GtkAccelGroup *archivo1_menu_accels;
  GtkWidget *nuevo1;
  GtkWidget *separator2;
  GtkWidget *abrir;
  GtkWidget *guardar;
  GtkWidget *separator1;
  GtkWidget *salir;
  GtkWidget *edit1;
  GtkWidget *edit1_menu;
  GtkAccelGroup *edit1_menu_accels;
  GtkWidget *eliminar_paquete1;
  GtkWidget *eliminar_todos_paquetes1;
  GtkWidget *eliminar_tramas_por_filtro1;
  GtkWidget *separator3;
  GtkWidget *ir_a_trama1;
  GtkWidget *buscar_trama1;
  GtkWidget *buscar_siguiente_trama1;
  GtkWidget *capturar1;
  GtkWidget *capturar1_menu;
  GtkAccelGroup *capturar1_menu_accels;
  GtkWidget *empezar1;
  GtkWidget *opciones_avanzadas1;
  GtkWidget *ayuda1;
  GtkWidget *ayuda1_menu;
  GtkAccelGroup *ayuda1_menu_accels;
  GtkWidget *acerca_de1;
  GtkWidget *notebook;
  GtkWidget *table2;
  GtkWidget *vpaned1;
  GtkWidget *scrolledwindow1;
  GtkWidget *clist1;
  GtkWidget *label4;
  GtkWidget *label5;
  GtkWidget *label6;
  GtkWidget *label7;
  GtkWidget *scrolledwindow2;
  GtkWidget *viewport1;
  GtkWidget *tree1;
  GtkWidget *label1;
  GtkWidget *fixed7;
  GtkWidget *label21;
  GtkWidget *label22;
  GtkWidget *label23;
  GtkWidget *label_estafin;
  GtkWidget *label26;
  GtkWidget *label_estanumtram;
  GtkWidget *hseparator2;
  GtkWidget *label34;
  GtkWidget *label36;
  GtkWidget *label_estalaf;
  GtkWidget *label38;
  GtkWidget *label_estaltf;
  GtkWidget *label35;
  GtkWidget *scrolledwindow4;
  GtkWidget *clist3;
  GtkWidget *label29;
  GtkWidget *label30;
  GtkWidget *label31;
  GtkWidget *label32;
  GtkWidget *label33;
  GtkWidget *label51;
  GtkWidget *label52;
  GtkWidget *label_estaiaf;
  GtkWidget *label53;
  GtkWidget *label_estaitf;
  GtkWidget *label54;
  GtkWidget *scrolledwindow5;
  GtkWidget *clist4;
  GtkWidget *label43;
  GtkWidget *label44;
  GtkWidget *label45;
  GtkWidget *label46;
  GtkWidget *label47;
  GtkWidget *label_estainicio;
  GtkWidget *label2;
  GtkAccelGroup *accel_group;

  accel_group = gtk_accel_group_new ();

  win_ini = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_object_set_data (GTK_OBJECT (win_ini), "win_ini", win_ini);
  gtk_widget_set_uposition (win_ini, 0, 0);
  gtk_window_set_title (GTK_WINDOW (win_ini), "           ");
  gtk_window_set_policy (GTK_WINDOW (win_ini), TRUE, TRUE, FALSE);

  table1 = gtk_table_new (2, 1, FALSE);
  gtk_widget_ref (table1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "table1", table1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (table1);
  gtk_container_add (GTK_CONTAINER (win_ini), table1);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_ref (menubar1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "menubar1", menubar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (menubar1);
  gtk_table_attach (GTK_TABLE (table1), menubar1, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  archivo1 = gtk_menu_item_new_with_label ("Archivo");
  gtk_widget_ref (archivo1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "archivo1", archivo1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (archivo1);
  gtk_container_add (GTK_CONTAINER (menubar1), archivo1);

  archivo1_menu = gtk_menu_new ();
  gtk_widget_ref (archivo1_menu);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "archivo1_menu", archivo1_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (archivo1), archivo1_menu);
  archivo1_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (archivo1_menu));

  nuevo1 = gtk_menu_item_new_with_label ("Nuevo");
  gtk_widget_ref (nuevo1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "nuevo1", nuevo1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (nuevo1);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), nuevo1);
  gtk_widget_add_accelerator (nuevo1, "activate", accel_group,
                              GDK_N, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  separator2 = gtk_menu_item_new ();
  gtk_widget_ref (separator2);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "separator2", separator2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (separator2);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), separator2);
  gtk_widget_set_sensitive (separator2, FALSE);

  abrir = gtk_menu_item_new_with_label ("Abrir sesion");
  gtk_widget_ref (abrir);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "abrir", abrir,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (abrir);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), abrir);
  gtk_widget_add_accelerator (abrir, "activate", accel_group,
                              GDK_A, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  guardar = gtk_menu_item_new_with_label ("Guardar sesion");
  gtk_widget_ref (guardar);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "guardar", guardar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (guardar);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), guardar);
  gtk_widget_add_accelerator (guardar, "activate", accel_group,
                              GDK_G, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  separator1 = gtk_menu_item_new ();
  gtk_widget_ref (separator1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "separator1", separator1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (separator1);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), separator1);
  gtk_widget_set_sensitive (separator1, FALSE);

  salir = gtk_menu_item_new_with_label ("Salir");
  gtk_widget_ref (salir);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "salir", salir,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (salir);
  gtk_container_add (GTK_CONTAINER (archivo1_menu), salir);
  gtk_widget_add_accelerator (salir, "activate", accel_group,
                              GDK_X, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  edit1 = gtk_menu_item_new_with_label ("Trama");
  gtk_widget_ref (edit1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "edit1", edit1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (edit1);
  gtk_container_add (GTK_CONTAINER (menubar1), edit1);

  edit1_menu = gtk_menu_new ();
  gtk_widget_ref (edit1_menu);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "edit1_menu", edit1_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (edit1), edit1_menu);
  edit1_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (edit1_menu));

  eliminar_paquete1 = gtk_menu_item_new_with_label ("Eliminar trama");
  gtk_widget_ref (eliminar_paquete1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "eliminar_paquete1", eliminar_paquete1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (eliminar_paquete1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), eliminar_paquete1);
  gtk_widget_add_accelerator (eliminar_paquete1, "activate", accel_group,
                              GDK_E, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  eliminar_todos_paquetes1 = gtk_menu_item_new_with_label ("Eliminar todas las tramas");
  gtk_widget_ref (eliminar_todos_paquetes1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "eliminar_todos_paquetes1", eliminar_todos_paquetes1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (eliminar_todos_paquetes1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), eliminar_todos_paquetes1);
  gtk_widget_add_accelerator (eliminar_todos_paquetes1, "activate", accel_group,
                              GDK_T, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  eliminar_tramas_por_filtro1 = gtk_menu_item_new_with_label ("Eliminar tramas por filtro");
  gtk_widget_ref (eliminar_tramas_por_filtro1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "eliminar_tramas_por_filtro1", eliminar_tramas_por_filtro1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (eliminar_tramas_por_filtro1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), eliminar_tramas_por_filtro1);
  gtk_widget_add_accelerator (eliminar_tramas_por_filtro1, "activate", accel_group,
                              GDK_F, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  separator3 = gtk_menu_item_new ();
  gtk_widget_ref (separator3);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "separator3", separator3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (separator3);
  gtk_container_add (GTK_CONTAINER (edit1_menu), separator3);
  gtk_widget_set_sensitive (separator3, FALSE);

  ir_a_trama1 = gtk_menu_item_new_with_label ("Ir a trama");
  gtk_widget_ref (ir_a_trama1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "ir_a_trama1", ir_a_trama1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ir_a_trama1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), ir_a_trama1);
  gtk_widget_add_accelerator (ir_a_trama1, "activate", accel_group,
                              GDK_I, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  buscar_trama1 = gtk_menu_item_new_with_label ("Buscar trama");
  gtk_widget_ref (buscar_trama1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "buscar_trama1", buscar_trama1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (buscar_trama1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), buscar_trama1);
  gtk_widget_add_accelerator (buscar_trama1, "activate", accel_group,
                              GDK_B, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  buscar_siguiente_trama1 = gtk_menu_item_new_with_label ("Buscar siguiente trama");
  gtk_widget_ref (buscar_siguiente_trama1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "buscar_siguiente_trama1", buscar_siguiente_trama1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (buscar_siguiente_trama1);
  gtk_container_add (GTK_CONTAINER (edit1_menu), buscar_siguiente_trama1);
  gtk_widget_add_accelerator (buscar_siguiente_trama1, "activate", accel_group,
                              GDK_S, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  capturar1 = gtk_menu_item_new_with_label ("Capturar");
  gtk_widget_ref (capturar1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "capturar1", capturar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (capturar1);
  gtk_container_add (GTK_CONTAINER (menubar1), capturar1);

  capturar1_menu = gtk_menu_new ();
  gtk_widget_ref (capturar1_menu);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "capturar1_menu", capturar1_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (capturar1), capturar1_menu);
  capturar1_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (capturar1_menu));

  empezar1 = gtk_menu_item_new_with_label ("Empezar");
  gtk_widget_ref (empezar1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "empezar1", empezar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (empezar1);
  gtk_container_add (GTK_CONTAINER (capturar1_menu), empezar1);
  gtk_widget_add_accelerator (empezar1, "activate", accel_group,
                              GDK_C, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  opciones_avanzadas1 = gtk_menu_item_new_with_label ("Opciones avanzadas");
  gtk_widget_ref (opciones_avanzadas1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "opciones_avanzadas1", opciones_avanzadas1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (opciones_avanzadas1);
  gtk_container_add (GTK_CONTAINER (capturar1_menu), opciones_avanzadas1);
  gtk_widget_add_accelerator (opciones_avanzadas1, "activate", accel_group,
                              GDK_O, GDK_CONTROL_MASK,
                              GTK_ACCEL_VISIBLE);

  ayuda1 = gtk_menu_item_new_with_label ("Ayuda");
  gtk_widget_ref (ayuda1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "ayuda1", ayuda1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ayuda1);
  gtk_container_add (GTK_CONTAINER (menubar1), ayuda1);

  ayuda1_menu = gtk_menu_new ();
  gtk_widget_ref (ayuda1_menu);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "ayuda1_menu", ayuda1_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (ayuda1), ayuda1_menu);
  ayuda1_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (ayuda1_menu));

  acerca_de1 = gtk_menu_item_new_with_label ("Acerca de...");
  gtk_widget_ref (acerca_de1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "acerca_de1", acerca_de1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (acerca_de1);
  gtk_container_add (GTK_CONTAINER (ayuda1_menu), acerca_de1);

  notebook = gtk_notebook_new ();
  gtk_widget_ref (notebook);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "notebook", notebook,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (notebook);
  gtk_table_attach (GTK_TABLE (table1), notebook, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
  gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook), TRUE);

  table2 = gtk_table_new (24, 1, FALSE);
  gtk_widget_ref (table2);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "table2", table2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (table2);
  gtk_container_add (GTK_CONTAINER (notebook), table2);
  gtk_container_set_border_width (GTK_CONTAINER (table2), 1);

  vpaned1 = gtk_vpaned_new ();
  gtk_widget_ref (vpaned1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "vpaned1", vpaned1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vpaned1);
  gtk_table_attach (GTK_TABLE (table2), vpaned1, 0, 1, 0, 24,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
  gtk_paned_set_position (GTK_PANED (vpaned1), 257);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "scrolledwindow1", scrolledwindow1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow1);
  gtk_paned_pack1 (GTK_PANED (vpaned1), scrolledwindow1, FALSE, TRUE);

  clist1 = gtk_clist_new (4);
  gtk_widget_ref (clist1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "clist1", clist1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (clist1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), clist1);
  gtk_clist_set_column_width (GTK_CLIST (clist1), 0, 39);
  gtk_clist_set_column_width (GTK_CLIST (clist1), 1, 141);
  gtk_clist_set_column_width (GTK_CLIST (clist1), 2, 168);
  gtk_clist_set_column_width (GTK_CLIST (clist1), 3, 80);
  gtk_clist_column_titles_show (GTK_CLIST (clist1));

  label4 = gtk_label_new ("ID");
  gtk_widget_ref (label4);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label4", label4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label4);
  gtk_clist_set_column_widget (GTK_CLIST (clist1), 0, label4);

  label5 = gtk_label_new ("Direccion origen");
  gtk_widget_ref (label5);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label5", label5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label5);
  gtk_clist_set_column_widget (GTK_CLIST (clist1), 1, label5);

  label6 = gtk_label_new ("Direccion destino");
  gtk_widget_ref (label6);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label6", label6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label6);
  gtk_clist_set_column_widget (GTK_CLIST (clist1), 2, label6);

  label7 = gtk_label_new ("Protocolos");
  gtk_widget_ref (label7);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label7", label7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label7);
  gtk_clist_set_column_widget (GTK_CLIST (clist1), 3, label7);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow2);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "scrolledwindow2", scrolledwindow2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow2);
  gtk_paned_pack2 (GTK_PANED (vpaned1), scrolledwindow2, TRUE, TRUE);

  viewport1 = gtk_viewport_new (NULL, NULL);
  gtk_widget_ref (viewport1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "viewport1", viewport1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (viewport1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), viewport1);

  tree1 = gtk_tree_new ();
  gtk_widget_ref (tree1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "tree1", tree1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (tree1);
  gtk_container_add (GTK_CONTAINER (viewport1), tree1);

  label1 = gtk_label_new ("Tramas capturadas");
  gtk_widget_ref (label1);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label1", label1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label1);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 0), label1);
  gtk_widget_set_usize (label1, 140, -2);

  fixed7 = gtk_fixed_new ();
  gtk_widget_ref (fixed7);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "fixed7", fixed7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed7);
  gtk_container_add (GTK_CONTAINER (notebook), fixed7);

  label21 = gtk_label_new ("ESTADISTICAS DE CAPTURA");
  gtk_widget_ref (label21);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label21", label21,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label21);
  gtk_fixed_put (GTK_FIXED (fixed7), label21, 8, 8);
  gtk_widget_set_uposition (label21, 8, 8);
  gtk_widget_set_usize (label21, 240, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label21), TRUE);

  label22 = gtk_label_new ("Inicio de captura:");
  gtk_widget_ref (label22);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label22", label22,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label22);
  gtk_fixed_put (GTK_FIXED (fixed7), label22, 32, 40);
  gtk_widget_set_uposition (label22, 32, 40);
  gtk_widget_set_usize (label22, 112, 16);
  gtk_label_set_justify (GTK_LABEL (label22), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label22), TRUE);

  label23 = gtk_label_new ("Fin de captura:");
  gtk_widget_ref (label23);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label23", label23,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label23);
  gtk_fixed_put (GTK_FIXED (fixed7), label23, 32, 64);
  gtk_widget_set_uposition (label23, 32, 64);
  gtk_widget_set_usize (label23, 96, 16);
  gtk_label_set_justify (GTK_LABEL (label23), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label23), TRUE);

  label_estafin = gtk_label_new ("xxxxxxx");
  gtk_widget_ref (label_estafin);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estafin", label_estafin,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estafin);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estafin, 136, 64);
  gtk_widget_set_uposition (label_estafin, 136, 64);
  gtk_widget_set_usize (label_estafin, 248, 16);
  gtk_label_set_justify (GTK_LABEL (label_estafin), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_estafin), TRUE);

  label26 = gtk_label_new ("Numero de tramas capturadas:");
  gtk_widget_ref (label26);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label26", label26,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label26);
  gtk_fixed_put (GTK_FIXED (fixed7), label26, 32, 88);
  gtk_widget_set_uposition (label26, 32, 88);
  gtk_widget_set_usize (label26, 184, 16);
  gtk_label_set_justify (GTK_LABEL (label26), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label26), TRUE);

  label_estanumtram = gtk_label_new ("xxx");
  gtk_widget_ref (label_estanumtram);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estanumtram", label_estanumtram,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estanumtram);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estanumtram, 216, 88);
  gtk_widget_set_uposition (label_estanumtram, 216, 88);
  gtk_widget_set_usize (label_estanumtram, 56, 16);
  gtk_label_set_justify (GTK_LABEL (label_estanumtram), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_estanumtram), TRUE);

  hseparator2 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator2);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "hseparator2", hseparator2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator2);
  gtk_fixed_put (GTK_FIXED (fixed7), hseparator2, 32, 104);
  gtk_widget_set_uposition (hseparator2, 32, 104);
  gtk_widget_set_usize (hseparator2, 504, 16);

  label34 = gtk_label_new ("ESTADISTICAS DE RED LOCAL");
  gtk_widget_ref (label34);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label34", label34,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label34);
  gtk_fixed_put (GTK_FIXED (fixed7), label34, 32, 120);
  gtk_widget_set_uposition (label34, 32, 120);
  gtk_widget_set_usize (label34, 192, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label34), TRUE);

  label36 = gtk_label_new ("(");
  gtk_widget_ref (label36);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label36", label36,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label36);
  gtk_fixed_put (GTK_FIXED (fixed7), label36, 240, 120);
  gtk_widget_set_uposition (label36, 240, 120);
  gtk_widget_set_usize (label36, 16, 24);

  label_estalaf = gtk_label_new ("X");
  gtk_widget_ref (label_estalaf);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estalaf", label_estalaf,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estalaf);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estalaf, 256, 120);
  gtk_widget_set_uposition (label_estalaf, 256, 120);
  gtk_widget_set_usize (label_estalaf, 24, 24);

  label38 = gtk_label_new ("de");
  gtk_widget_ref (label38);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label38", label38,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label38);
  gtk_fixed_put (GTK_FIXED (fixed7), label38, 280, 120);
  gtk_widget_set_uposition (label38, 280, 120);
  gtk_widget_set_usize (label38, 24, 24);

  label_estaltf = gtk_label_new ("Y");
  gtk_widget_ref (label_estaltf);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estaltf", label_estaltf,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estaltf);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estaltf, 304, 120);
  gtk_widget_set_uposition (label_estaltf, 304, 120);
  gtk_widget_set_usize (label_estaltf, 24, 24);

  label35 = gtk_label_new ("tramas analizadas)");
  gtk_widget_ref (label35);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label35", label35,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label35);
  gtk_fixed_put (GTK_FIXED (fixed7), label35, 328, 120);
  gtk_widget_set_uposition (label35, 328, 120);
  gtk_widget_set_usize (label35, 120, 24);

  scrolledwindow4 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow4);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "scrolledwindow4", scrolledwindow4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow4);
  gtk_fixed_put (GTK_FIXED (fixed7), scrolledwindow4, 32, 144);
  gtk_widget_set_uposition (scrolledwindow4, 32, 144);
  gtk_widget_set_usize (scrolledwindow4, 528, 152);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow4), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  clist3 = gtk_clist_new (5);
  gtk_widget_ref (clist3);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "clist3", clist3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (clist3);
  gtk_container_add (GTK_CONTAINER (scrolledwindow4), clist3);
  gtk_widget_set_usize (clist3, 504, 144);
  gtk_clist_set_column_width (GTK_CLIST (clist3), 0, 95);
  gtk_clist_set_column_width (GTK_CLIST (clist3), 1, 86);
  gtk_clist_set_column_width (GTK_CLIST (clist3), 2, 90);
  gtk_clist_set_column_width (GTK_CLIST (clist3), 3, 95);
  gtk_clist_set_column_width (GTK_CLIST (clist3), 4, 103);
  gtk_clist_column_titles_show (GTK_CLIST (clist3));

  label29 = gtk_label_new ("Maquina");
  gtk_widget_ref (label29);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label29", label29,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label29);
  gtk_clist_set_column_widget (GTK_CLIST (clist3), 0, label29);

  label30 = gtk_label_new ("Bytes enviados");
  gtk_widget_ref (label30);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label30", label30,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label30);
  gtk_clist_set_column_widget (GTK_CLIST (clist3), 1, label30);

  label31 = gtk_label_new ("Bytes recibidos");
  gtk_widget_ref (label31);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label31", label31,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label31);
  gtk_clist_set_column_widget (GTK_CLIST (clist3), 2, label31);

  label32 = gtk_label_new ("Tramas enviadas");
  gtk_widget_ref (label32);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label32", label32,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label32);
  gtk_clist_set_column_widget (GTK_CLIST (clist3), 3, label32);

  label33 = gtk_label_new ("Tramas recibidas");
  gtk_widget_ref (label33);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label33", label33,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label33);
  gtk_clist_set_column_widget (GTK_CLIST (clist3), 4, label33);

  label51 = gtk_label_new ("ESTADISTICAS DE RED IP");
  gtk_widget_ref (label51);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label51", label51,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label51);
  gtk_fixed_put (GTK_FIXED (fixed7), label51, 32, 304);
  gtk_widget_set_uposition (label51, 32, 304);
  gtk_widget_set_usize (label51, 192, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label51), TRUE);

  label52 = gtk_label_new ("(");
  gtk_widget_ref (label52);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label52", label52,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label52);
  gtk_fixed_put (GTK_FIXED (fixed7), label52, 240, 304);
  gtk_widget_set_uposition (label52, 240, 304);
  gtk_widget_set_usize (label52, 16, 24);

  label_estaiaf = gtk_label_new ("X");
  gtk_widget_ref (label_estaiaf);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estaiaf", label_estaiaf,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estaiaf);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estaiaf, 256, 304);
  gtk_widget_set_uposition (label_estaiaf, 256, 304);
  gtk_widget_set_usize (label_estaiaf, 24, 24);

  label53 = gtk_label_new ("de");
  gtk_widget_ref (label53);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label53", label53,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label53);
  gtk_fixed_put (GTK_FIXED (fixed7), label53, 280, 304);
  gtk_widget_set_uposition (label53, 280, 304);
  gtk_widget_set_usize (label53, 24, 24);

  label_estaitf = gtk_label_new ("Y");
  gtk_widget_ref (label_estaitf);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estaitf", label_estaitf,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estaitf);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estaitf, 304, 304);
  gtk_widget_set_uposition (label_estaitf, 304, 304);
  gtk_widget_set_usize (label_estaitf, 24, 24);

  label54 = gtk_label_new ("tramas analizadas)");
  gtk_widget_ref (label54);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label54", label54,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label54);
  gtk_fixed_put (GTK_FIXED (fixed7), label54, 328, 304);
  gtk_widget_set_uposition (label54, 328, 304);
  gtk_widget_set_usize (label54, 120, 24);

  scrolledwindow5 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow5);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "scrolledwindow5", scrolledwindow5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow5);
  gtk_fixed_put (GTK_FIXED (fixed7), scrolledwindow5, 32, 328);
  gtk_widget_set_uposition (scrolledwindow5, 32, 328);
  gtk_widget_set_usize (scrolledwindow5, 528, 160);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow5), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  clist4 = gtk_clist_new (5);
  gtk_widget_ref (clist4);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "clist4", clist4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (clist4);
  gtk_container_add (GTK_CONTAINER (scrolledwindow5), clist4);
  gtk_widget_set_usize (clist4, 504, 152);
  gtk_clist_set_column_width (GTK_CLIST (clist4), 0, 95);
  gtk_clist_set_column_width (GTK_CLIST (clist4), 1, 86);
  gtk_clist_set_column_width (GTK_CLIST (clist4), 2, 90);
  gtk_clist_set_column_width (GTK_CLIST (clist4), 3, 95);
  gtk_clist_set_column_width (GTK_CLIST (clist4), 4, 103);
  gtk_clist_column_titles_show (GTK_CLIST (clist4));

  label43 = gtk_label_new ("Maquina");
  gtk_widget_ref (label43);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label43", label43,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label43);
  gtk_clist_set_column_widget (GTK_CLIST (clist4), 0, label43);

  label44 = gtk_label_new ("Bytes enviados");
  gtk_widget_ref (label44);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label44", label44,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label44);
  gtk_clist_set_column_widget (GTK_CLIST (clist4), 1, label44);

  label45 = gtk_label_new ("Bytes recibidos");
  gtk_widget_ref (label45);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label45", label45,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label45);
  gtk_clist_set_column_widget (GTK_CLIST (clist4), 2, label45);

  label46 = gtk_label_new ("Tramas enviadas");
  gtk_widget_ref (label46);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label46", label46,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label46);
  gtk_clist_set_column_widget (GTK_CLIST (clist4), 3, label46);

  label47 = gtk_label_new ("Tramas recibidas");
  gtk_widget_ref (label47);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label47", label47,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label47);
  gtk_clist_set_column_widget (GTK_CLIST (clist4), 4, label47);

  label_estainicio = gtk_label_new ("xxxxxxx");
  gtk_widget_ref (label_estainicio);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label_estainicio", label_estainicio,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_estainicio);
  gtk_fixed_put (GTK_FIXED (fixed7), label_estainicio, 136, 40);
  gtk_widget_set_uposition (label_estainicio, 136, 40);
  gtk_widget_set_usize (label_estainicio, 248, 16);
  gtk_label_set_justify (GTK_LABEL (label_estainicio), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_estainicio), TRUE);

  label2 = gtk_label_new ("Estadisticas de captura");
  gtk_widget_ref (label2);
  gtk_object_set_data_full (GTK_OBJECT (win_ini), "label2", label2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label2);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), gtk_notebook_get_nth_page (GTK_NOTEBOOK (notebook), 1), label2);
  gtk_widget_set_usize (label2, 140, 11);

  gtk_signal_connect (GTK_OBJECT (win_ini), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_ini_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (archivo1), "activate",
                      GTK_SIGNAL_FUNC (on_archivo1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (nuevo1), "activate",
                      GTK_SIGNAL_FUNC (on_nuevo1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (abrir), "activate",
                      GTK_SIGNAL_FUNC (on_abrir_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (guardar), "activate",
                      GTK_SIGNAL_FUNC (on_guardar_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (salir), "activate",
                      GTK_SIGNAL_FUNC (on_salir_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (edit1), "activate",
                      GTK_SIGNAL_FUNC (on_edit1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (eliminar_paquete1), "activate",
                      GTK_SIGNAL_FUNC (on_eliminar_paquete1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (eliminar_todos_paquetes1), "activate",
                      GTK_SIGNAL_FUNC (on_eliminar_todos_paquetes1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (eliminar_tramas_por_filtro1), "activate",
                      GTK_SIGNAL_FUNC (on_eliminar_tramas_por_filtro1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ir_a_trama1), "activate",
                      GTK_SIGNAL_FUNC (on_ir_a_trama1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (buscar_trama1), "activate",
                      GTK_SIGNAL_FUNC (on_buscar_trama1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (buscar_siguiente_trama1), "activate",
                      GTK_SIGNAL_FUNC (on_buscar_siguiente_trama1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (empezar1), "activate",
                      GTK_SIGNAL_FUNC (on_empezar1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (opciones_avanzadas1), "activate",
                      GTK_SIGNAL_FUNC (on_opciones_avanzadas1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (acerca_de1), "activate",
                      GTK_SIGNAL_FUNC (on_acerca_de1_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (notebook), "switch_page",
                      GTK_SIGNAL_FUNC (on_notebook_switch_page),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (clist1), "select_row",
                      GTK_SIGNAL_FUNC (on_clist1_select_row),
                      NULL);

  gtk_window_add_accel_group (GTK_WINDOW (win_ini), accel_group);

  return win_ini;
}

GtkWidget*
create_win_cap (void)
{
  GtkWidget *win_cap;
  GtkWidget *fixed2;
  GtkWidget *entry_dev;
  GtkWidget *button1;
  GtkWidget *button4;
  GtkObject *spin_numofpkt_adj;
  GtkWidget *spin_numofpkt;
  GtkObject *spin_maxtime_adj;
  GtkWidget *spin_maxtime;
  GtkObject *spin_maxbytes_adj;
  GtkWidget *spin_maxbytes;
  GtkWidget *entry_filter;
  GtkWidget *hseparator1;
  GtkWidget *label_net_ip;
  GtkWidget *label_net_mask;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkWidget *label16;
  GtkWidget *hseparator3;
  GtkWidget *hseparator4;
  GtkWidget *label48;
  GtkWidget *label49;
  GtkWidget *check_maxtime;
  GtkWidget *check_promis;
  GtkWidget *check_numofpkt;
  GtkWidget *check_maxbytes;
  GtkWidget *label_cap1;

  win_cap = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_cap), "win_cap", win_cap);
  gtk_widget_set_usize (win_cap, 400, 434);
  gtk_container_set_border_width (GTK_CONTAINER (win_cap), 4);
  gtk_window_set_title (GTK_WINDOW (win_cap), "      ");
  gtk_window_set_position (GTK_WINDOW (win_cap), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_cap), TRUE);

  fixed2 = gtk_fixed_new ();
  gtk_widget_ref (fixed2);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "fixed2", fixed2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed2);
  gtk_container_add (GTK_CONTAINER (win_cap), fixed2);

  entry_dev = gtk_entry_new ();
  gtk_widget_ref (entry_dev);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "entry_dev", entry_dev,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_dev);
  gtk_fixed_put (GTK_FIXED (fixed2), entry_dev, 206, 38);
  gtk_widget_set_uposition (entry_dev, 206, 38);
  gtk_widget_set_usize (entry_dev, 100, 24);

  button1 = gtk_button_new_with_label ("Capturar");
  gtk_widget_ref (button1);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "button1", button1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button1);
  gtk_fixed_put (GTK_FIXED (fixed2), button1, 100, 368);
  gtk_widget_set_uposition (button1, 100, 368);
  gtk_widget_set_usize (button1, 64, 30);

  button4 = gtk_button_new_with_label ("Parar");
  gtk_widget_ref (button4);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "button4", button4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button4);
  gtk_fixed_put (GTK_FIXED (fixed2), button4, 236, 368);
  gtk_widget_set_uposition (button4, 236, 368);
  gtk_widget_set_usize (button4, 64, 30);

  spin_numofpkt_adj = gtk_adjustment_new (1, 1, 10000, 1, 10, 10);
  spin_numofpkt = gtk_spin_button_new (GTK_ADJUSTMENT (spin_numofpkt_adj), 1, 0);
  gtk_widget_ref (spin_numofpkt);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "spin_numofpkt", spin_numofpkt,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (spin_numofpkt);
  gtk_fixed_put (GTK_FIXED (fixed2), spin_numofpkt, 272, 135);
  gtk_widget_set_uposition (spin_numofpkt, 272, 135);
  gtk_widget_set_usize (spin_numofpkt, 64, 25);

  spin_maxtime_adj = gtk_adjustment_new (1, 1, 100000, 1, 10, 10);
  spin_maxtime = gtk_spin_button_new (GTK_ADJUSTMENT (spin_maxtime_adj), 1, 0);
  gtk_widget_ref (spin_maxtime);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "spin_maxtime", spin_maxtime,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (spin_maxtime);
  gtk_fixed_put (GTK_FIXED (fixed2), spin_maxtime, 272, 175);
  gtk_widget_set_uposition (spin_maxtime, 272, 175);
  gtk_widget_set_usize (spin_maxtime, 64, 25);

  spin_maxbytes_adj = gtk_adjustment_new (0, 0, 2000, 1, 10, 10);
  spin_maxbytes = gtk_spin_button_new (GTK_ADJUSTMENT (spin_maxbytes_adj), 1, 0);
  gtk_widget_ref (spin_maxbytes);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "spin_maxbytes", spin_maxbytes,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (spin_maxbytes);
  gtk_fixed_put (GTK_FIXED (fixed2), spin_maxbytes, 272, 215);
  gtk_widget_set_uposition (spin_maxbytes, 272, 215);
  gtk_widget_set_usize (spin_maxbytes, 64, 25);

  entry_filter = gtk_entry_new ();
  gtk_widget_ref (entry_filter);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "entry_filter", entry_filter,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_filter);
  gtk_fixed_put (GTK_FIXED (fixed2), entry_filter, 96, 300);
  gtk_widget_set_uposition (entry_filter, 96, 300);
  gtk_widget_set_usize (entry_filter, 232, 40);

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator1);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "hseparator1", hseparator1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator1);
  gtk_fixed_put (GTK_FIXED (fixed2), hseparator1, 50, 110);
  gtk_widget_set_uposition (hseparator1, 50, 110);
  gtk_widget_set_usize (hseparator1, 300, 16);

  label_net_ip = gtk_label_new ("");
  gtk_widget_ref (label_net_ip);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label_net_ip", label_net_ip,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_net_ip);
  gtk_fixed_put (GTK_FIXED (fixed2), label_net_ip, 206, 62);
  gtk_widget_set_uposition (label_net_ip, 206, 62);
  gtk_widget_set_usize (label_net_ip, 100, 24);
  gtk_label_set_justify (GTK_LABEL (label_net_ip), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_net_ip), TRUE);

  label_net_mask = gtk_label_new ("");
  gtk_widget_ref (label_net_mask);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label_net_mask", label_net_mask,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_net_mask);
  gtk_fixed_put (GTK_FIXED (fixed2), label_net_mask, 206, 86);
  gtk_widget_set_uposition (label_net_mask, 206, 86);
  gtk_widget_set_usize (label_net_mask, 100, 24);
  gtk_label_set_justify (GTK_LABEL (label_net_mask), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_net_mask), TRUE);

  label9 = gtk_label_new ("Distpositivo");
  gtk_widget_ref (label9);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label9", label9,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label9);
  gtk_fixed_put (GTK_FIXED (fixed2), label9, 92, 38);
  gtk_widget_set_uposition (label9, 92, 38);
  gtk_widget_set_usize (label9, 92, 24);
  gtk_label_set_justify (GTK_LABEL (label9), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label9), TRUE);

  label10 = gtk_label_new ("IP de red");
  gtk_widget_ref (label10);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label10", label10,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label10);
  gtk_fixed_put (GTK_FIXED (fixed2), label10, 92, 62);
  gtk_widget_set_uposition (label10, 92, 62);
  gtk_widget_set_usize (label10, 92, 24);
  gtk_label_set_justify (GTK_LABEL (label10), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label10), TRUE);

  label16 = gtk_label_new ("IP de mascara");
  gtk_widget_ref (label16);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label16", label16,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label16);
  gtk_fixed_put (GTK_FIXED (fixed2), label16, 92, 86);
  gtk_widget_set_uposition (label16, 92, 86);
  gtk_widget_set_usize (label16, 92, 24);
  gtk_label_set_justify (GTK_LABEL (label16), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label16), TRUE);

  hseparator3 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator3);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "hseparator3", hseparator3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator3);
  gtk_fixed_put (GTK_FIXED (fixed2), hseparator3, 48, 277);
  gtk_widget_set_uposition (hseparator3, 48, 277);
  gtk_widget_set_usize (hseparator3, 300, 16);

  hseparator4 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator4);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "hseparator4", hseparator4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator4);
  gtk_fixed_put (GTK_FIXED (fixed2), hseparator4, 48, 347);
  gtk_widget_set_uposition (hseparator4, 48, 347);
  gtk_widget_set_usize (hseparator4, 300, 16);

  label48 = gtk_label_new ("Filtro");
  gtk_widget_ref (label48);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label48", label48,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label48);
  gtk_fixed_put (GTK_FIXED (fixed2), label48, 32, 308);
  gtk_widget_set_uposition (label48, 32, 308);
  gtk_widget_set_usize (label48, 48, 24);

  label49 = gtk_label_new ("OPCIONES DE CAPTURA");
  gtk_widget_ref (label49);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label49", label49,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label49);
  gtk_fixed_put (GTK_FIXED (fixed2), label49, 72, 0);
  gtk_widget_set_uposition (label49, 72, 0);
  gtk_widget_set_usize (label49, 240, 24);

  check_maxtime = gtk_check_button_new_with_label ("Numero maximo de\nsegundos a capturar");
  gtk_widget_ref (check_maxtime);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "check_maxtime", check_maxtime,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_maxtime);
  gtk_fixed_put (GTK_FIXED (fixed2), check_maxtime, 50, 170);
  gtk_widget_set_uposition (check_maxtime, 50, 170);
  gtk_widget_set_usize (check_maxtime, 190, 32);

  check_promis = gtk_check_button_new_with_label ("Captura en modo promiscuo");
  gtk_widget_ref (check_promis);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "check_promis", check_promis,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_promis);
  gtk_fixed_put (GTK_FIXED (fixed2), check_promis, 50, 250);
  gtk_widget_set_uposition (check_promis, 50, 250);
  gtk_widget_set_usize (check_promis, 190, 24);

  check_numofpkt = gtk_check_button_new_with_label ("Numero maximo de \ntramas a capturar");
  gtk_widget_ref (check_numofpkt);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "check_numofpkt", check_numofpkt,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_numofpkt);
  gtk_fixed_put (GTK_FIXED (fixed2), check_numofpkt, 50, 130);
  gtk_widget_set_uposition (check_numofpkt, 50, 130);
  gtk_widget_set_usize (check_numofpkt, 190, 32);

  check_maxbytes = gtk_check_button_new_with_label ("Maximo numero de bytes \ncapturados por trama");
  gtk_widget_ref (check_maxbytes);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "check_maxbytes", check_maxbytes,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (check_maxbytes);
  gtk_fixed_put (GTK_FIXED (fixed2), check_maxbytes, 50, 210);
  gtk_widget_set_uposition (check_maxbytes, 50, 210);
  gtk_widget_set_usize (check_maxbytes, 190, 32);

  label_cap1 = gtk_label_new ("Capturando tramas...");
  gtk_widget_ref (label_cap1);
  gtk_object_set_data_full (GTK_OBJECT (win_cap), "label_cap1", label_cap1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_fixed_put (GTK_FIXED (fixed2), label_cap1, 104, 408);
  gtk_widget_set_uposition (label_cap1, 104, 408);
  gtk_widget_set_usize (label_cap1, 200, 16);

  gtk_signal_connect (GTK_OBJECT (win_cap), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_cap_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (entry_dev), "focus_out_event",
                      GTK_SIGNAL_FUNC (on_entry_dev_focus_out_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button1), "clicked",
                      GTK_SIGNAL_FUNC (on_button1_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button4), "clicked",
                      GTK_SIGNAL_FUNC (on_button4_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (check_maxtime), "toggled",
                      GTK_SIGNAL_FUNC (on_check_maxtime_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (check_numofpkt), "toggled",
                      GTK_SIGNAL_FUNC (on_check_numofpkt_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (check_maxbytes), "toggled",
                      GTK_SIGNAL_FUNC (on_check_maxbytes_toggled),
                      NULL);

  return win_cap;
}

GtkWidget*
create_win_error (void)
{
  GtkWidget *win_error;
  GtkWidget *fixed4;
  GtkWidget *button_ok;
  GtkWidget *pixmap_error;
  GtkWidget *label_error;

  win_error = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_error), "win_error", win_error);
  gtk_widget_set_usize (win_error, 350, 200);
  gtk_window_set_title (GTK_WINDOW (win_error), "   ");
  gtk_window_set_position (GTK_WINDOW (win_error), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_error), TRUE);

  fixed4 = gtk_fixed_new ();
  gtk_widget_ref (fixed4);
  gtk_object_set_data_full (GTK_OBJECT (win_error), "fixed4", fixed4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed4);
  gtk_container_add (GTK_CONTAINER (win_error), fixed4);

  button_ok = gtk_button_new_with_label ("Aceptar");
  gtk_widget_ref (button_ok);
  gtk_object_set_data_full (GTK_OBJECT (win_error), "button_ok", button_ok,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_ok);
  gtk_fixed_put (GTK_FIXED (fixed4), button_ok, 144, 152);
  gtk_widget_set_uposition (button_ok, 144, 152);
  gtk_widget_set_usize (button_ok, 64, 30);

  pixmap_error = create_pixmap (win_error, "error.xpm");
  gtk_widget_ref (pixmap_error);
  gtk_object_set_data_full (GTK_OBJECT (win_error), "pixmap_error", pixmap_error,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap_error);
  gtk_fixed_put (GTK_FIXED (fixed4), pixmap_error, 8, 40);
  gtk_widget_set_uposition (pixmap_error, 8, 40);
  gtk_widget_set_usize (pixmap_error, 76, 76);

  label_error = gtk_label_new ("label17");
  gtk_widget_ref (label_error);
  gtk_object_set_data_full (GTK_OBJECT (win_error), "label_error", label_error,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label_error);
  gtk_fixed_put (GTK_FIXED (fixed4), label_error, 96, 24);
  gtk_widget_set_uposition (label_error, 96, 24);
  gtk_widget_set_usize (label_error, 204, 95);
  gtk_label_set_justify (GTK_LABEL (label_error), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label_error), TRUE);

  gtk_signal_connect (GTK_OBJECT (win_error), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_error_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_ok), "clicked",
                      GTK_SIGNAL_FUNC (on_button_ok_clicked),
                      NULL);

  return win_error;
}

GtkWidget*
create_win_save (void)
{
  GtkWidget *win_save;
  GtkWidget *fixed5;
  GtkWidget *entry1;
  GtkWidget *button_aceptar;
  GtkWidget *button_cancelar;
  GtkWidget *scrolledwindow3;
  GtkWidget *clist2;
  GtkWidget *label18;
  GtkWidget *label17;
  GtkWidget *label19;
  GtkWidget *pixmap2;

  win_save = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_save), "win_save", win_save);
  gtk_widget_set_usize (win_save, 408, 355);
  gtk_window_set_title (GTK_WINDOW (win_save), "     ");
  gtk_window_set_position (GTK_WINDOW (win_save), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_save), TRUE);

  fixed5 = gtk_fixed_new ();
  gtk_widget_ref (fixed5);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "fixed5", fixed5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed5);
  gtk_container_add (GTK_CONTAINER (win_save), fixed5);

  entry1 = gtk_entry_new ();
  gtk_widget_ref (entry1);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "entry1", entry1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry1);
  gtk_fixed_put (GTK_FIXED (fixed5), entry1, 200, 264);
  gtk_widget_set_uposition (entry1, 200, 264);
  gtk_widget_set_usize (entry1, 152, 24);

  button_aceptar = gtk_button_new_with_label ("Aceptar");
  gtk_widget_ref (button_aceptar);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "button_aceptar", button_aceptar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_aceptar);
  gtk_fixed_put (GTK_FIXED (fixed5), button_aceptar, 96, 312);
  gtk_widget_set_uposition (button_aceptar, 96, 312);
  gtk_widget_set_usize (button_aceptar, 64, 30);

  button_cancelar = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (button_cancelar);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "button_cancelar", button_cancelar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_cancelar);
  gtk_fixed_put (GTK_FIXED (fixed5), button_cancelar, 240, 312);
  gtk_widget_set_uposition (button_cancelar, 240, 312);
  gtk_widget_set_usize (button_cancelar, 64, 30);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_ref (scrolledwindow3);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "scrolledwindow3", scrolledwindow3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow3);
  gtk_fixed_put (GTK_FIXED (fixed5), scrolledwindow3, 56, 40);
  gtk_widget_set_uposition (scrolledwindow3, 56, 40);
  gtk_widget_set_usize (scrolledwindow3, 296, 216);

  clist2 = gtk_clist_new (1);
  gtk_widget_ref (clist2);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "clist2", clist2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (clist2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), clist2);
  gtk_clist_set_column_width (GTK_CLIST (clist2), 0, 80);
  gtk_clist_column_titles_show (GTK_CLIST (clist2));

  label18 = gtk_label_new ("");
  gtk_widget_ref (label18);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "label18", label18,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label18);
  gtk_clist_set_column_widget (GTK_CLIST (clist2), 0, label18);

  label17 = gtk_label_new ("Nombre del archivo");
  gtk_widget_ref (label17);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "label17", label17,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label17);
  gtk_fixed_put (GTK_FIXED (fixed5), label17, 56, 264);
  gtk_widget_set_uposition (label17, 56, 264);
  gtk_widget_set_usize (label17, 128, 24);

  label19 = gtk_label_new ("ABRIR");
  gtk_widget_ref (label19);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "label19", label19,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label19);
  gtk_fixed_put (GTK_FIXED (fixed5), label19, 168, 8);
  gtk_widget_set_uposition (label19, 168, 8);
  gtk_widget_set_usize (label19, 120, 32);
  gtk_label_set_justify (GTK_LABEL (label19), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label19), TRUE);

  pixmap2 = create_pixmap (win_save, "save.xpm");
  gtk_widget_ref (pixmap2);
  gtk_object_set_data_full (GTK_OBJECT (win_save), "pixmap2", pixmap2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap2);
  gtk_fixed_put (GTK_FIXED (fixed5), pixmap2, 120, 8);
  gtk_widget_set_uposition (pixmap2, 120, 8);
  gtk_widget_set_usize (pixmap2, 40, 32);

  gtk_signal_connect (GTK_OBJECT (win_save), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_save_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_aceptar), "clicked",
                      GTK_SIGNAL_FUNC (on_button_aceptar_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_cancelar), "clicked",
                      GTK_SIGNAL_FUNC (on_button_cancelar_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (clist2), "select_row",
                      GTK_SIGNAL_FUNC (on_clist2_select_row),
                      NULL);

  gtk_widget_grab_focus (entry1);
  return win_save;
}

GtkWidget*
create_win_sure (void)
{
  GtkWidget *win_sure;
  GtkWidget *fixed6;
  GtkWidget *surebutton_aceptar;
  GtkWidget *surebutton_cancelar;
  GtkWidget *label20;
  GtkWidget *pixmap1;

  win_sure = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_sure), "win_sure", win_sure);
  gtk_widget_set_usize (win_sure, 350, 200);
  gtk_window_set_title (GTK_WINDOW (win_sure), "       ");
  gtk_window_set_position (GTK_WINDOW (win_sure), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_sure), TRUE);

  fixed6 = gtk_fixed_new ();
  gtk_widget_ref (fixed6);
  gtk_object_set_data_full (GTK_OBJECT (win_sure), "fixed6", fixed6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed6);
  gtk_container_add (GTK_CONTAINER (win_sure), fixed6);

  surebutton_aceptar = gtk_button_new_with_label ("Aceptar");
  gtk_widget_ref (surebutton_aceptar);
  gtk_object_set_data_full (GTK_OBJECT (win_sure), "surebutton_aceptar", surebutton_aceptar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (surebutton_aceptar);
  gtk_fixed_put (GTK_FIXED (fixed6), surebutton_aceptar, 80, 144);
  gtk_widget_set_uposition (surebutton_aceptar, 80, 144);
  gtk_widget_set_usize (surebutton_aceptar, 64, 30);

  surebutton_cancelar = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (surebutton_cancelar);
  gtk_object_set_data_full (GTK_OBJECT (win_sure), "surebutton_cancelar", surebutton_cancelar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (surebutton_cancelar);
  gtk_fixed_put (GTK_FIXED (fixed6), surebutton_cancelar, 216, 144);
  gtk_widget_set_uposition (surebutton_cancelar, 216, 144);
  gtk_widget_set_usize (surebutton_cancelar, 64, 30);

  label20 = gtk_label_new ("label20");
  gtk_widget_ref (label20);
  gtk_object_set_data_full (GTK_OBJECT (win_sure), "label20", label20,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label20);
  gtk_fixed_put (GTK_FIXED (fixed6), label20, 96, 24);
  gtk_widget_set_uposition (label20, 96, 24);
  gtk_widget_set_usize (label20, 204, 95);
  gtk_label_set_justify (GTK_LABEL (label20), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label20), TRUE);

  pixmap1 = create_pixmap (win_sure, "question.xpm");
  gtk_widget_ref (pixmap1);
  gtk_object_set_data_full (GTK_OBJECT (win_sure), "pixmap1", pixmap1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap1);
  gtk_fixed_put (GTK_FIXED (fixed6), pixmap1, 8, 32);
  gtk_widget_set_uposition (pixmap1, 8, 32);
  gtk_widget_set_usize (pixmap1, 76, 76);

  gtk_signal_connect (GTK_OBJECT (win_sure), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_sure_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (surebutton_aceptar), "clicked",
                      GTK_SIGNAL_FUNC (on_surebutton_aceptar_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (surebutton_cancelar), "clicked",
                      GTK_SIGNAL_FUNC (on_surebutton_cancelar_clicked),
                      NULL);

  gtk_widget_grab_focus (surebutton_aceptar);
  return win_sure;
}

GtkWidget*
create_win_options (void)
{
  GtkWidget *win_options;
  GtkWidget *fixed8;
  GtkWidget *button6;
  GtkWidget *button7;
  GtkWidget *checkbutton_ip;
  GtkWidget *checkbutton_ascii;
  GtkWidget *checkbutton_reset;
  GtkWidget *label50;
  GtkWidget *checkbutton_tcp;

  win_options = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_options), "win_options", win_options);
  gtk_widget_set_usize (win_options, 324, 306);
  gtk_window_set_title (GTK_WINDOW (win_options), " ");
  gtk_window_set_position (GTK_WINDOW (win_options), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_options), TRUE);

  fixed8 = gtk_fixed_new ();
  gtk_widget_ref (fixed8);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "fixed8", fixed8,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed8);
  gtk_container_add (GTK_CONTAINER (win_options), fixed8);

  button6 = gtk_button_new_with_label ("Aceptar");
  gtk_widget_ref (button6);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "button6", button6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button6);
  gtk_fixed_put (GTK_FIXED (fixed8), button6, 64, 256);
  gtk_widget_set_uposition (button6, 64, 256);
  gtk_widget_set_usize (button6, 64, 30);

  button7 = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (button7);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "button7", button7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button7);
  gtk_fixed_put (GTK_FIXED (fixed8), button7, 200, 256);
  gtk_widget_set_uposition (button7, 200, 256);
  gtk_widget_set_usize (button7, 63, 30);

  checkbutton_ip = gtk_check_button_new_with_label ("Sobreescribir direcciones MAC\npor direcciones IP");
  gtk_widget_ref (checkbutton_ip);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "checkbutton_ip", checkbutton_ip,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (checkbutton_ip);
  gtk_fixed_put (GTK_FIXED (fixed8), checkbutton_ip, 72, 56);
  gtk_widget_set_uposition (checkbutton_ip, 72, 56);
  gtk_widget_set_usize (checkbutton_ip, 208, 32);

  checkbutton_ascii = gtk_check_button_new_with_label ("Traducir datos de tramas \na codigo ASCII");
  gtk_widget_ref (checkbutton_ascii);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "checkbutton_ascii", checkbutton_ascii,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (checkbutton_ascii);
  gtk_fixed_put (GTK_FIXED (fixed8), checkbutton_ascii, 72, 136);
  gtk_widget_set_uposition (checkbutton_ascii, 72, 136);
  gtk_widget_set_usize (checkbutton_ascii, 208, 32);

  checkbutton_reset = gtk_check_button_new_with_label ("Eliminar todas las tramas cuando\nse empieza una nueva captura");
  gtk_widget_ref (checkbutton_reset);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "checkbutton_reset", checkbutton_reset,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (checkbutton_reset);
  gtk_fixed_put (GTK_FIXED (fixed8), checkbutton_reset, 72, 176);
  gtk_widget_set_uposition (checkbutton_reset, 72, 176);
  gtk_widget_set_usize (checkbutton_reset, 208, 32);

  label50 = gtk_label_new ("OPCIONES AVANZADAS");
  gtk_widget_ref (label50);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "label50", label50,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label50);
  gtk_fixed_put (GTK_FIXED (fixed8), label50, 48, 8);
  gtk_widget_set_uposition (label50, 48, 8);
  gtk_widget_set_usize (label50, 224, 32);

  checkbutton_tcp = gtk_check_button_new_with_label ("Actualizar listado de paquetes \ncon puertos TCP/UDP");
  gtk_widget_ref (checkbutton_tcp);
  gtk_object_set_data_full (GTK_OBJECT (win_options), "checkbutton_tcp", checkbutton_tcp,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (checkbutton_tcp);
  gtk_fixed_put (GTK_FIXED (fixed8), checkbutton_tcp, 72, 96);
  gtk_widget_set_uposition (checkbutton_tcp, 72, 96);
  gtk_widget_set_usize (checkbutton_tcp, 208, 32);

  gtk_signal_connect (GTK_OBJECT (win_options), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_options_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button6), "clicked",
                      GTK_SIGNAL_FUNC (on_button6_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button7), "clicked",
                      GTK_SIGNAL_FUNC (on_button7_clicked),
                      NULL);

  return win_options;
}

GtkWidget*
create_win_goto (void)
{
  GtkWidget *win_goto;
  GtkWidget *fixed9;
  GtkObject *spinbutton_gotonum_adj;
  GtkWidget *spinbutton_gotonum;
  GtkWidget *button_goto_go;
  GtkWidget *button_goto_cancel;
  GtkWidget *label56;
  GtkWidget *label55;
  GtkWidget *pixmap3;

  win_goto = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_goto), "win_goto", win_goto);
  gtk_widget_set_usize (win_goto, 300, 200);
  gtk_window_set_title (GTK_WINDOW (win_goto), " ");
  gtk_window_set_position (GTK_WINDOW (win_goto), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_goto), TRUE);

  fixed9 = gtk_fixed_new ();
  gtk_widget_ref (fixed9);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "fixed9", fixed9,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed9);
  gtk_container_add (GTK_CONTAINER (win_goto), fixed9);

  spinbutton_gotonum_adj = gtk_adjustment_new (1, 1, 10000, 1, 10, 10);
  spinbutton_gotonum = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_gotonum_adj), 1, 0);
  gtk_widget_ref (spinbutton_gotonum);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "spinbutton_gotonum", spinbutton_gotonum,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (spinbutton_gotonum);
  gtk_fixed_put (GTK_FIXED (fixed9), spinbutton_gotonum, 184, 88);
  gtk_widget_set_uposition (spinbutton_gotonum, 184, 88);
  gtk_widget_set_usize (spinbutton_gotonum, 64, 24);

  button_goto_go = gtk_button_new_with_label ("Ir");
  gtk_widget_ref (button_goto_go);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "button_goto_go", button_goto_go,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_goto_go);
  gtk_fixed_put (GTK_FIXED (fixed9), button_goto_go, 64, 152);
  gtk_widget_set_uposition (button_goto_go, 64, 152);
  gtk_widget_set_usize (button_goto_go, 64, 30);

  button_goto_cancel = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (button_goto_cancel);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "button_goto_cancel", button_goto_cancel,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_goto_cancel);
  gtk_fixed_put (GTK_FIXED (fixed9), button_goto_cancel, 176, 152);
  gtk_widget_set_uposition (button_goto_cancel, 176, 152);
  gtk_widget_set_usize (button_goto_cancel, 64, 30);

  label56 = gtk_label_new ("Ir a trama con id");
  gtk_widget_ref (label56);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "label56", label56,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label56);
  gtk_fixed_put (GTK_FIXED (fixed9), label56, 56, 88);
  gtk_widget_set_uposition (label56, 56, 88);
  gtk_widget_set_usize (label56, 120, 24);
  gtk_label_set_justify (GTK_LABEL (label56), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label56), TRUE);

  label55 = gtk_label_new ("Buscar trama");
  gtk_widget_ref (label55);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "label55", label55,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label55);
  gtk_fixed_put (GTK_FIXED (fixed9), label55, 88, 24);
  gtk_widget_set_uposition (label55, 88, 24);
  gtk_widget_set_usize (label55, 112, 24);

  pixmap3 = create_pixmap (win_goto, "find.xpm");
  gtk_widget_ref (pixmap3);
  gtk_object_set_data_full (GTK_OBJECT (win_goto), "pixmap3", pixmap3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap3);
  gtk_fixed_put (GTK_FIXED (fixed9), pixmap3, 64, 22);
  gtk_widget_set_uposition (pixmap3, 64, 22);
  gtk_widget_set_usize (pixmap3, 32, 24);

  gtk_signal_connect (GTK_OBJECT (win_goto), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_goto_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_goto_go), "clicked",
                      GTK_SIGNAL_FUNC (on_button_goto_go_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_goto_cancel), "clicked",
                      GTK_SIGNAL_FUNC (on_button_goto_cancel_clicked),
                      NULL);

  return win_goto;
}

GtkWidget*
create_win_find (void)
{
  GtkWidget *win_find;
  GtkWidget *fixed10;
  GtkWidget *entry_srcaddr;
  GtkWidget *entry_destaddr;
  GtkWidget *entry_proto;
  GtkWidget *pixmap4;
  GtkWidget *button_find_go;
  GtkWidget *button_find_cancel;
  GtkWidget *label58;
  GtkWidget *label59;
  GtkWidget *label60;
  GtkWidget *label57;

  win_find = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_find), "win_find", win_find);
  gtk_widget_set_usize (win_find, 358, 278);
  gtk_window_set_title (GTK_WINDOW (win_find), " ");
  gtk_window_set_position (GTK_WINDOW (win_find), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_find), TRUE);

  fixed10 = gtk_fixed_new ();
  gtk_widget_ref (fixed10);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "fixed10", fixed10,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed10);
  gtk_container_add (GTK_CONTAINER (win_find), fixed10);

  entry_srcaddr = gtk_entry_new ();
  gtk_widget_ref (entry_srcaddr);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "entry_srcaddr", entry_srcaddr,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_srcaddr);
  gtk_fixed_put (GTK_FIXED (fixed10), entry_srcaddr, 160, 80);
  gtk_widget_set_uposition (entry_srcaddr, 160, 80);
  gtk_widget_set_usize (entry_srcaddr, 158, 22);

  entry_destaddr = gtk_entry_new ();
  gtk_widget_ref (entry_destaddr);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "entry_destaddr", entry_destaddr,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_destaddr);
  gtk_fixed_put (GTK_FIXED (fixed10), entry_destaddr, 160, 120);
  gtk_widget_set_uposition (entry_destaddr, 160, 120);
  gtk_widget_set_usize (entry_destaddr, 158, 22);

  entry_proto = gtk_entry_new ();
  gtk_widget_ref (entry_proto);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "entry_proto", entry_proto,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_proto);
  gtk_fixed_put (GTK_FIXED (fixed10), entry_proto, 160, 160);
  gtk_widget_set_uposition (entry_proto, 160, 160);
  gtk_widget_set_usize (entry_proto, 158, 22);

  pixmap4 = create_pixmap (win_find, "find.xpm");
  gtk_widget_ref (pixmap4);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "pixmap4", pixmap4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap4);
  gtk_fixed_put (GTK_FIXED (fixed10), pixmap4, 96, 22);
  gtk_widget_set_uposition (pixmap4, 96, 22);
  gtk_widget_set_usize (pixmap4, 32, 24);

  button_find_go = gtk_button_new_with_label ("Buscar");
  gtk_widget_ref (button_find_go);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "button_find_go", button_find_go,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_find_go);
  gtk_fixed_put (GTK_FIXED (fixed10), button_find_go, 96, 216);
  gtk_widget_set_uposition (button_find_go, 96, 216);
  gtk_widget_set_usize (button_find_go, 64, 30);

  button_find_cancel = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (button_find_cancel);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "button_find_cancel", button_find_cancel,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button_find_cancel);
  gtk_fixed_put (GTK_FIXED (fixed10), button_find_cancel, 208, 216);
  gtk_widget_set_uposition (button_find_cancel, 208, 216);
  gtk_widget_set_usize (button_find_cancel, 64, 30);

  label58 = gtk_label_new ("Por direccion origen");
  gtk_widget_ref (label58);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "label58", label58,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label58);
  gtk_fixed_put (GTK_FIXED (fixed10), label58, 24, 80);
  gtk_widget_set_uposition (label58, 24, 80);
  gtk_widget_set_usize (label58, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label58), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label58), TRUE);

  label59 = gtk_label_new ("Por direccion destino");
  gtk_widget_ref (label59);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "label59", label59,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label59);
  gtk_fixed_put (GTK_FIXED (fixed10), label59, 24, 120);
  gtk_widget_set_uposition (label59, 24, 120);
  gtk_widget_set_usize (label59, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label59), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label59), TRUE);

  label60 = gtk_label_new ("Por protocolo");
  gtk_widget_ref (label60);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "label60", label60,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label60);
  gtk_fixed_put (GTK_FIXED (fixed10), label60, 24, 160);
  gtk_widget_set_uposition (label60, 24, 160);
  gtk_widget_set_usize (label60, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label60), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label60), TRUE);

  label57 = gtk_label_new ("Buscar trama");
  gtk_widget_ref (label57);
  gtk_object_set_data_full (GTK_OBJECT (win_find), "label57", label57,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label57);
  gtk_fixed_put (GTK_FIXED (fixed10), label57, 136, 24);
  gtk_widget_set_uposition (label57, 136, 24);
  gtk_widget_set_usize (label57, 112, 24);

  gtk_signal_connect (GTK_OBJECT (win_find), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_find_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_find_go), "clicked",
                      GTK_SIGNAL_FUNC (on_button_find_go_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button_find_cancel), "clicked",
                      GTK_SIGNAL_FUNC (on_button_find_cancel_clicked),
                      NULL);

  return win_find;
}

GtkWidget*
create_win_about (void)
{
  GtkWidget *win_about;
  GtkWidget *fixed11;
  GtkWidget *button8;
  GtkWidget *label61;
  GtkWidget *label63;
  GtkWidget *label62;
  GtkWidget *frame1;
  GtkWidget *label64;

  win_about = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_about), "win_about", win_about);
  gtk_widget_set_usize (win_about, 350, 200);
  gtk_window_set_title (GTK_WINDOW (win_about), "                     ");
  gtk_window_set_position (GTK_WINDOW (win_about), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_about), TRUE);

  fixed11 = gtk_fixed_new ();
  gtk_widget_ref (fixed11);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "fixed11", fixed11,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed11);
  gtk_container_add (GTK_CONTAINER (win_about), fixed11);

  button8 = gtk_button_new_with_label ("Cerrar");
  gtk_widget_ref (button8);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "button8", button8,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button8);
  gtk_fixed_put (GTK_FIXED (fixed11), button8, 144, 152);
  gtk_widget_set_uposition (button8, 144, 152);
  gtk_widget_set_usize (button8, 64, 30);

  label61 = gtk_label_new ("Proyecto fin de carrera:");
  gtk_widget_ref (label61);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "label61", label61,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label61);
  gtk_fixed_put (GTK_FIXED (fixed11), label61, 64, 32);
  gtk_widget_set_uposition (label61, 64, 32);
  gtk_widget_set_usize (label61, 152, 24);
  gtk_label_set_justify (GTK_LABEL (label61), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label61), TRUE);

  label63 = gtk_label_new ("Autor: Armando Aznar");
  gtk_widget_ref (label63);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "label63", label63,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label63);
  gtk_fixed_put (GTK_FIXED (fixed11), label63, 80, 112);
  gtk_widget_set_uposition (label63, 80, 112);
  gtk_widget_set_usize (label63, 248, 24);
  gtk_label_set_justify (GTK_LABEL (label63), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label63), TRUE);

  label62 = gtk_label_new ("Dise\361o y desarrollo de un sistema de analisis del trafico de paquetes para redes ethernet.");
  gtk_widget_ref (label62);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "label62", label62,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label62);
  gtk_fixed_put (GTK_FIXED (fixed11), label62, 80, 48);
  gtk_widget_set_uposition (label62, 80, 48);
  gtk_widget_set_usize (label62, 216, 56);
  gtk_label_set_justify (GTK_LABEL (label62), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label62), TRUE);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_ref (frame1);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "frame1", frame1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame1);
  gtk_fixed_put (GTK_FIXED (fixed11), frame1, 8, 8);
  gtk_widget_set_uposition (frame1, 8, 8);
  gtk_widget_set_usize (frame1, 336, 184);

  label64 = gtk_label_new ("");
  gtk_widget_ref (label64);
  gtk_object_set_data_full (GTK_OBJECT (win_about), "label64", label64,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label64);
  gtk_container_add (GTK_CONTAINER (frame1), label64);

  gtk_signal_connect (GTK_OBJECT (win_about), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_about_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button8), "clicked",
                      GTK_SIGNAL_FUNC (on_button8_clicked),
                      NULL);

  return win_about;
}

GtkWidget*
create_win_delfil (void)
{
  GtkWidget *win_delfil;
  GtkWidget *fixed12;
  GtkWidget *button9;
  GtkWidget *button10;
  GtkWidget *entry_protocol;
  GtkWidget *entry_destaddress;
  GtkWidget *entry_srcaddress;
  GtkWidget *label65;
  GtkWidget *label66;
  GtkWidget *label67;
  GtkWidget *label68;

  win_delfil = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_delfil), "win_delfil", win_delfil);
  gtk_widget_set_usize (win_delfil, 358, 278);
  gtk_window_set_title (GTK_WINDOW (win_delfil), "   ");
  gtk_window_set_position (GTK_WINDOW (win_delfil), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_delfil), TRUE);

  fixed12 = gtk_fixed_new ();
  gtk_widget_ref (fixed12);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "fixed12", fixed12,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed12);
  gtk_container_add (GTK_CONTAINER (win_delfil), fixed12);

  button9 = gtk_button_new_with_label ("Cancelar");
  gtk_widget_ref (button9);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "button9", button9,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button9);
  gtk_fixed_put (GTK_FIXED (fixed12), button9, 208, 216);
  gtk_widget_set_uposition (button9, 208, 216);
  gtk_widget_set_usize (button9, 64, 30);

  button10 = gtk_button_new_with_label ("Eliminar");
  gtk_widget_ref (button10);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "button10", button10,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button10);
  gtk_fixed_put (GTK_FIXED (fixed12), button10, 96, 216);
  gtk_widget_set_uposition (button10, 96, 216);
  gtk_widget_set_usize (button10, 64, 30);

  entry_protocol = gtk_entry_new ();
  gtk_widget_ref (entry_protocol);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "entry_protocol", entry_protocol,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_protocol);
  gtk_fixed_put (GTK_FIXED (fixed12), entry_protocol, 160, 160);
  gtk_widget_set_uposition (entry_protocol, 160, 160);
  gtk_widget_set_usize (entry_protocol, 158, 22);

  entry_destaddress = gtk_entry_new ();
  gtk_widget_ref (entry_destaddress);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "entry_destaddress", entry_destaddress,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_destaddress);
  gtk_fixed_put (GTK_FIXED (fixed12), entry_destaddress, 160, 120);
  gtk_widget_set_uposition (entry_destaddress, 160, 120);
  gtk_widget_set_usize (entry_destaddress, 158, 22);

  entry_srcaddress = gtk_entry_new ();
  gtk_widget_ref (entry_srcaddress);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "entry_srcaddress", entry_srcaddress,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (entry_srcaddress);
  gtk_fixed_put (GTK_FIXED (fixed12), entry_srcaddress, 160, 80);
  gtk_widget_set_uposition (entry_srcaddress, 160, 80);
  gtk_widget_set_usize (entry_srcaddress, 158, 22);

  label65 = gtk_label_new ("Por direccion origen");
  gtk_widget_ref (label65);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "label65", label65,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label65);
  gtk_fixed_put (GTK_FIXED (fixed12), label65, 24, 80);
  gtk_widget_set_uposition (label65, 24, 80);
  gtk_widget_set_usize (label65, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label65), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label65), TRUE);

  label66 = gtk_label_new ("Por direccion destino");
  gtk_widget_ref (label66);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "label66", label66,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label66);
  gtk_fixed_put (GTK_FIXED (fixed12), label66, 24, 120);
  gtk_widget_set_uposition (label66, 24, 120);
  gtk_widget_set_usize (label66, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label66), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label66), TRUE);

  label67 = gtk_label_new ("Por protocolo");
  gtk_widget_ref (label67);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "label67", label67,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label67);
  gtk_fixed_put (GTK_FIXED (fixed12), label67, 24, 160);
  gtk_widget_set_uposition (label67, 24, 160);
  gtk_widget_set_usize (label67, 128, 24);
  gtk_label_set_justify (GTK_LABEL (label67), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label67), TRUE);

  label68 = gtk_label_new ("Eliminar por filtro");
  gtk_widget_ref (label68);
  gtk_object_set_data_full (GTK_OBJECT (win_delfil), "label68", label68,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label68);
  gtk_fixed_put (GTK_FIXED (fixed12), label68, 80, 24);
  gtk_widget_set_uposition (label68, 80, 24);
  gtk_widget_set_usize (label68, 184, 24);

  gtk_signal_connect (GTK_OBJECT (win_delfil), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_delfil_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button9), "clicked",
                      GTK_SIGNAL_FUNC (on_button9_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button10), "clicked",
                      GTK_SIGNAL_FUNC (on_button10_clicked),
                      NULL);

  return win_delfil;
}

GtkWidget*
create_win_infor (void)
{
  GtkWidget *win_infor;
  GtkWidget *fixed13;
  GtkWidget *button11;
  GtkWidget *label69;
  GtkWidget *pixmap5;

  win_infor = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (win_infor), "win_infor", win_infor);
  gtk_widget_set_usize (win_infor, 350, 200);
  gtk_window_set_title (GTK_WINDOW (win_infor), "      ");
  gtk_window_set_position (GTK_WINDOW (win_infor), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (win_infor), TRUE);

  fixed13 = gtk_fixed_new ();
  gtk_widget_ref (fixed13);
  gtk_object_set_data_full (GTK_OBJECT (win_infor), "fixed13", fixed13,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (fixed13);
  gtk_container_add (GTK_CONTAINER (win_infor), fixed13);

  button11 = gtk_button_new_with_label ("Aceptar");
  gtk_widget_ref (button11);
  gtk_object_set_data_full (GTK_OBJECT (win_infor), "button11", button11,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button11);
  gtk_fixed_put (GTK_FIXED (fixed13), button11, 144, 144);
  gtk_widget_set_uposition (button11, 144, 144);
  gtk_widget_set_usize (button11, 64, 30);

  label69 = gtk_label_new ("label20");
  gtk_widget_ref (label69);
  gtk_object_set_data_full (GTK_OBJECT (win_infor), "label69", label69,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label69);
  gtk_fixed_put (GTK_FIXED (fixed13), label69, 96, 24);
  gtk_widget_set_uposition (label69, 96, 24);
  gtk_widget_set_usize (label69, 204, 95);
  gtk_label_set_justify (GTK_LABEL (label69), GTK_JUSTIFY_LEFT);
  gtk_label_set_line_wrap (GTK_LABEL (label69), TRUE);

  pixmap5 = create_pixmap (win_infor, "info.xpm");
  gtk_widget_ref (pixmap5);
  gtk_object_set_data_full (GTK_OBJECT (win_infor), "pixmap5", pixmap5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (pixmap5);
  gtk_fixed_put (GTK_FIXED (fixed13), pixmap5, 8, 32);
  gtk_widget_set_uposition (pixmap5, 8, 32);
  gtk_widget_set_usize (pixmap5, 76, 76);

  gtk_signal_connect (GTK_OBJECT (win_infor), "delete_event",
                      GTK_SIGNAL_FUNC (on_win_infor_delete_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button11), "clicked",
                      GTK_SIGNAL_FUNC (on_button11_clicked),
                      NULL);

  return win_infor;
}

