#include "equipArray.h"

struct equip{
    int inUso;
    int vettEq[N_INV];
};

void alloca_tabEquip(tabEquipment *tab){
    int j;
    
    (*tab) = (tabEquipment)malloc(sizeof(*(*tab)));
    if((*tab)==NULL){
        printf("Errore allocazione equip.\n");
        exit(-1);
    }
    for(j=0; j<N_INV; j++){                         //inizializzazione degli elemeti dell'inventario a -1
        (*tab)->vettEq[j]=-1;
    }
    (*tab)->inUso = 0;
}

int check_full_equip(tabEquipment tab){
    if(tab->inUso==N_INV){
        return 1;
    }
    return 0;
}

int sleziona_cella_equip(tabEquipment tab){
    int i=0;
    
    for(i=0; tab->vettEq[i]!=-1; i++);
    return tab->vettEq[i];
}

void assegna_obj_inv(tabEquipment tab, int ind_eq, int ind_obj){
    tab->vettEq[ind_eq] = ind_obj;
    tab->inUso++;
}

int rimozione_oggetto_equipe(tabEquipment tab, char *oggetto, inv_t *inv){
    int i;
    for(i=0; i<tab->inUso; i++){
        if(check_oggetto(tab->vettEq[i], oggetto, inv)){
            //printf("%s\n",x->pg_t.tabEquip->vettEq[i]->nome );
            break;
        }
    }
    
    if(i==tab->inUso){
        return -1;
    }
    
    i++;
    while(tab->vettEq[i]!=-1){
        tab->vettEq[i-1]=tab->vettEq[i];      //copertura della cella in cui è stato eliminato l'oggetto
        i++;
    }
    tab->vettEq[i-1]=-1;         //assegnazione di NULL all'ultimo elemento dell'inventario diventato un doppione del penultimo
    tab->inUso--;
    
    return 1;
}

void print_equipe(tabEquipment eq, inv_t *inv){
    int i;
    if(eq->inUso!=0){
        printf("Inventario:\n");
        for(i=0; i<eq->inUso; i++)
            print_oggetto(eq->vettEq[i], inv);
    }
    else{
        printf("Inventario di vuoto.\n");
    }
}

void calcola_statistiche(int *hp, int *mp, int *atk, int *def, int *mag, int *spr, tabEquipment tab, inv_t *inv){
    int i;
    
    for(i=0; i<tab->inUso; i++){
        (*hp)+=_hp(tab->vettEq[i], inv);
        (*mp)+=_mp(tab->vettEq[i], inv);
        (*atk)+=_atk(tab->vettEq[i], inv);
        (*def)+=_def(tab->vettEq[i], inv);
        (*mag)+=_mag(tab->vettEq[i], inv);
        (*spr)+=_spr(tab->vettEq[i], inv);
    }
}

void libera_equipment(tabEquipment tab){
    free(tab->vettEq);
    free(tab);
}