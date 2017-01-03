//pkt_mem_list.c
//--------------

#include <gtk/gtk.h>
#include <sys/types.h>
#include <stdlib.h>
#include "misc.h"
#include "pkt_mem_list.h"
#include "node.h"

//Variables globales
static GList *pkt_mem_list;	//Lista donde estan almacenadas todas las tramas de la sesion.

//Funcion encargada de eliminar todas las tramas de la lista en memoria.
//Debido a que g_list_free() no libera la memoria asignada a sus datos, se tendra
//que hacerlo manualmente.
void pkt_mem_list_reset()
{
    GList *runner;
    guint length,cnt;
    
    struct packet_list_node *node;        
    length=g_list_length(pkt_mem_list);
    
    for(cnt=0;cnt!=length;cnt++){
	runner=g_list_nth(pkt_mem_list,cnt);
	node=(struct packet_list_node *)runner->data;
	
	//Se libera la memoria asignada a los nodos con anterioridad	    
	free_node(node);    
	    
    }
    
    //Una vez liberados todos los nodos, se libera/resetea la lista.
    g_list_free(pkt_mem_list); 
    pkt_mem_list=NULL;
}

//Funcion que elimina una trama de la lista de memoria.
//Parametros:
//	row:Entero con el id de la trama a eliminar de memoria.
void pkt_mem_list_delete_pkt(int row)
{
    GList *runner;
    struct packet_list_node *node;
    
    
    runner=g_list_nth(pkt_mem_list,row);
    node=(struct packet_list_node *)runner->data;

    pkt_mem_list=g_list_remove(pkt_mem_list,node);
    
    //Liberamos la memoria asignada a ese nodo.
    free_node(node);

}

//Funcion para insertar una trama en la lista de memoria
//Parametros:
//	pkthdr:Estructura con datos relevantes a la trama a insertar
//	packet:Puntero a los datos de la trama a insertar
void pkt_mem_list_append(const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    struct packet_list_node *node;
    
    //Se duplica el paquete en memoria debido a que pcap usa un buffer estatico
    // para el almacenamiento de paquetes.
    node=new_node(pkthdr,packet);
    
    pkt_mem_list=g_list_append(pkt_mem_list,node);
}

//Funcion que devuelve el tamaño de la lista de tramas en memoria
guint pkt_mem_list_length()
{
    if (pkt_mem_list!=NULL){
	return g_list_length(pkt_mem_list);
    }else return 0;
}

//Funcion para leer una trama de la lista en memoria
//Parametros:
//	frame: Numero id de la trama que se quiere leer
//	Devuelve:Puntero al nodo de la lista en memoria
GList *pkt_mem_list_nth(int frame)
{
    GList *runner;    
    
    if (pkt_mem_list!=NULL){
	runner=g_list_nth(pkt_mem_list,frame);
	return runner;
    }else return NULL;
    
}