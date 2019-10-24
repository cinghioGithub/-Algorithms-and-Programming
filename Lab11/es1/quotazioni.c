#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include "quotazioni.h"

#define S 1.5

struct quotazioni {
    Quotazione quot;
    Quotazioni l, r;
    int n;
    float max_q, min_q;
};

void sort_data(int n, Temp *v){
    int i, j;
    Temp sup;
    
    for(i=0; i<n; i++){         //selection sort per le transazioni  
        for(j=i+1; j<n ; j++){
            if(data_cmp(v[i].d, v[j].d)>0){
                sup = v[i];
                v[i] = v[j];
                v[j] = sup;
            }
        }
    }
}

Quotazioni new_leef(Data d, float n_tr, float n_num){
    Quotazioni q;
    q = (Quotazioni)malloc(sizeof(*q));
    if(q==NULL){
        printf("Errore allocazione foglia bst.\n");
        exit(-4);
    }
    q->quot.d = d;
    q->quot.tot_titoli = n_tr;
    q->quot.val = n_num/n_tr;
    q->quot.den = n_tr;
    q->n = 1;
    q->max_q = q->quot.val;
    q->min_q = q->quot.val;
    q->l = NULL;
    q->r = NULL;
    
    return q;
}

Quotazioni insert_leef(Data d, float n_tr, float n_num, Quotazioni bst){
    if(bst == NULL){
        return new_leef(d, n_tr, n_num);     //caso terminale, creo una foglia
    }
    if(data_cmp(bst->quot.d, d)<0){                 //controllo se la data è maggiore del nodo selezionato
        bst->r = insert_leef(d, n_tr, n_num, bst->r);
    }
    if(data_cmp(bst->quot.d, d)>0){
        bst->l = insert_leef(d, n_tr, n_num, bst->l);
    }
    //funzione di aggiornamento nel caso la data sia già presente
    if(data_cmp(bst->quot.d, d)==0){
        bst->quot.val = ((bst->quot.val)*(bst->quot.den) + n_num) / ((bst->quot.den) + n_tr);
		bst->max_q = bst->quot.val;         //assegnazioni per evitare che, se il massimo assouluto diminuisce non diminuisca max_q, e lo stesso per il minimo
		bst->min_q = bst->quot.val;
    }
    
    if(bst->l==NULL){                   //aggiornamento del max
        if(bst->quot.val > bst->r->max_q){
           bst->max_q = bst->quot.val; 
        }
        else{
            bst->max_q = bst->r->max_q;
        }
        if(bst->quot.val < bst->r->min_q){
           bst->min_q = bst->quot.val; 
        }
        else{
            bst->min_q = bst->r->min_q;
        }
    }
    else{
        if(bst->r==NULL){                       //aggiornamento del min
            if(bst->quot.val > bst->l->max_q){
                bst->max_q = bst->quot.val; 
            }
            else{
                bst->max_q = bst->l->max_q;
            }
            if(bst->quot.val < bst->l->min_q){
               bst->min_q = bst->quot.val; 
            }
            else{
                bst->min_q = bst->l->min_q;
            }
        }
        else{
            if(bst->r->max_q > bst->l->max_q){   //aggiornamento del massimo
                if(bst->quot.val > bst->r->max_q){
                    bst->max_q = bst->r->max_q;
                }
                else{
                    bst->max_q = bst->quot.val;
                }
            }
            else{
                if(bst->quot.val > bst->l->max_q){
                    bst->max_q = bst->l->max_q;
                }
                else{
                    bst->max_q = bst->quot.val;
                }
            }
            if(bst->r->min_q < bst->l->min_q){   //aggiornamento del minimo
                if(bst->quot.val < bst->r->min_q){
                    bst->min_q = bst->r->min_q;
                }
                else{
                    bst->min_q = bst->quot.val;
                }
            }
            else{
                if(bst->quot.val < bst->l->min_q){
                    bst->min_q = bst->l->min_q;
                }
                else{
                    bst->min_q = bst->quot.val;
                }
            }
        }
    }
    (bst->n)++;              //aggiornamento numero di nodi del sotto albero
    return bst;
}

Quotazioni calcola_quotazione(int n_tr, Temp *v, Quotazioni bst){
    int i;
    Data d;
    float tot_tr=0, tot_val=0;
    
    sort_data(n_tr, v);
    for(i=0; i<n_tr; i++){
        d = v[i].d;
        tot_tr = 0; tot_val = 0;
        while(v[i].d.anno == d.anno && v[i].d.mese == d.mese && v[i].d.giorno == d.giorno && i<n_tr){             //seleziono tutte le data ugauli
            tot_tr += v[i].num;             //conteggio delle transazioni totali per la data corrente
            tot_val += v[i].val*v[i].num;       //calcolo del numeratore dalla frazione per il calcolo della quotazione
            i++;
        }
        i--;       //corregge il doppio incremento dovuto al while e al for
        tot_val/tot_tr;          //calcolo della quotazione
        
        bst = insert_leef(d, tot_tr, tot_val, bst);      //inserimento della quotazione calcolata nel bst
    }
    
    return bst;
}

