#ifndef PROC_ICMP_H
#define PROC_ICMP_H

//Definicion de tipos
#define ICMP_TYP_ECHO_REPLY		0
#define ICMP_TYP_DEST_UNREA		3
#define ICMP_TYP_SOURCE_QUENCH		4
#define ICMP_TYP_REDIRECT		5
#define ICMP_TYP_ALT_HOST_ADDR		6
#define ICMP_TYP_ECHO			8
#define ICMP_TYP_ROUTER_ADVIRT		9
#define ICMP_TYP_ROUTER_SELECT		10
#define ICMP_TYP_TIMEOUT		11
#define ICMP_TYP_PARAMET_PROB		12
#define ICMP_TYP_TIMESTAMP		13
#define ICMP_TYP_TIMESTAMP_REPLY	14
#define ICMP_TYP_INFOR_REQUEST		15
#define ICMP_TYP_INFOR_REPLY		16
#define ICMP_TYP_ADDR_MASK_REQUEST	17
#define ICMP_TYP_ADDR_MASK_REPLY	18
#define ICMP_TYP_TRACEROUTE		30
#define ICMP_TYP_DATAG_CONV_ERROR	31
#define ICMP_TYP_MOBILE_HOST_REDI	32
#define ICMP_TYP_IPV6_WHERE		33
#define ICMP_TYP_IPV6_IMHERE		34

struct icmp_header{
    guint8 type;
    guint8 code;
    guint16 checksum;
};

struct icmp_echo_header{
    guint16 id;
    guint16 seq_num; 
};

struct icmp_redirect_header{
    guint8 router_addr[4];
};

//Prototipos
void icmp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode, int offset);

#endif