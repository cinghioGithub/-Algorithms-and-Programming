#ifndef _GRAFO
#define _GRAFO

typedef struct grafo *Grafo;

void carica_Grafo(Grafo g, char *nome);
Grafo Init();
void Test_Kernel(Grafo g, char *nome);
int *Max_Kernel(Grafo g, char *str);
void libera_Grafo(Grafo g);
void cammini_semplici(Grafo g, int *k);

#endif 