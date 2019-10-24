#ifndef _LISTA_PG
#define _LISTA_PG

#include "inventario.h"
#include "equipArray.h"
#include "lista_pg.h"
#include "personaggio.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo_pg *link;
typedef struct node *tabPg_t;

link new_node();
void libera_nodo(link nodo);
tabPg_t Init_lista();
tabPg_t nuovo_personaggio(tabPg_t head);
tabPg_t carica_lista(tabPg_t head);
tabPg_t elimina_personaggio(tabPg_t head);
void agg_oggetto(tabPg_t head, tabInv inventario);
void rim_oggetto(tabPg_t head, tabInv inventario);
void statistiche(tabPg_t head, tabInv inventario);
void ricerca_pg(tabPg_t head);
void stampa_personaggio(tabPg_t head, inv_t *inventario);
void libera_lista(tabPg_t head);

#endif

