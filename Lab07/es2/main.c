#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef struct gioielli{
    char sigla;
    int num;
}pietre;

void collane(char *best_sol, char *sol, int n,int pos, pietre *pietra, int max_rip, int n_z,int n_s,int n_r,int n_t, int val_z,int val_s,int val_r,int val_t, int *max_val, int *n_max);
int check(int n, char *sol, int max_rip, int n_z,int n_s,int n_r,int n_t, int val_z,int val_s,int val_r,int val_t, int *val);
int controlla_pietra(char primo, char secondo, int i);

int main() {
    pietre pietra[4];
    int tot, max_rip, max_val=0, n_max;
    int n_z=0, n_s=0, n_r=0, n_t=0;
    int val_z, val_s, val_r, val_t;
    char *sol, *best_sol;
    int i, pos=0;
    
    printf("Inerire numero [zaffiri] [smeraldi] [rubini] [topazi]: ");
    scanf("%d %d %d %d", &pietra[0].num, &pietra[1].num, &pietra[2].num, &pietra[3].num);
    printf("Inserire [val_z] [val_s] [val_r] [val_t] [max_rip]: ");
    scanf("%d %d %d %d %d", &val_z, &val_s, &val_r, &val_t, &max_rip);
    for(int i=0; i<N; i++){
        tot += pietra[i].num;
    }
    pietra[0].sigla = 'z';
    pietra[1].sigla = 's';
    pietra[2].sigla = 'r';
    pietra[3].sigla = 't';
    best_sol = (char *)malloc(tot*sizeof(char));
    sol = (char *)malloc(tot*sizeof(char));
    for(i=tot; i>=1; i--){
        if(sol == NULL){
            printf("Errore allocazione\n");
            exit(1);
        }
        collane(best_sol, sol, i, pos, pietra, max_rip, n_z, n_s, n_r, n_t, val_z, val_s, val_r, val_t,&max_val, &n_max);
    }
    
    printf("La collana e' lunga %d, di valore %d\n", n_max, max_val);
    printf("Collana: ");
    for(i=0; i<n_max; i++){
        printf("%c", best_sol[i]);
    }
    free(sol);
    free(best_sol);
    return 0;
}

void collane(char *best_sol, char *sol, int n,int pos, pietre *pietra, int max_rip, int n_z,int n_s,int n_r,int n_t, int val_z,int val_s,int val_r,int val_t, int *max_val, int *n_max){
    int i, val=0;
    if(pos>=n){
        if(check(n, sol, max_rip, n_z, n_s, n_r, n_t, val_z, val_s, val_r, val_t, &val)){
            if(val>(*max_val)){
                (*max_val)=val;
                (*n_max)=n;
                for(int j=0; j<n; j++){
                    best_sol[j]=sol[j];
                }
            }
        }
        return;
    }
    
    for(i=0; i<N ; i++){
        if(pietra[i].num>0 && controlla_pietra(sol[pos-1], pietra[i].sigla, pos)){
            sol[pos]=pietra[i].sigla;
            pietra[i].num--;
            collane(best_sol, sol, n, pos+1, pietra, max_rip, n_z, n_s, n_r, n_t, val_z, val_s, val_r, val_t, max_val, n_max);
            pietra[i].num++;
        }
    }
    return;
}

int check(int n, char *sol, int max_rip, int n_z,int n_s,int n_r,int n_t, int val_z,int val_s,int val_r,int val_t, int *val){
    int i, flag=1;
    int nz=0, ns=0, nr=0 ,nt=0;
    n_z=0; n_s=0; n_t=0; n_r=0;
    for(i=0; i<n && flag==1; i++){
        if(i==n-1){
            switch(sol[i]){
                case 'z':
                    n_z++;
                    break;
                case 's':
                    n_s++;
                    break;
                case 'r':
                    n_r++;
                    break;
                case 't':
                    n_t++;
                    break;
            }
        }
        else{
            switch(sol[i]){
                case 'z':
                    nz=0;
                    while(sol[i]=='z' && i<n){
                        nz++;
                        n_z++;
                        i++;
                    }
                    if(i>=n-1)
                        break;
                    i--;
                    if(nz>max_rip){
                        flag=0;
                    }
                    else{
                        if(sol[i+1]!='z' && sol[i+1]!='r')
                            flag=0;
                    }
                    break;
                case 's':
                    ns=0;
                    while(sol[i]=='s'&& i<n){
                        n_s++;
                        ns++;
                        i++;
                    }
                    if(i>=n-1)
                        break;
                    i--;
                    if(ns>max_rip){
                        flag=0;
                    }
                    else{
                        if(sol[i+1]!='s' && sol[i+1]!='t')
                            flag=0;
                    }
                    break;
                case 'r':
                    nr=0;
                    while(sol[i]=='r'&& i<n){
                        n_r++;
                        nr++;
                        i++;
                    }
                    if(i>=n-1)
                        break;
                    i--;
                    if(nr>max_rip){
                        flag=0;
                    }
                    else{
                        if(sol[i+1]!='s' && sol[i+1]!='t')
                            flag=0;
                    }
                    break;
                case 't':
                    nt=0;
                    while(sol[i]=='t'&& i<n){
                        n_t++;
                        nt++;
                        i++;
                    }
                    if(i>=n-1)
                        break;
                    i--;
                    if(nt>max_rip){
                        flag=0;
                    }
                    else{
                        if(sol[i+1]!='z' && sol[i+1]!='r')
                            flag=0;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if(n_z>n_s)
        flag=0;
    (*val) = val_z* n_z + val_s* n_s + val_r* n_r + val_t* n_t;
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