#ifndef PROC_ETHERNET_H
#define PROC_ETHERNET_H

//Prototipos
void ether_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset);

#endif