#ifndef _QUOTAZIONI
#define _QUOTAZIONI

#include "data.h"

typedef struct quotazione {
    Data d;
    float val;
    float den;
    int tot_titoli;
}Quotazione;

typedef struct temp {
    char ora[6];
    Data d;
    float val; int num;
}Temp;

typedef struct quotazioni *Quotazioni;

void sort_data(int n, Temp *v);
Quotazioni new_leef(Data d, float n_tr, float n_num);
Quotazioni insert_leef(Data d, float n_tr, float n_num, Quotazioni bst);
Quotazioni calcola_quotazione(int n_tr, Temp *v, Quotazioni bst);
void ricerca_quotazione_data(Quotazioni bst, char *data);
void quotazione_max_min(Quotazioni bst);
void quotazione_max_min_intervallo(Quotazioni bst, char *d1, char *d2);
void bilancia_bst(Quotazioni bst);
void libera_bst(Quotazioni bst);

#endif

