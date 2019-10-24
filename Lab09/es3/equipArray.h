#ifndef _EQUIPARRAY
#define _EQUIPARRAY

#include "inventario.h"
#include "invArray.h"
#include <stdlib.h>
#include <stdio.h>
#define N_INV 8

typedef struct equip *tabEquipment;

void alloca_tabEquip(tabEquipment *tab);
int check_full_equip(tabEquipment tab);
int sleziona_cella_equip(tabEquipment tab);
void assegna_obj_inv(tabEquipment tab, int ind_eq, int ind_obj);
int rimozione_oggetto_equipe(tabEquipment tab, char *oggetto, inv_t *inv);
void print_equipe(tabEquipment eq, inv_t *inv);
void calcola_statistiche(int *hp, int *mp, int *atk, int *def, int *mag, int *spr, tabEquipment tab, inv_t *inv);
void libera_equipment(tabEquipment tab);

#endif 

