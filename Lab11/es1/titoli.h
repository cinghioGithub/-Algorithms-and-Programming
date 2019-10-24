#ifndef _TITOLI
#define _TITOLI

typedef struct titolo *Titolo;
typedef struct lista_titoli *L_titoli;

L_titoli init (L_titoli l);
Titolo alloca_titolo();
L_titoli new_node();
void carica_lista_titoli(L_titoli head);
void ricerca_titolo(L_titoli head);
void ricerca_quotazione(L_titoli head);
void max_min_titolo(L_titoli head);
void max_min_intervallo(L_titoli head);
void bilancia(L_titoli head);
void libera_lista(L_titoli head);
void print_lista_titoli(L_titoli head);

#endif 

