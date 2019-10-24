#ifndef _ST
#define _ST

#define MAX 31

typedef struct st *ST;

ST setNull();
ST st_new_node(char *str, int ind);
ST st_insert(ST st, char *str, int ind);
void libera_ST(ST st);
int string_to_ind(ST st, char *str);
char *ind_to_string(ST st, int ind, int *flag);
void print_st(ST st);

#endif 

