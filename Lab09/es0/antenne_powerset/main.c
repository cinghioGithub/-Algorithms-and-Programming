#include <stdio.h>
#include <stdlib.h>

#define N 8

void powerset(int *antenne, int *mark,int pos );

int main(int argc, char** argv) {

    
    int antenne[N] = {0, 14, 22, 13, 25, 30, 11, 90};
    int mark[N]={0};
    
    
    powerset(antenne, mark, 0);
    
    return (EXIT_SUCCESS);
}

void powerset(int *antenne, int *mark,int pos ){
    int i;
    if(pos>=N){
        for(int j=1; j<N; j++){
            if(mark[j]!=0){
                printf("%d ", antenne[j]);
            }
        }
        printf("\n");
        return;
    }
    
    mark[pos]=1;
    powerset(antenne, mark, pos+1);
    mark[pos]=0;
    powerset(antenne, mark, pos+1);
}
