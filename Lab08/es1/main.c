#include <stdio.h>
#include <stdlib.h>

typedef struct attivita {
    int s;
    int f;
}att;

void attSel(int N, att *v);
void carica(att **vet, int *n);
void powerset(int num, att *v, int pos, att *sol, int start, int n, att *best, int *sum, int *n_b);
int check(att *sol,int num, int *sum);
int controlla(att prima, att seconda, int i);

int main() {
    att *vet;
    int n;
    
    carica(&vet, &n);
    
    attSel(n, vet);
    return 0;
}

void carica(att **vet, int *n){     //funzione per caricare il vettore di struct da file
    FILE *fp;
    
    fp = fopen("file.txt", "r");
    if(fp==NULL){
        printf("Errore file.\n");
        exit(1);
    }
    
    fscanf(fp, "%d", n);
    (*vet)=(att *)malloc((*n)*sizeof(att));
    for(int i=0; i<(*n); i++){
        fscanf(fp, "%d %d", &(*vet)[i].s, &(*vet)[i].f);
    }
    
    fclose(fp);
}

void attSel(int n, att *v){    //funzione wrapper
    int i=0;
    att *sol, *best;
    int sum=0, n_best;
    
    sol = (att *)malloc(n*sizeof(att));     //allocazione del vettore soluzione
    best = (att *)malloc(n*sizeof(att));    //allocazione del vettore per la soluzione migliore
    for(i=0; i<n; i++){                 //calcolo del powerset attraverso le combinazioni semplici
        powerset(i, v, 0, sol, 0, n, best, &sum, &n_best);
    }
    
    for(i=0; i<n_best; i++){            //stampa della soluzione migliore
        printf("(%d,%d) ", best[i].s, best[i].f);
    }
    printf("somma = %d", sum);
    
}

void powerset(int num, att *v, int pos, att *sol, int start, int n, att *best, int *sum, int *n_b){
    int i;
    
    if(pos>=num){
        if(check(sol, num, sum)){       //funzione di controllo per l'aggionamento della soluzione migliore
            (*n_b)=num;
            for(int j=0; j<num; j++){
                best[j]=sol[j];
            }
        }
        return;
    }
    
    for(i=start; i<n; i++){
        if(controlla(sol[pos-1], v[i], pos)){       //funzione di pruning
            sol[pos]=v[i];

            powerset(num, v, pos+1, sol, i+1, n, best, sum, n_b);   //chiamata ricorsiva
        }
    }
}

int check(att *sol,int num, int *sum){
    int somma=0;
    for(int i=0; i<num; i++){       //calcolo della somma della soluzione temporanea
        somma+=(sol[i].f-sol[i].s);
    }
    if(somma>(*sum)){       //aggiornamento della somma nel caso quella trovata si maggiore di quella massima
        (*sum)=somma;
        return 1;
    }
    
    return 0;
}

int controlla(att prima, att seconda, int i){       //funzione di pruning 
    if(i!=0){
        if((prima.s<seconda.f) && (seconda.s<prima.f)){         //controllo che le due attività selezionate siano compatibili
            return 0;
        }
        else return 1;
    }
    return 1;
}