#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef struct {
    char T1;
    int nT1;
    char T2;
    int nT2;
} Pedina;

typedef struct {
    int n_p;
    int rot;
} Scacchiera;

Pedina *carica_pedine(int *num_p, int **mark);
Scacchiera **carica_scacchiera(int *nr, int *nc, Scacchiera ***sol);
int controlla(Pedina *p, Scacchiera **s, int nr, int nc);
void disposizioni(Pedina *p, Scacchiera **s, Scacchiera **sol, int nr, int nc, int pos, int *max_p, int *mark, int num_p);
void my_free(Pedina *p, Scacchiera **s, Scacchiera **sol,int *mark, int nr);

int main() {
    Pedina *pedine;
    Scacchiera **scacchiera, **sol;
    int num_p, nr, nc, max=0, *mark;
    
    pedine = carica_pedine(&num_p, &mark);
    scacchiera = carica_scacchiera(&nr, &nc, &sol);
    
    disposizioni(pedine, scacchiera, sol, nr, nc, 0, &max, mark, num_p);
    
    printf("%d\n", max);
    for(int y=0; y<nr; y++){
        for(int l=0; l<nc; l++){
            printf("%d/%d ", sol[y][l].n_p, sol[y][l].rot);
        }
        printf("\n");
    }
    
    my_free(pedine, scacchiera, sol, mark, nr);
    
    return 0;
}

Pedina *carica_pedine(int *num_p, int **mark){
    Pedina *tmp;
    FILE *fp;
    int i;
    char sup[N];
    
    fp = fopen("tiles.txt", "r");
    if(fp==NULL){
        printf("Errore tiles.txt\n");
        exit(1);
    }
    
    fgets(sup, N, fp);
    sscanf(sup, "%d", num_p);
    tmp = (Pedina *)malloc((*num_p)*sizeof(Pedina));    //allocazione del vettore per le pedine
    (*mark) = (int *)calloc((*num_p),sizeof(int));      //allocazione del vettore mark per le disposizioni semplici
    for(i=0; i<(*num_p); i++){
        fgets(sup, N, fp);
        sscanf(sup, "%c %d %c %d", &tmp[i].T1, &tmp[i].nT1, &tmp[i].T2, &tmp[i].nT2);
    }
    
    fclose(fp);
    return tmp;
}

Scacchiera **carica_scacchiera(int *nr, int *nc, Scacchiera ***sol){
    FILE *fp;
    Scacchiera **tmp;
    char sup[20];
    int i, j;
    
    fp = fopen("board.txt", "r");
    if(fp == NULL){
        printf("Errore board.txt\n");
        exit(1);
    }
    
    fscanf(fp, "%d %d", nr, nc);
    tmp = (Scacchiera **)malloc((*nr)*sizeof(Scacchiera *));    //allocazione del vettore si puntatori per la scacchiera
    (*sol) = (Scacchiera **)malloc((*nr)*sizeof(Scacchiera *));     //allocazione del vettore si puntatori per la soluzione migliore
    for(i=0; i<(*nr); i++){
        tmp[i] = (Scacchiera *)malloc((*nc)*sizeof(Scacchiera));       //allocazione di ogni riga della matrice per la scacchiera
        (*sol)[i] = (Scacchiera *)malloc((*nc)*sizeof(Scacchiera));     //allocazione di ogni riga della matrice per la soluzione migliore
    }
    
    for(i=0; i<(*nr); i++){
        for(j=0; j<(*nc); j++){
            fscanf(fp, "%d/%d", &tmp[i][j].n_p, &tmp[i][j].rot);
        }
    }
    
    fclose(fp);
    return tmp;
}

