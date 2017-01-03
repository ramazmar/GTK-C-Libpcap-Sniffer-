#ifndef PROC_FRAME_H
#define PROC_FRAME_H

//Prototipos
void frame_handler(int pos, struct pcap_pkthdr *pkt_hdr, u_char *pkt,int mode);
void data_tree(GtkWidget *tree,char *data_ptr,int size);

#endif