#include "invArray.h"
#include "inventario.h"

struct tab_inv{
    int nInv;
    inv_t *vettInv;
};

void carica_oggetti(tabInv *inventario){
    FILE *fp;
    inv_t *invent;
    int i, num_inv;
    
    fp = fopen("inventario.txt", "r");
    if(fp==NULL){
        printf("Errore apertura inventario.txt\n");
        exit(1);
    }
    
    fscanf(fp, "%d", &num_inv);
    (*inventario)=(tabInv)malloc(sizeof(*(*inventario)));
    invent = alloca_inventario(num_inv);
 
    leggi_oggetti(fp, invent, num_inv);
    
    (*inventario)->nInv=num_inv;
    (*inventario)->vettInv=invent;
    fclose(fp);
}

void ricerca_oggetto(tabInv tab){
    char name[MAX];
    int i;
    if(tab->nInv==0){
        printf("Inventario vuoto.\n");
    }
    else{
        printf("Inserire nome oggetto: ");
        scanf("%s", name);
        
        for(i=0; i<tab->nInv; i++){
            if(!strcmp(tab->vettInv[i].nome, name)){
                break;
            }
        }
        if(i==tab->nInv){
            printf("Oggetto non presente nell'inventario.\n");
        }
        else{
            printf("Oggetto trovato, tipo: %s\n", tab->vettInv[i].tipo);
        }
    }
    
}

void stampa_oggetto(tabInv tab){
    char name[MAX];
    int i;
    if(tab->nInv==0){
        printf("Inventario vuoto.\n");
    }
    else{
        printf("Inserire nome oggetto: ");
        scanf("%s", name);
        
        for(i=0; i<tab->nInv; i++){
            if(!strcmp(tab->vettInv[i].nome, name)){
                break;
            }
        }
        if(i==tab->nInv){
            printf("Oggetto non presente nell'inventario.\n");
        }
        else{
            printf("Oggetto trovato:\n %s %s %d %d %d %d %d %d\n", tab->vettInv[i].nome, tab->vettInv[i].tipo, tab->vettInv[i].stat.hp, tab->vettInv[i].stat.mp, tab->vettInv[i].stat.atk, tab->vettInv[i].stat.def, tab->vettInv[i].stat.mag, tab->vettInv[i].stat.spr);
        }
    }
}

int sel_obj_inv(tabInv tab, char *oggetto){
    int ans;
    if((ans=sel_obj_vettInv(tab->vettInv, tab->nInv, oggetto))!=-1){
        return -1;
    }
    return ans;
}

void print_oggetto(int ind, inv_t *tab){
    print_tool(tab[ind]);
}

void libera_inventario(tabInv tab){
    libera_inv(tab->vettInv);
    free(tab);
}