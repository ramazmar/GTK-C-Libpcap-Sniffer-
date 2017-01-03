#ifndef PROC_TCP_H
#define PROC_TCP_H

struct tcp_header{
    guint16	src_port;
    guint16	dest_port;
    guint32	seq_num;
    guint32	ack_num;
    guint8	offset_reser;
    guint8	reser_flags;
#define TCP_OFFSET_MASK 	0xf0
#define TCP_FLAG_URG_MASK	0x20
#define TCP_FLAG_ACK_MASK	0x10
#define TCP_FLAG_PSH_MASK	0x08
#define TCP_FLAG_RST_MASK	0x04
#define TCP_FLAG_SYN_MASK	0x02
#define TCP_FLAG_FIN_MASK	0x01
    guint16	window;
    guint16	checksum;
    guint16	urg_ptr;
};

//Prototipos
void tcp_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode,int offset);

#endif