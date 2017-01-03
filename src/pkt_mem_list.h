#ifndef PKT_MEM_LIST_H
#define PKT_MEM_LIST_H

#include "node.h"

//Prototipos
void pkt_mem_list_reset();
void pkt_mem_list_delete_pkt(int row);
void pkt_mem_list_append(const struct pcap_pkthdr* pkthdr, const u_char* packet);
guint pkt_mem_list_length();
GList *pkt_mem_list_nth(int frame);

#endif