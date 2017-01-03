#ifndef PROC_UDP_H
#define PROC_UDP_H

struct udp_header{
    guint16	src_port;
    guint16	dest_port;
    guint16	length;
    guint16	checksum;
};

//Prototipos
void udp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset);

#endif