#ifndef WIN_INI_H
#define WIN_INI_H

//Variable global
GtkWidget *win_ini;
//Prototipos
void winini_init();
void winini_row_selected(int row);
int winini_get_row_selected();
void winini_delete_row_selected();
void winini_update_packet_mem_list();
void winini_clist_get_text(int row,int col,char **str);
void winini_clist_set_text(int row,int col,char *str);
void winini_clist_append(char *vlist[4]);
void winini_clist_select_row(int row);
void winini_clist_reset();
void winini_tree_append(GtkWidget *treeitem);
void winini_delete_all_rows();

#endif