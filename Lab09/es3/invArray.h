#ifndef _INVARRAY
#define _INVARRAY

#include "inventario.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tab_inv *tabInv;

void carica_oggetti(tabInv *inventario);
void ricerca_oggetto(tabInv tab);
void stampa_oggetto(tabInv tab);
int sel_obj_inv(tabInv tab, char *oggetto);
void print_oggetto(int ind, inv_t *tab);
void libera_inventario(tabInv tab);

#endif 

