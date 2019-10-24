#include <stdio.h>
#include <stdlib.h>

#define MAX 101
#define N_D 3
#define N_EL 5
#define DD 4
#define DP 

typedef struct elementi{
    char nome[MAX];
    int tipo;
    int dir_in;
    int dir_out;
    int prec;
    int end;
    float valore;
    int diff;
}Elementi;

Elementi *carica_file(int *n);
void crea_diagonali_w(Elementi *el, int n);
void genera_diagonali(Elementi *el, int n, int pos, int *mark, int *sol, int dim, float *dif, int i);

int main() {
    Elementi *elementi;
    int num=0;
    
    elementi = carica_file(&num);
    
    crea_diagonali_w(elementi, num);
/*
    for(int i=0; i<num; i++){
        printf("%s %d %d %d %d %d %f %d\n", elementi[i].nome, elementi[i].tipo, elementi[i].dir_in, elementi[i].dir_out, elementi[i].prec, elementi[i].end, elementi[i].valore, elementi[i].diff);
    }
*/
    
    return 0;
}

Elementi *carica_file(int *n){
    FILE *fp;
    Elementi *el;
    
    fp=fopen("elementi.txt", "r");
    if(fp==NULL){
        printf("Errore apertura file.\n");
        exit(-1);
    }
    
    fscanf(fp, "%d", n);
    el = (Elementi *)malloc((*n)*sizeof(Elementi));
    for(int i=0; i<(*n); i++){
        fscanf(fp, "%s %d %d %d %d %d %f %d", el[i].nome, &el[i].tipo, &el[i].dir_in, &el[i].dir_out, &el[i].prec, &el[i].end, &el[i].valore, &el[i].diff);
    }
    
    fclose(fp);
    return el;
}

int check_diag (Elementi *el, int ind, int *sol, int dim, float *dif){
    int i;
    int flag=0, flag_dif=0;
    
    for(i=0; i<dim; i++){                   //controllo che ci sia almeno un elemento acrobatico nella diagonale
        if(el[sol[i]].tipo==2 || el[sol[i]].tipo==1){
            flag=1;
        }
    }
    if(!flag)
        return 0;
    
    for(i=1; i<dim; i++){               //controllo che la direzione di uscita di ogni elemento corrisponda a quella di entrata dell'elemento successivo
        if(el[sol[i-1]].dir_out!=el[sol[i]].dir_in){
            return 0;
        }
    }
    
    return 1;
}

void genera_diagonali(Elementi *el, int n, int pos, int *mark, int *sol, int dim, float *dif, int i){  //calcolo il power set permutando gli elementi di ogni soluzione
    int i;
    
    if(pos>=dim){
        if(check_diag(el, i, sol, dim, dif)){
            
            //aggiungere la diagonale al vettore di diagonali
            
            (*dif)=0;
            return 1;
        }
        return 0;
    }
    
    for(i=0; i<n; i++){     //mettere pruning su entrata e uscita
/*
        if(pos!=0){
            if(mark[i]==0){
                if(el[pos-1].dir_out==el[i].dir_in){
                    dif += el[i].diff;
                    if(dif>DD)
                        return;
                    mark[i]=1;
                    sol[pos]=i;
                    genera_diagonali(el, n, pos+1, mark, sol, dim, dif);
                    mark[i]=0;
                }
            }
        }
        else{
            if(mark[i]==0){
                dif += el[i].diff;
                if(dif>DD)
                    return;
                mark[i]=1;
                genera_diagonali(el, n, pos+1, mark, sol, dim, dif);
                mark[i]=0;
            }
        }
*/
        if(mark[i]==0){
            (*dif) += el[i].diff;
            if((*dif)<=DD){
                mark[i]=1;
                sol[pos]=i;
                genera_diagonali(el, n, pos+1, mark, sol, dim, dif, i);
                mark[i]=0;
            }
        }
    }
        
}

void crea_diagonali_w(Elementi *el, int n){
    int i, j, *sol, *mark;
    float dif=0;
    int **diag=(int **)malloc(N_D*sizeof(int *));
    int num_diag=N_D;
    
    mark = (int *)calloc(N_EL, sizeof(int));
    
/*
    for(i=0; i<num_diag; i++){
        diag[i]=NULL;
    }
*/
    
    //for(i=0; i<N_D; i++){
        for(j=0; j<=N_EL; j++){
            sol = (int *)malloc(j*sizeof(int));
            genera_diagonali(el, n, 0, mark, sol, j, &dif);
        }
    //}
    
}