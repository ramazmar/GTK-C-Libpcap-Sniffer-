//win_ini.c
//---------

#include <pcap.h>
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include "support.h"
#include "misc.h"
#include "win_ini.h"
#include "interface.h"
#include "pkt_mem_list.h"
#include "proc_frame.h"
#include "win_infor.h"

//Variables globales
//GtkWidget *win_ini; Ya definida en el archivo de cabecera
static GtkWidget *packet_clist;
static GtkWidget *packet_tree;
static int row_selected=-1;

//Se le llama desde main para inicializar la ventana inicial.
//Desde ella se crearán las referencias globales a la lista de columnas de paquetes
//y a la lista de arbol.
void winini_init()
{
    
	GtkWidget *table1;
	GtkWidget *table2;
	GtkWidget *vpaned;
	GtkWidget *scrolledwin1,*scrolledwin2;
	GtkWidget *viewport;
	GtkWidget *notebook;
	GtkWidget *esta_fixed;
	
	Display *display;
	int def_screen;
	char *display_name=NULL;
	unsigned int width,heigth;

	
	win_ini=create_win_ini();
	
	//Se maximiza la pantalla
	if (!(display=XOpenDisplay(display_name))){
	    fprintf(stderr, "No se puede conectar al servidor X %s\n",XDisplayName(display_name));	
	}else{
	    def_screen=DefaultScreen(display);
	    width=DisplayWidth(display,def_screen);
	    heigth=DisplayHeight(display,def_screen);
	    XCloseDisplay(display);
	    gtk_widget_set_usize(win_ini,width-10,heigth-20);
	}

	
        //Recordar k si no encuentra el widget se jode todo así k no hace falta comprobar luego.
        table1=lookup_widget(GTK_WIDGET(win_ini),"table1");
        notebook=lookup_widget(GTK_WIDGET(table1),"notebook");
	esta_fixed=lookup_widget(GTK_WIDGET(notebook),"fixed7");
        table2=lookup_widget(GTK_WIDGET(notebook),"table2");
        vpaned=lookup_widget(GTK_WIDGET(table2),"vpaned1");
        scrolledwin1=lookup_widget(GTK_WIDGET(vpaned),"scrolledwindow1");
	scrolledwin2=lookup_widget(GTK_WIDGET(vpaned),"scrolledwindow2");
	viewport=lookup_widget(GTK_WIDGET(scrolledwin2),"viewport1");
        
        packet_clist=lookup_widget(GTK_WIDGET(scrolledwin1),"clist1");
        packet_tree=lookup_widget(GTK_WIDGET(viewport),"tree1");
        
        //Inicializada la ventana principal.
	gtk_widget_show(win_ini);
	
};


//Funcion llamada cuando se selecciona una fila de la lista de paquetes capturados.
void winini_row_selected(int row)
{
    struct packet_list_node *node;    
    GList *runner;
    
    //Seleccionada fila señalada por row
    row_selected=row;
    
    //Se actualiza el arbol referente al paquete seleccionado
    runner=pkt_mem_list_nth(row);
    node=(struct packet_list_node *)runner->data;
    frame_handler(row,node->pkthdr,node->pkt,2);
}

//Funcion utilizada para saber que fila esta seleccionada desde una funcion
//  externa al módulo.
int winini_get_row_selected()
{
    return row_selected;
}


//Funcion que borra una trama de la lita de memoria.
void winini_delete_row_selected()
{

    if ((row_selected!=-1)&&(row_selected<pkt_mem_list_length())){
	
	pkt_mem_list_delete_pkt(row_selected);
	winini_update_packet_mem_list();
	
    }else{
	wininfor_msg("No se ha seleccionado ninguna trama.");
    }
}

//Funciones de acceso a la variable packet_clist
void winini_clist_get_text(int row,int col,char **str)
{
    gtk_clist_get_text(GTK_CLIST(packet_clist),row,col,str);
}

void winini_clist_set_text(int row,int col,char *str)
{
    gtk_clist_set_text(GTK_CLIST(packet_clist),row,col,str);
}

void winini_clist_append(char *vlist[4])
{    
    gtk_clist_append(GTK_CLIST(packet_clist),vlist);
}

void winini_clist_select_row(int row)
{
    row_selected=row;
    gtk_clist_select_row(GTK_CLIST(packet_clist),row,0);
    gtk_clist_moveto(GTK_CLIST(packet_clist),row,0,0,0);
}

void winini_clist_reset(){
    gtk_tree_clear_items(GTK_TREE(packet_tree),0,g_list_length(GTK_TREE(packet_tree)->children));//Hay k dar posiciones de inicio(0) y de fin(lenght)
}

void winini_tree_append(GtkWidget *treeitem)
{
    gtk_tree_append(GTK_TREE(packet_tree),treeitem);
}
//Actualiza la lista de columnas con la lista en memoria de los paquetes,
// resetea el arbol y pone el notebook en la pagina 1.
void winini_update_packet_mem_list()
{
    GList *runner;
    gint length,cnt;
    GtkWidget *notebook,*table;
    
    struct packet_list_node *node; //Un puntero a nodos de paquetes en memoria.
    
    table=lookup_widget(GTK_WIDGET(win_ini),"table1");
    notebook=lookup_widget(GTK_WIDGET(table),"notebook");
    
    //Primero se debe borrar todos las lineas la lista de columnas y resetear el arbol.
    gtk_clist_clear(GTK_CLIST(packet_clist));

    gtk_tree_clear_items(GTK_TREE(packet_tree),0,g_list_length(GTK_TREE(packet_tree)->children));//Hay k dar posiciones de inicio(0) y de fin(lenght)

    row_selected=-1;
        
    //Se recorrera la lista de memoria actualizando la lista de columnas solo.(mode 1)
    if (pkt_mem_list_length()>0){
	length=pkt_mem_list_length();
	
	//Se llamara al handler en modo1 de cada paquete para actualizar la lista de paquetes.    
	for(cnt=0;cnt!=length;cnt++){
	    runner=pkt_mem_list_nth(cnt);
	    node=(struct packet_list_node *)runner->data;
	    frame_handler(cnt,node->pkthdr,node->pkt,1);
	}
    }
    
    gtk_notebook_set_page(GTK_NOTEBOOK(notebook),0);
}

void winini_delete_all_rows()
{
    pkt_mem_list_reset();
    winini_update_packet_mem_list();
}