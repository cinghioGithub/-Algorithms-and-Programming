#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct gioielli{
    char sigla;
    int num;
}pietre;

void wrapper_collane(int tot, char *sol, pietre *pietra);
void collane(char *sol, int n,int pos, pietre *pietra, int *controll);
int check(int n, char *sol);
int controlla_pietra(char primo, char secondo, int i);

int main() {
    pietre pietra[4];
    int tot;
    char *sol;
    
    wrapper_collane(tot, sol, pietra);
    
    
    return 0;
}

void wrapper_collane(int tot, char *sol, pietre *pietra){
    int i, pos=0, controll=0;
    printf("Inerire numero [zaffiri] [smeraldi] [rubini] [topazi]: ");
    scanf("%d %d %d %d", &pietra[0].num, &pietra[1].num, &pietra[2].num, &pietra[3].num);
    for(int i=0; i<N; i++){
        tot += pietra[i].num;
    }
    pietra[0].sigla = 'z';
    pietra[1].sigla = 's';
    pietra[2].sigla = 'r';
    pietra[3].sigla = 't';
    for(i=tot; i>=1; i--){
        sol = (char *)malloc(i*sizeof(char));
        if(sol == NULL){
            printf("Errore allocazione\n");
            exit(1);
        }
        collane(sol, i, pos, pietra, &controll);
        free(sol);
    }
}

void collane(char *sol, int n,int pos, pietre *pietra, int *controll){
    int i;
    if(pos>=n){
        if(check(n, sol)){
            (*controll)=1;
            printf("Lunghezza collana: %d\n", n);
            for(int k=0; k<n; k++)
                printf("%c ", sol[k]);

            printf("\n");
        }
        return;
    }
    
    for(i=0; i<N && (*controll)==0; i++){
        if(pietra[i].num>0 && controlla_pietra(sol[pos-1], pietra[i].sigla, pos)){
            sol[pos]=pietra[i].sigla;
            pietra[i].num--;
            collane(sol, n, pos+1, pietra, controll);
            pietra[i].num++;
        }
    }
        return;
}

int check(int n, char *sol){
    int i, flag=1;
    for(i=0; i<n-1 && flag==1; i++){
        switch(sol[i]){
            case 'z':
                if(sol[i+1]!='z' && sol[i+1]!='r')
                    flag=0;
                break;
            case 's':
                if(sol[i+1]!='s' && sol[i+1]!='t')
                    flag=0;
                break;
            case 'r':
                if(sol[i+1]!='s' && sol[i+1]!='t')
                    flag=0; 
                break;
            case 't':
                if(sol[i+1]!='z' && sol[i+1]!='r')
                    flag=0;
                break;
            default:
                break;
        }
    }
    return flag;
}

int controlla_pietra(char primo, char secondo, int pos){
    int flag=1;
    if(pos==0) return flag;
    switch(primo){
        case 'z':
            if(secondo!='z' && secondo!='r')
                flag=0;
            break;
        case 's':
            if(secondo!='s' && secondo!='t')
                flag=0;
            break;
        case 'r':
            if(secondo!='s' && secondo!='t')
                flag=0; 
            break;
        case 't':
            if(secondo!='z' && secondo!='r')
                flag=0;
            break;
        default:
            break;
    }
    return flag;
    
}