static void ricerca_quotazione_dataR(Quotazioni bst, Data d){
    if(bst == NULL){
        printf("Quotazione NON trovata.\n");
        return;
    }
    if(!data_cmp(bst->quot.d, d)){
        printf("Quotazione: %.2f\n", bst->quot.val);
        return;
    }
    if(data_cmp(bst->quot.d, d)>0){
        ricerca_quotazione_dataR(bst->r, d);
        return;
    }
    if(data_cmp(bst->quot.d, d)<0){
        ricerca_quotazione_dataR(bst->l, d);
        return;
    }
}

void ricerca_quotazione_data(Quotazioni bst, char *data){
    Data d;
    
    d = carica_data(data);
    
    ricerca_quotazione_dataR(bst, d);
}

void quotazione_max_min(Quotazioni bst){
    printf("Quotazione massima: %.2f\nQuotazione minima: %.2f\n", bst->max_q, bst->min_q);
}

static void max_bst_intervallo(Quotazioni bst, Data d1, Data d2){
    Quotazioni x;
    
    for(x = bst; x!=NULL;){                 //tagio i rami finchè la data non rientra nell'intervallo, quando trovo una data che ci rientra stampo il max
        if(data_cmp(x->quot.d, d2)>0){
            x = x->l;
        }
        else if (data_cmp(x->quot.d, d1)<0){
                x = x->r;
            }
            else{
            printf("Quotazione max: %.2f\n", x->max_q);
            return;
            }
    }
    
    printf("Intervallo di date errato.\n");    
}

static Quotazioni search_start_minR(Quotazioni bst, Data d1, Data d2){
    Quotazioni x;
    
    for(x = bst; x!=NULL;){                                 //ricerco la prima data compresa nell'intervallo di date per poi visitare il suo sottoalbero
        if(data_cmp(x->quot.d, d2)>0){
            x = x->l;
        }
        else if (data_cmp(x->quot.d, d1)<0){
                x = x->r;
            }
            else{
            return x;
            }
    }
    
    return NULL;
}

static void min_bst_intervalloR(Quotazioni bst, Data d1, Data d2, float *min){
    if(bst==NULL){
        return;                                                                 //visito il sottoalbero che parte da bst e trovo il minimo
    }
    if(data_cmp(bst->quot.d, d1)<0 || data_cmp(bst->quot.d, d2)>0){
        return;
    }
    
    if(bst->quot.val < (*min)){
        (*min) = bst->quot.val;
    }
    
    min_bst_intervalloR(bst->r, d1, d2, min);
    min_bst_intervalloR(bst->l, d1, d2, min);
}

void quotazione_max_min_intervallo(Quotazioni bst, char *d1, char *d2){
    float min = FLT_MAX;
    Data data1 = carica_data(d1);
    Data data2 = carica_data(d2);
    Quotazioni start = search_start_minR(bst, data1, data2);
    
    if(start==NULL){
        printf("Intervallo date errato.\n");
        return;
    }
    max_bst_intervallo(bst, data1, data2);
    min_bst_intervalloR(start, data1, data2, &min);
    
    printf("Quotazione min: %.2f\n", min);
}

static void calcola_cammino_max_min(Quotazioni bst, int *max, int *min, int c){
    
    if(bst==NULL){              //scendo nell'albero, quando trovo un NULL, sono in fondo a un ramo, guardo se la sua lunghezza migliora max o min
        if(c<(*min)){
            (*min)=c;
        }
        if(c>(*max)){
            (*max)=c;
        }
        return;
    }
    c++;
    calcola_cammino_max_min(bst->r, max, min, c);
    calcola_cammino_max_min(bst->l, max, min, c);
}

static Quotazioni rot_r(Quotazioni bst){
    Quotazioni x = bst->l;
    bst->l = x->r;
    x->r = bst;
    x->n = bst->n;
    bst->n = ((bst->l == NULL)? 0:bst->l->n) + ((bst->r == NULL)? 0:bst->r->n) + 1;
    return x;
}

static Quotazioni rot_l(Quotazioni bst){
    Quotazioni x = bst->r;
    bst->r = x->l;
    x->l = bst;
    x->n = bst->n;
    bst->n = ((bst->l == NULL)? 0:bst->l->n) + ((bst->r == NULL)? 0:bst->r->n) + 1;
    return x;
}

static Quotazioni partition(Quotazioni bst, int n){
    int t = (bst->l == NULL)? 0 : bst->l->n;
    if(t > n){
        bst->l = partition(bst->l, n);
        bst = rot_r(bst);
    }
    if(t < n){
        bst->r = partition(bst->r, n-t-1);
        bst = rot_l(bst);
    }
    return bst;
}

void bilancia_bst(Quotazioni bst){
    int max = 1, min = INT_MAX ;
    float s=0;
    
    calcola_cammino_max_min(bst, &max, &min, 0);
    
    s = (float)max/min;
    
    if(s>S){
        partition(bst, (bst->n+1)/2-1);
        printf("Bilanciamento eseguito.\n");
    }
    else{
        printf("Bilanciamento NON eseguito.\n");
    }
}

void libera_bst(Quotazioni bst){
	if(bst==NULL){
		return;
	}
	libera_bst(bst->r);
	libera_bst(bst->l);
	free(bst);
}