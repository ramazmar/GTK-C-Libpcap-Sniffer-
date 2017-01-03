#ifndef PROC_ARP_H
#define PROC_ARP_H

//Definicion de tipos de tramas ARP.
#define REQUEST		1	// ARP request
#define REPLY		2	// ARP REPLY
#define REV_REQUEST	3	// RARP REQUEST
#define REV_REPLY	4	// RARP REPLY
#define InREQUEST	8	// InARP REQUEST
#define InREPLY		9	// InARP REPLY
#define NAK		10	// (ATM)ARP NAK

//Definicion de tipo de protocolos que usa por encima de ARP.
#define XEROX_PUP	0x512
#define XEROX_NS_IDP	0x600
#define INTERNET_PROTO	0x800
#define X_75		0x801

struct arp_header {

    guint16 format_hwaddr;
    guint16 proto_type;
    guint8 hw_addr_len;
    guint8 proto_addr_len;
    guint16 op;
    
    guint8 arp_sha[6]; //Sender hardware addres
    guint8 arp_spa[4]; //Sender protocol addres
    guint8 arp_tha[6]; //Target hw addres
    guint8 arp_tpa[4]; //Targer protocol addres

};

//Prototipos
void arp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset);

#endif