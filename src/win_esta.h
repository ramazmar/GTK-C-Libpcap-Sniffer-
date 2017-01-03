#ifndef WIN_ESTA_H
#define WIN_ESTA_H

//Estructura especial para sacar las direcciones IP de una trama.
struct ipaddr_header{
    guint32 nothing[3];
    guint8 src_addr[4];
    guint8 dest_addr[4];
};

//Prototipos
void winesta_refresh();
#endif