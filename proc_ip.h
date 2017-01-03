#ifndef PROC_IP_H
#define PROC_IP_H

#define ICMP 		1
#define IGMP 		2
#define GGP		3
#define IP 		4
#define STREAM		5
#define TCP		6
#define UDP		17

#define CBT		7
#define EGP		8
#define IGP		9
#define BBNRCCMON	10
#define BVPII		11
#define PUP		12
#define ARGUS		13
#define EMCON		14
#define XNET		15
#define CHAOS		16
#define MUX		18
#define DCNMEANS	19
#define HMP		20
#define PRM		21
#define XNSIDP		22
#define TRUNK1		23
#define TRUNK2		24
#define LEAF1		25
#define LEAF2		26
#define RFP		27
#define IRTP		28
#define ISOTP4		29
#define NETBLT		30


struct ip_header {

    guint8 vers_hlen;
    guint8 service;
    guint16 tlen;
    guint16 id;
//4 bits de FLAG
#define DF_FLAG_MASK 0x4000
#define MF_FLAG_MASK 0x2000
#define OFFSET_MASK 0X1fff
    guint16 offset;
    guint8 ttl;
    guint8 protocol;
    guint16 checksum;

    guint8 src_addr[4];
    guint8 dest_addr[4];

};

//Prototipos
void ip_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset);

#endif