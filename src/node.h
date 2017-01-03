#ifndef NODE_H
#define NODE_H

#include <pcap.h>
#include "node.h"

//Prototipos
struct packet_list_node* new_node(const struct pcap_pkthdr* pkthdr,const u_char* packet);
void free_node(struct packet_list_node *node);

//Estructura utilizada para almacenar un paquete en la lista de memoria
struct packet_list_node{
	struct pcap_pkthdr *pkthdr;
	u_char *pkt;
};

#endif


