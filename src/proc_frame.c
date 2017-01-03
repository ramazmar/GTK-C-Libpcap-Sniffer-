 //proc_frame.c
//-------------

#include <pcap.h>
#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "proc_frame.h"
#include "win_ini.h"
#include "proc_ethernet.h"
#include "win_options.h"
#include "win_error.h"


//Funcion que actualiza los datos (en la lista de tramas capturadas o en el
// arbol de detalles)  de una trama determinada
//Esta funcion es llamada una vez es terminada una captura (o abierta una sesion 
//  grabada anteriormente) pasandole el mode 2 y todos los ids de las tramas capturadas
//  en orden, así se actualiza la lista de tramas capturadas. Tambien es llamada
//  cada vez que se selecciona una trama de la lista para actualizar los
//  detalles de la trama seleccionada.
//Parametros:
//	pos:Posicion en la lista de memoria de la trama
//	pcap_pkthr:Estructura con datos relevantes a la trama capturada.
//	pkt:Puntero a la trama capturada.
//	mode:Modo en el que el handler debe actualizar la ventana.
//		mode 1:Actualiza solo la lista
//		mode 2:Actualiza solo el arbol
void frame_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode)
{    
    GtkWidget *treeitem,*subtree;
    GString *gcadena;
    char *vlist[4];
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
    
    if (mode==2){ 
	//Si hay q actualizar el arbol solo	
	//Al ser el primer handler, se resetea el arbol.
	winini_clist_reset();
	//Se crea un subarbol con la etiqueta "Trama:id"	
	sprintf(str_buf_run,"Trama:%d",pos+1);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	winini_tree_append(treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
	
	//Se añade el tiempo de llegada al subarbol
	sprintf(str_buf_run,"Tiempo de llegada:%s",ctime((const time_t*)&pkt_hdr->ts.tv_sec)); //Ctime devuelve la cadena correspondiente a la fecha/hora
	
	//Se quita el salto de linea de la cadena que devuelve ctime()
	str_buf_run[strlen(str_buf_run)-1]=' ';
	sprintf(&str_buf_run[strlen(str_buf_run)],"(%li micro segundos)",pkt_hdr->ts.tv_usec);
	
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
	//Se añade el tamaño de trama y de captura
	sprintf(str_buf_run,"Tamaño de la trama:%u bytes",pkt_hdr->len);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	sprintf(str_buf_run,"Tamaño de captura:%u bytes",pkt_hdr->caplen);
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(subtree),treeitem);
	gtk_widget_show(treeitem);
	
    }else{
	//Si solo hay que actualizar la lista de tramas, se añade el ID
	sprintf(str_buf_run,"%d",pos+1);
	gcadena=g_string_new(str_buf_run);
	vlist[0]=gcadena->str;
    
	gcadena=g_string_new("");
	vlist[1]=vlist[2]=vlist[3]=gcadena->str;
	winini_clist_append(vlist);
    }
    //Se le pasa la trama al handler de ethernet, ya que solo es posible que lleguen tramas ethernet.
    ether_handler(pos,pkt_hdr,pkt,mode,0);
}

//Función que utilizaran todos los handlers para añadir su arbol de datos
//Parametros:
//	tree:Arbol donde se añadira el subarbol con los datos
//	data_ptr:Puntero a los datos a añadir en el subarbol de DATOS
//	size:Cantidad de ytes a añadir en el arbol de datos (empezando desde donde apunta data_ptr).
void data_tree(GtkWidget *tree,char *data_ptr,int size)
{
    
    GtkWidget *treeitem,*subtree;
    guchar *temp_str,*temp_str3,*temp_str4;
    int cnt,cnt2;
    char *str_buf_run;
    
    str_buf_run=(char *)str_buf;
	
	//Primero se crea el subarbol de DATOS
    	sprintf(str_buf_run,"DATOS");
	treeitem=gtk_tree_item_new_with_label(str_buf_run);
	gtk_tree_append(GTK_TREE(tree),treeitem);
	gtk_widget_show(treeitem);
	subtree=gtk_tree_new();
	gtk_tree_item_set_subtree(GTK_TREE_ITEM(treeitem),subtree);
	
	if((temp_str=malloc(size+1))==NULL){
	    winerror_msg("No hay memoria suficiente.");
	    gtk_main_quit();
	    exit (-1);
	}

	//Si esta marcada la opcion de traducir a código ascii de la ventana de
	//  opciones avanzadas, se traduce.
	if (winoptions_option_ascii()){
	    for (cnt=0;cnt<size;cnt++){
		if (data_ptr[cnt]>31){ //Los caracteres por debajo de 31 no son imprimibles.
		    temp_str[cnt]=data_ptr[cnt];
		}else {
		    temp_str[cnt]='-';
		}
	    }
	}else{//Si se ponel el valor BINARIO
	    for (cnt=0;cnt<size;cnt++){
		    temp_str[cnt]=data_ptr[cnt];
	    }
	    
	}
	
	temp_str[size]='\0';
	
	//Si esta marcada la opcion de traducir a código ascii de la ventana de
	//  opciones avanzadas, se traduce.
	if (winoptions_option_ascii()){
	    cnt2=0;
	    temp_str3=malloc(8+1);
	    for(cnt=0;cnt<size;cnt++){
		temp_str3[cnt2]=temp_str[cnt];
		cnt2++;
		if(cnt2==8){
		    temp_str3[cnt2]='\0';
		    cnt2=0;
		    sprintf(str_buf_run,"%s",temp_str3);
		    treeitem=gtk_tree_item_new_with_label(str_buf_run);
		    gtk_tree_append(GTK_TREE(subtree),treeitem);
		    gtk_widget_show(treeitem);
		}
	    }
	    if (cnt2!=0){
		//Si falta la última línea
		temp_str3[cnt2]='\0';
		sprintf(str_buf_run,"%s",temp_str3);
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);		
		gtk_widget_show(treeitem);
	    }
	    free(temp_str3);
	    free(temp_str);
	}else{
	    temp_str3=malloc(2);
	    temp_str4=malloc(8*3+1+1);//*3 pk por cada ascii irán 2 hexas y un espacio (pero serán espaciados de 8)
	    //Habrá que volver a reserar memoria en funcion de los espaciados.
	    cnt2=0;
	    for(cnt=0;cnt<(size);cnt++){
		    sprintf(temp_str3,"%2.2x",temp_str[cnt]);
		    temp_str4[cnt2*2+cnt2]=temp_str3[0];
		    temp_str4[cnt2*2+cnt2+1]=temp_str3[1];
		    temp_str4[cnt2*2+cnt2+2]=' ';
		    cnt2++;
		    if (cnt2==8){
			temp_str4[(cnt2-1)*2+cnt2+2]='\0'; //Se resta uno, pq antes se ha incrementado
			cnt2=0;
			sprintf(str_buf_run,"%s",temp_str4);
			treeitem=gtk_tree_item_new_with_label(str_buf_run);
			gtk_tree_append(GTK_TREE(subtree),treeitem);
			gtk_widget_show(treeitem);
		    }

	    }
	    if (cnt2!=0){
		//Si hace falta la última línea.
		temp_str4[cnt2*2+cnt2-1]='\0';
		sprintf(str_buf_run,"%s",temp_str4);
		treeitem=gtk_tree_item_new_with_label(str_buf_run);
		gtk_tree_append(GTK_TREE(subtree),treeitem);
		gtk_widget_show(treeitem);
	    }
	    free(temp_str);
	    free(temp_str3);
	    free(temp_str4);
	}
}
  
