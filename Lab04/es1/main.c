#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main() {
    int a,b;
    printf("Inerire due numero [a b]: ");
    scanf("%d %d", &a,&b);
    printf("Il MCD vale: %d", gcd(a,b));
    return 0;
}

int gcd(int a, int b){
    if(a==b) return a;

    if(a%2==0 && b%2==0) return 2*gcd(a/2,b/2);

    if (a%2!=0 && b%2!=0) {
        if(a>b) return gcd((a-b)/2,b);
        return gcd(a,(b-a)/2);
    }

    if(a%2==0) {return gcd(a/2,b);}
    else return gcd(a,b/2);
}