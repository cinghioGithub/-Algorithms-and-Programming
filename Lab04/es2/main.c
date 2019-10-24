#include <stdio.h>
#include <stdlib.h>

int majority(int *a, int l, int r, int N);
int ricombinazione(int A[], int a, int b, int i, int f, int N);

int main() {
    int a[7]={5,2,5,4,5,6,5};
    int N=7;

    printf("%d",majority(a,0,N-1,N));
    return 0;
}

int majority(int *A, int l, int r, int N) {
    int a=0, b=0;
    if(N%2==0) {
        if (N == 2) {
            if (A[l] == A[r])
                return A[l];
            else
                return -1;
        }

        a = majority(A, l, N / 2 - 1, N / 2);
        b = majority(A, N / 2, r, N / 2);
        return ricombinazione(A, a, b, l, r, N);
    }
    else{
        if (N == 1) {
            return A[l];
        }

        a = majority(A, l, N / 2 -1, N / 2);
        b = majority(A, N / 2, r, N / 2);
        return ricombinazione(A, a, b, l, r, N);
    }
}

int ricombinazione(int A[], int a, int b, int i, int f, int N){
    int count=0;
    if(a!=-1){
        for(int j=i; j<=f; j++){
            if(A[j]==a) count++;
        }
        if(count>N/2) return a;
    }
    else{
        if(b!=-1){
            for(int j=i; j<=f; j++){
                if(A[j]==b) count++;
            }
        if(count>N/2) return b;
        }
        else
            return -1;
    }
}