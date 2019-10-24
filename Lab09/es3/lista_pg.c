#include "lista_pg.h"

struct nodo_pg {
    caratteristiche pg_t;
    link next;
};

struct node{
    link headPg;
    link tailPg;
    int nPg;
};

link new_node(){
    link node;
    node = (link)malloc(sizeof(*node));
    if(node==NULL){
        printf("Allocazione node fallita.\n");
        exit(1);
    }
    alloca_equip(node->pg_t);
    return node;
}

void libera_nodo(link nodo){
    libera_equip(nodo->pg_t);
    //free(nodo->pg_t.tabEquip);
    free(nodo);
}

tabPg_t Init_lista(){
    tabPg_t tmp;
    
    tmp = (tabPg_t)malloc(sizeof(*tmp));
    tmp->nPg=0;
    return tmp;
}

tabPg_t nuovo_personaggio(tabPg_t head){
    link tmp;
    tmp = new_node();
    
    carica_caratt_pg(&(tmp->pg_t));
    
    if(head->headPg==NULL){
        head->headPg=tmp;
    }
    else{
        head->tailPg->next = tmp;
        tmp->next=NULL;
        head->tailPg=tmp;
    }
    
    (head->nPg)++;
    return head;
}

tabPg_t carica_lista(tabPg_t head){
    FILE *fp;
    link tmp, x;
    
    fp=fopen("pg.txt", "r");
    if(fp==NULL){
        printf("Errore apertura pg.txt\n");
        exit(1);
    }

    x = head->headPg;
   
    while(!feof(fp)){
        if(fp!=EOF){
            tmp = new_node();
            leggi_caratteristiche(fp, &(tmp->pg_t), &(head->nPg));
            
            if((head->nPg)==1){    //gestisco il caricamento del primo nodo
            head->headPg=tmp;
            x=tmp;
            }
            else{
                (tmp->next)=NULL;
                x->next = tmp;
                head->tailPg=tmp;
                x = x->next;
            }
        }
    }
    
    fclose(fp);
    return head;
}

tabPg_t elimina_personaggio(tabPg_t head){
    link x=head->headPg, p=NULL;
    char cod[MAX];
    int i;
    if(x==NULL){
        printf("Errore - lista vuota.\n");
        return head;
    }
    
    printf("Inserire codice personaggio: ");
    scanf("%s", cod);
    
    for(i=0; i<head->nPg; i++){
        if(confronta_codice(x->pg_t, cod)){
            if(p==NULL){
                head->headPg=x->next;
            }
            else{
                p->next=x->next;
                //x->next=NULL;
            }
            libera_nodo(x);
            break;
        }
        p=x;
        x=x->next;
    }
    return head;
}

void agg_oggetto(tabPg_t head, tabInv inventario){
    char codice[MAX], oggetto[MAX];
    link x=head->headPg;
    int i, j, ind_eq, ind_obj;
    
    if(head->headPg==NULL){                     //controllo che la lista non sia vuota
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inserire codice personaggio e nome oggetto: ");
    scanf("%s %s", codice, oggetto);
    
    for(i=0; i<head->nPg ; i++){
        if(confronta_codice(x->pg_t, codice)){
            break;
        }
        x=x->next;
    }
        
    if(i==head->nPg){
        printf("Errore - codice personaggio non trovato.\n");
        return;
    }
    
    if(check_equip(x->pg_t)){
        printf("Errore - inventario pieno.\n");
        return;
    }
 
    ind_eq = selezione_equip(x->pg_t);    //selezione del primo elemento diverso da -1
    ind_obj = sel_obj_inv(inventario, oggetto);      //selezionde dell'oggetto da caricare nell'inventario

    if(ind_obj==-1){
        printf("Errore - Oggetto non presente nell' inventario\n");
        return;
    }

    assegna_obj(&(x->pg_t), ind_eq, ind_obj);    //assegnazione dell'oggetto all'inventario del personaggio tramite indice dell'oggetto nel vettore dell'inventario

    //printf("%s\n", x->pg_t.tabEquip->vettEq[i]->nome );
}

void rim_oggetto(tabPg_t head, tabInv inventario){
    char codice[MAX], oggetto[MAX];
    link x=head->headPg;
    int i, j, ind_eq, ind_obj;
    
    if(head->headPg==NULL){                     //controllo che la lista non sia vuota
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inserire codice personaggio e nome oggetto: ");
    scanf("%s %s", codice, oggetto);
    
    for(i=0; i<head->nPg ; i++){
        if(confronta_codice(x->pg_t, codice)){
            break;
        }
        x=x->next;
    }
        
    if(i==head->nPg){
        printf("Errore - codice personaggio non trovato.\n");
        return;
    }
    
    if(check_equip(x->pg_t)){
        printf("Errore - inventario pieno.\n");
        return;
    }
    
    ind_eq = rimozione_oggetto(&(x->pg_t), oggetto, inventario->vettInv);
        
    if(ind_eq==-1){
        printf("Errore - oggetto non trovato nell'inventario del personaggio.\n");
        return;
    }
/*
        for(int k=0; x->pg_t.tabEquip->vettEq[k]!=NULL; k++)
            printf("%s\n", x->pg_t.tabEquip->vettEq[k]->nome );
*/
}

void statistiche(tabPg_t head, tabInv inventario){
    link x=head->headPg;
    char cod[MAX];
    int i;
    
    
    if(x==NULL){
        printf("Errore - lista vuota.\n");
        return;
    }
    
    printf("Inserire codice personaggio: ");
    scanf("%s", cod);
    
    for(i=0; i<head->nPg ; i++){
        if(confronta_codice(x->pg_t, cod)){
            break;
        }
        x=x->next;
    }
    
    if(i==head->nPg){
        printf("Errore - personaggio non presente nella lista.\n");
        return;
    }
    
    calcola_stat(x->pg_t, inventario->vettInv);
}

void ricerca_pg(tabPg_t head){
    link x;
    char cod[MAX];
    
    if(head->headPg==NULL){
        printf("Errore - lista vuota.\n");
        exit(1);
    }
    
    printf("Inerisci il codice personaggio: ");
    scanf("%s", cod);
    
    for(x=head->headPg; x!=NULL; x=x->next){
        if(confronta_codice(x->pg_t, cod))
            break;
    }
   
     printf("PG: %s\n", x!=NULL? "Presente":"Non presente");
}

void stampa_personaggio(tabPg_t head, inv_t *inventario){
    link x;
    int i=0;
    char cod[MAX];
    
    if(head->headPg==NULL){
        printf("Errore - lista vuota.\n");
        exit(1);
    }
    
    printf("Inserire il codice personaggio: ");
    scanf("%s", cod);
    
    for(x=head->headPg; x!=NULL; x=x->next){
        if(confronta_codice(x->pg_t, cod))
            break;
    }
    
    if(x!=NULL){
        print_personaggio(x->pg_t, inventario);
    }
    else{
        printf("Personaggio non trovato.\n");
    }
}

void libera_lista(tabPg_t head){
    int i;
    link x, tmp;
    x=head->headPg;
    for(i=0; i<head->nPg; i++){
        tmp=x;
        x=x->next;
        libera_nodo(tmp);
    }
    free(head);
}