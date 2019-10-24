#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main() {
    Grafo g;
    
    g = init(g);
    carica_grafo(g);
    
    power_set(g);
    
    max_dist(g);
    return 0;
}

