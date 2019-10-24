#ifndef _GRAFO
#define _GRAFO

typedef struct grafo *Grafo;
typedef struct node *link;

Grafo grafo_init();
link new_node();
void free_lista(link *ladj, int n);
int **adj_init(int v);
void carica_grafo(Grafo g);
void print_grafo(Grafo g);
void genera_lista(Grafo g);
void print_elenco(Grafo g);
void adiacenti(Grafo g);
void adiacenti_lista(Grafo g);
void free_grafo(Grafo g);
void print_tabella_G(Grafo g);

#endif 

