#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(int argc, char *argv[]) {
    Grafo g;
    int *k;
    
    if(argc!=4)
        exit(1);
    
    g = Init();
    carica_Grafo(g, argv[1]);  
    Test_Kernel(g, argv[2]);     
    k = Max_Kernel(g, argv[3]);     
    cammini_semplici(g, k);
    libera_Grafo(g);
    
    return 0;
}

