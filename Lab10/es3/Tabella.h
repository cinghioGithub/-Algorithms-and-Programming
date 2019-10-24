#ifndef _TABELLA
#define _TABELLA

typedef struct tabella *Tab;

Tab tabella_init(int n);
int ins_tab(Tab t, char *name, int *num);
char *ind_to_string(Tab t, int ind);
int string_to_ind(Tab t, char *name);
void sort_vertici(int *v, Tab t, int n);
void print_tabella(Tab t);

#endif

