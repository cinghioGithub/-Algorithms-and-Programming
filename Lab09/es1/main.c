#include <stdio.h>
#include <stdlib.h>

typedef struct attivita {
    int s;
    int f;
}att;

void carica(att **vet, int *n);
void best_sol(att *vet, int n);
void print_solR(att *vet, int i, int *ind);
void print_sol(att *vet, int n, int *w, int *ind);
void sort(att *vet, int n);

int main() {

    att *vet;
    int n;
    
    carica(&vet, &n);
    
    sort(vet, n);
    
    best_sol(vet, n);
    
    free(vet);
    
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

void sort(att *vet, int n){             //ordinamento delle attività in maniera crescente rispetto al tempo di inizio
    att tmp;
    int i, j;
    
    for(i=0; i<n; i++){
        for(j=0; j<n-1-i; j++){
            if(vet[j].s>vet[j+1].s){
                tmp=vet[j];
                vet[j]=vet[j+1];
                vet[j+1]=tmp;
            }
            else if(vet[j].s==vet[j+1].s){
                if(vet[j].f>vet[j+1].f){
                    tmp=vet[j];
                    vet[j]=vet[j+1];
                    vet[j+1]=tmp;
                }
            }
        }
    }
}

void print_solR(att *vet, int i, int *ind){         //stampa ricosrsiva della soluzione
    if(i==-1){
        return;
    }
    print_solR(vet, ind[i], ind);
    printf("(%d,%d) ", vet[i].s, vet[i].f);
}

void print_sol(att *vet, int n, int *w, int *ind){      
    int i, max_w=0, max_i=-1;
    for(i=0; i<n; i++){             //selezione dell'attività che termina la soluzione
        if(w[i]>=max_w){
            max_i=i;
            max_w=w[i];
        }
    }
    
    printf("Sequenza di attività con somma delle durate massima: ");
    print_solR(vet, max_i, ind);        //stampa della soluzione
}

void best_sol(att *vet, int n){
    int i, j;
    int *ind, *w, w_tmp;
    
    ind = (int *)malloc(n*sizeof(int));
    w = (int *)malloc(n*sizeof(int));
    if(ind==NULL || w==NULL){
        printf("Errore.\n");
        exit(-1);
    }
    ind[0]=-1; w[0]=vet[0].f-vet[0].s;
    for(i=1; i<n; i++){
        ind[i]=-1; w[i]=vet[i].f-vet[i].s;
        w_tmp=w[i];
        for(j=0; j<i; j++){                                 //controllo di ogni prefisso per ogni attività selezionata dal ciclo esterno
            if((vet[j].s<=vet[i].f && vet[j].f<=vet[i].s) && w[i]<w_tmp+w[j]){   //controlla della compatibilità di due attività
                ind[i]=j;
                w[i]=w_tmp+w[j];
            }
        }
    }
    
    print_sol(vet, n, w, ind);      //stampa della soluzione
    free(ind);
    free(w);
}