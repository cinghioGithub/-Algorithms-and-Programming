#include <stdio.h>
#include <stdlib.h>

#define N 10

int insert(int V[]){
    int i=0;
    for(i=0; i<N; i++){
        scanf("%d",&V[i]);
    }
    return V;
}
            
void print(int V[]){
    printf("\n");
    int i=0;
    while(i<N && V[i]!=0){
        printf("%d\n",V[i]);
        i++;
    }
}

int zero(int sup[]){
    int i=0;
    for(i=0;i<N;i++){
        sup[i]=0;
    }
    return sup;
}


int main(int argc, char** argv) {
    
    int V[N];
    int sup[N];
    int max=0,i=0,c=0,j=0;
    
    insert(V);
    zero(sup);
    
    while(i<N){
        if(V[j]==0) j++;
        c=0;
        while(V[j]!=0 && j<N){
            c++;
            j++;
        }
        if (c>max) max=c;
        i++;
    }
    
    i=0; j=0;
    while(i<N){
        zero(sup);
        c=0;
        if(V[j]==0) j++;
        while(V[j]!=0 && j<N){
            sup[c]=V[j];
            c++;
            j++;
        }
        c=0;
        while(sup[c]!=0 && c<N){
            c++;
        }
        if(c==max){
            print(sup);
        }
        
        i=j;;
    }
   
    return 0;
}