void disposizioni(Pedina *p, Scacchiera **s, Scacchiera **sol, int nr, int nc, int pos, int *max_p, int *mark, int num_p){
    int i, j, k, punti;
    if(pos>=(nr*nc)){

        punti = controlla(p, s, nr, nc);      //calcolo il punteggio della soluzione corrente
        if(punti>(*max_p)){
            (*max_p)=punti;
            for(int y=0; y<nr; y++){        //salvo la soluzione migliore
                for(int l=0; l<nc; l++){
                    sol[y][l].n_p=s[y][l].n_p;
                    sol[y][l].rot=s[y][l].rot;
                }
            }
        }
        return;
    }
    
    i=pos/nc;       //calcolo delle coordinate della cella nella matrice
    j=pos%nc;
    if(s[i][j].n_p!=-1 && s[i][j].rot!=-1){    //vado avanti dato che la posizione è già occupata
        mark[s[i][j].n_p]=1;
        disposizioni(p, s, sol, nr, nc, pos+1, max_p, mark, num_p);
    }
    else{
        for(k=0; k<num_p; k++){
            if(mark[k]==0){
                s[i][j].n_p=k;          //seleziono la k-esima pedina non ruotata
                s[i][j].rot=0;
                mark[k]=1;
                disposizioni(p, s, sol, nr, nc, pos+1, max_p, mark, num_p);

                s[i][j].n_p=k;          //seleziono la k-esima pedina ruotata
                s[i][j].rot=1;
                mark[k]=1;
                disposizioni(p, s, sol, nr, nc, pos+1, max_p, mark, num_p);

                s[i][j].n_p=-1;         //back track
                s[i][j].rot=-1;
                mark[k]=0;
            }
        }

    }
    
}

int controlla(Pedina *p, Scacchiera **s, int nr, int nc){
    int score=0, p_tmp;
    int i, j, flag=1;
    
    for(i=0; i<nr; i++){        //scorro le righe
        flag=1;         //flag di uscita nel caso su una riga ci siano due colori diversi
        p_tmp=0;        //puntaggio della riga
        for(j=0; j<nc && flag; j++){    //scorro le colonne
            if(j!=nc-1){        //controllo che non sia all'ultima cella, per fare il controllo del colore con la cella successiva
                if(s[i][j].rot==1){
                    if(s[i][j+1].rot==1){
                        if(p[s[i][j].n_p].T2!=p[s[i][j+1].n_p].T2){         //serie di controlli sulla posizione delle pedine e dei rispettivi colori per trovare eventuali diversità nel colore
                            flag=0;
                        }
                    }
                    else{
                        if(p[s[i][j].n_p].T2!=p[s[i][j+1].n_p].T1){
                            flag=0;
                        }
                    }
                }
                else{
                    if(s[i][j+1].rot==1){
                        if(p[s[i][j].n_p].T1!=p[s[i][j+1].n_p].T2){
                            flag=0;
                        }
                    }
                    else{
                        if(p[s[i][j].n_p].T1!=p[s[i][j+1].n_p].T1){
                            flag=0;
                        }
                    }
                }
            }
            if(s[i][j].rot==1){             //calcolo del puntaggio della riga in base alla posizione (ruotata o no) della pedina
                p_tmp += p[s[i][j].n_p].nT2;
            }
            else{
                p_tmp += p[s[i][j].n_p].nT1;
            }
        }
        if(flag){           //aggiornamento del totale complessivo solo nel caso la riga sia composta da pedine dello stesso colore (orizzontale)
            score+=p_tmp;
        }
    }
    
    for(j=0; j<nc; j++){            //procedimento analogo a quelle delle righe ma fatto sulle colonne
        flag=1;                 
        p_tmp=0;
        for(i=0; i<nr && flag; i++){
            if(i!=nr-1){
                if(s[i][j].rot==1){
                    if(s[i+1][j].rot==1){
                        if(p[s[i][j].n_p].T1!=p[s[i+1][j].n_p].T1){
                            flag=0;
                        }
                    }
                    else{
                        if(p[s[i][j].n_p].T1!=p[s[i+1][j].n_p].T2){
                            flag=0;
                        }
                    }
                }
                else{
                    if(s[i+1][j].rot==1){
                        if(p[s[i][j].n_p].T2!=p[s[i+1][j].n_p].T1){
                            flag=0;
                        }
                    }
                    else{
                        if(p[s[i][j].n_p].T2!=p[s[i+1][j].n_p].T2){
                            flag=0;
                        }
                    }
                }
            }
            if(s[i][j].rot==1){
                p_tmp += p[s[i][j].n_p].nT1;
            }
            else{
                p_tmp += p[s[i][j].n_p].nT2;
            }
        }
        if(flag){
            score+=p_tmp;
        }
    }
    
    return score;
}

void my_free(Pedina *p, Scacchiera **s, Scacchiera **sol,int *mark, int nr){
    for(int i=0; i<nr; i++){  //liberazione delle righe delle matrici
        free(s[i]);
        free(sol[i]);
    }
    free(p);        //liberazione dei vettori
    free(s);
    free(sol);
    free(mark);
}