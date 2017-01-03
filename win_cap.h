#ifndef WIN_CAP_H
#define WIN_CAP_H

//Prototipos
pcap_t *wincap_get_pcap_descr();
void wincap_set_pcap_descr(pcap_t *new_descr);
void wincap_stop_capture();
void wincap_close_window();
void wincap_start_capture();
void wincap_ini();
void wincap_update_ip_mask();
void wincap_mode_capture();
void wincap_check_numofpkt_toggled();
void wincap_check_maxtime_toggled();
void wincap_check_maxbytes_toggled();
guint32 wincap_get_netp();
guint32 wincap_get_maskp();

#endif