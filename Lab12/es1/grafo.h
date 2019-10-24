#ifndef _GRAFO
#define _GRAFO

typedef struct grafo *Grafo;
typedef struct edge {
    int a;
    int b;
    int w;
}Edge;

Grafo init(Grafo g);
void free_grafo(Grafo g);
void carica_grafo(Grafo g);
void power_set(Grafo g);
void max_dist(Grafo g);
void print_grafo(Grafo g);

#endif

