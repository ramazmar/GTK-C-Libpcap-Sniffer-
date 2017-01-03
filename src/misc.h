#ifndef MISC_H
#define MISC_H

#include <pcap.h>

#define MY_BUF_SIZE 300

//Zona de memoria para uso comun de todos los modulos
char *str_buf[MY_BUF_SIZE];

char errbuf[PCAP_ERRBUF_SIZE];

#endif //MISC_H