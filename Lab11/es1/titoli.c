#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titoli.h"
#include "quotazioni.h"

#define MAX 21

struct titolo {
    char nome[MAX];
    Quotazioni lquot;
};

struct lista_titoli {
    Titolo t;
    L_titoli next;
};

L_titoli init (L_titoli l){
    l = (L_titoli)malloc(sizeof(*l));
    l->t = (Titolo)malloc(sizeof(*(l->t)));
    l->t->lquot = NULL;
    strcmp(l->t->nome, "");
    l->next = NULL;
    
    return l;
}

Titolo alloca_titolo(){
    Titolo t;
    
    t = (Titolo)malloc(sizeof(*t));
    if(t == NULL){
        printf("Errore allocazione titolo.\n");
        exit(-3);
    }
    t->lquot = NULL;
    
    return t;
}

L_titoli new_node(){
    L_titoli tmp;
    tmp = (L_titoli)malloc(sizeof(*tmp));
    if(tmp == NULL){
        printf("Errore allocazione nuovo nodo.\n");
        exit(-2);
    }
    tmp->next = NULL;
    tmp->t = alloca_titolo();
    
    return tmp;
}

void carica_lista_titoli(L_titoli head){
    FILE *fp;
    int n, n_tr, i, j, flag=0;
    L_titoli sup, x, p;
    char nome[MAX];
    char date[11];
    Temp *v;
    
    fp = fopen("titoli.txt", "r");
    if(fp==NULL){
        printf("Errore apertura titoli.txt\n");
        exit(-1);
    }
    
    fscanf(fp, "%d", &n);
    for(i=0; i<n; i++){               //ciclo di lettura di un titolo
        fscanf(fp, "%s %d", nome, &n_tr);
        sup = new_node();
        strcpy(sup->t->nome, nome);
        
        v = (Temp *)malloc(n_tr*sizeof(Temp));           //allocazione vettore temporaneo per il calcolo delle quotazioni
        for(j=0; j<n_tr; j++){                              //ciclo di lettura delle transazioni di un titolo
            fscanf(fp, "%s %s %f %d", date, v[j].ora, &v[j].val, &v[j].num);
            v[j].d = carica_data(date);
        }
        sup->t->lquot = calcola_quotazione(n_tr, v, sup->t->lquot);    //calcolo delle quotazioni e creazione del bst
        
        for(x=head, p=head; x!=NULL; x=x->next){       //insertion sort sui titoli     
            if(strcmp(x->t->nome, sup->t->nome)>0){
                break;
            }
            else{
                if(!strcmp(x->t->nome, sup->t->nome)){
                    //aggiorna titolo
                    flag=1;
                    x->t->lquot = calcola_quotazione(n_tr, v, x->t->lquot);
                }
            }
            p = x;
        }
        if(!flag){                  //inserimento in lista solo nel caso si tratti di un titolo nuovo
            p->next = sup;
            sup->next = x;
            free(v);
        }
    }
}

void ricerca_titolo(L_titoli head){
    char titolo[MAX];
    int flag=0;
    L_titoli x;
    
    printf("Inserire nome titolo: ");
    scanf("%s", titolo);
    
    for(x=head; x!=NULL && flag==0; x=x->next){
        if(!strcmp(x->t->nome, titolo)){
            flag=1;
        }
    }
    
    if(flag){
        printf("Titolo trovato.\n");
    }
    else{
        printf("Titolo NON trovato.\n");
    }
}

void ricerca_quotazione(L_titoli head){
    char titolo[MAX], data[11];
    int flag=0;
    L_titoli x;
    
    printf("Inserire nome titolo: ");
    scanf("%s", titolo);
    
    for(x=head; x!=NULL; x=x->next){
        if(!strcmp(x->t->nome, titolo)){
            flag=1;
            break;
        }
    }
    
    if(flag){
        printf("Inserire data: ");
        scanf("%s", data);
        ricerca_quotazione_data(x->t->lquot, data);
    }
    else{
        printf("Titolo NON trovato.\n");
    }
}

void max_min_titolo(L_titoli head){
    char titolo[MAX], data[11];
    int flag=0;
    L_titoli x;
    
    printf("Inserire nome titolo: ");
    scanf("%s", titolo);
    
    for(x=head; x!=NULL; x=x->next){
        if(!strcmp(x->t->nome, titolo)){
            flag=1;
            break;
        }
    }
    
    if(flag){
        quotazione_max_min(x->t->lquot);
    }
    else{
        printf("Titolo NON trovato.\n");
    }
}

void max_min_intervallo(L_titoli head){
    char titolo[MAX], data1[11], data2[11];
    int flag=0;
    L_titoli x;
    
    printf("Inserire nome titolo: ");
    scanf("%s", titolo);
    
    for(x=head; x!=NULL; x=x->next){
        if(!strcmp(x->t->nome, titolo)){
            flag=1;
            break;
        }
    }
    
    if(flag){
        printf("Inserire intervallo di date [data_inizio data_fine]: ");
        scanf("%s %s", data1, data2);
        quotazione_max_min_intervallo(x->t->lquot, data1, data2);
    }
    else{
        printf("Titolo NON trovato.\n");
    }
}

void bilancia(L_titoli head){
    char titolo[MAX], data[11];
    int flag=0;
    L_titoli x;
    
    printf("Inserire nome titolo: ");
    scanf("%s", titolo);
    
    for(x=head; x!=NULL; x=x->next){
        if(!strcmp(x->t->nome, titolo)){
            flag=1;
            break;
        }
    }
    
    if(flag){
        bilancia_bst(x->t->lquot);
    }
    else{
        printf("Titolo NON trovato.\n");
    }
}

static void libera_titolo(Titolo t){
	libera_bst(t->lquot);
	free(t);
}

void libera_lista(L_titoli head){
	L_titoli x, sup;
	
	for(x=head, p=NULL; x!=NULL; ){
		sup = x;
		x = x->next;
		libera_titolo(sup->t);
		free(sup);
	}
}

void print_lista_titoli(L_titoli head){      //debug
    L_titoli x;
    
    for(x=head->next; x!=NULL; x=x->next){
        printf("%s\n", x->t->nome);
    }
}