#include <stdio.h>
#include <stdlib.h>

#define maxN 10

void ruota(int V[], int N){
    int sup=0;
    for(int i=0; i<N;i++){
        sup = V[maxN-1];
        for(int j=maxN-1;j>0;j--){
            V[j]=V[j-1];
        }
        V[0]=sup;
    }
}

int main() {
    int V[maxN];
    int N=0,dir=0, i=0;

    printf("Inserire il vettore: ");
    for( i=0; i<maxN;i++) {
        scanf("%d",&V[i]);
    }

    printf("Inserire il numero di traslazioni: ");
    scanf("%d",&N);

    ruota(V,N);

    for(i=0;i<maxN;i++){
        printf("%d ", V[i]);
    }
    return 0;
}