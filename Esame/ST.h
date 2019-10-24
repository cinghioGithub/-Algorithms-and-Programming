#ifndef _ST
#define _ST

typedef struct st *ST;

ST ST_init(int n);
int ST_insert(ST st, char *str);
int ST_string_to_ind(ST st, char *str);
char *ST_ind_to_string(ST st, int i);
void libera_ST(ST st);
int ST_size(ST st);   //correzione

#endif