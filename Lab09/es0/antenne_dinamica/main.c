#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char** argv) {
    int antenne[N] = {0, 14, 22, 13, 25, 30, 11, 90};
    int cop[N]={0};
    int sol[N];
    
    cop[1]=antenne[1];
    
    //find best solution
    for(int i=2; i<N; i++){
        if(cop[i-1]>cop[i-2]+antenne[i]){
            cop[i]=cop[i-1];
        }
        else{
            cop[i]=cop[i-2]+antenne[i];
        }
    }
    
    //show best solution
    for(int i=N-1; i>=2; i--){
        if(cop[i]==cop[i-1]){
            sol[i]=0;
        }
        if(cop[i]==cop[i-2]+antenne[i]){
            sol[i]=1;
            sol[i-1]=0;
            i--;
        }
    }
    
    for(int i=0; i<N; i++){
        if(sol[i]!=0)
            printf("%d ", i);
    }
    return (EXIT_SUCCESS);
}

