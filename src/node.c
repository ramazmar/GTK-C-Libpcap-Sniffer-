//node.c
//------

#include <pcap.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "node.h"
#include "win_error.h"


//Estructura utilizada para almacenar un paquete en la lista de memoria
//struct packet_list_node{
//	struct pcap_pkthdr *pkthdr;
//	u_char *pkt;
//};


struct packet_list_node* new_node(const struct pcap_pkthdr* pkthdr,const u_char* packet)
{
    struct packet_list_node *node;

    if((node=(struct packet_list_node *)malloc(sizeof(struct packet_list_node)))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    }        
    //Se duplica el paquete en memoria debido a que pcap usa un buffer estatico
    if((node->pkthdr=malloc(sizeof(struct pcap_pkthdr)))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    }
    node->pkthdr->ts=pkthdr->ts;
    node->pkthdr->caplen=pkthdr->caplen;
    node->pkthdr->len=pkthdr->len;
    
    //Se reserva memoria para copiar el paquete en memoria
    if((node->pkt=malloc(pkthdr->len))==NULL){
	winerror_msg("No hay memoria suficiente.");
	gtk_main_quit();
	exit (-1);
    };
    
    //Se copia la zona de memoria en la que se ha reservado
    node->pkt=memcpy(node->pkt,packet,pkthdr->len);     
    return node;    
}

void free_node(struct packet_list_node *node)
{
    //Se libera la memoria ocupada por la trama/nodo en memoria
    free(node->pkthdr);
    free(node->pkt);
    free (node);
}
