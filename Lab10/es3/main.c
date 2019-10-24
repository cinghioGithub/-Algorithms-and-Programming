#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

#define N 100
#define N_C 6

typedef enum elenco {
    c_lista, c_elenco, c_adiacenti_mat, c_adiacenti_list, c_menu, c_fine
}cmd;

cmd gestione_comando(char *cod, char **tab);
void print_menu(char **tab);

int main() {
    int flag=1;
    Grafo g;
    char command[N];
    cmd c;
    char *tab[N_C] = {"lista", "elenco", "adiacenti_mat", "adiacenti_list", "help", "fine"};
    
    g = grafo_init();
    carica_grafo(g);
    
    do{
        printf("Inserire comando [help per lista comandi]: ");
        scanf("%s", command);
        
        c = gestione_comando(command, tab);
        
        switch(c){
            case c_lista:
                genera_lista(g);
                break;
            case c_elenco:
                print_elenco(g);
                break;
            case c_adiacenti_mat:
                adiacenti(g);
                break;
            case c_adiacenti_list:
                adiacenti_lista(g);
                break;
            case c_menu:
                print_menu(tab);
                break;
            case c_fine:
                flag=0;
                break;
            case -1:
                printf("Errore - \"%s\" comando non esistente.\n", command);
                break;
            default:
                break;
        }       
    }while(flag);
    
    free_grafo(g);
    
    return 0;
}

cmd gestione_comando(char *cod, char **tab){
    cmd i;
    
    for(i=0; i<N_C; i++){
        if(!strcmp(cod, tab[i])){
            return i;
        }
    }
    
    return -1;
} 

void print_menu(char **tab){
    int i;
    
    for(i=0; i<N_C; i++){
        switch(i){
            case c_lista:
                printf("%s - genera lista delle adiacenze.\n", tab[i]);
                break;
            case c_elenco:
                printf("%s - eleno alfabetico dei vertici con i rispettivi archi.\n",tab[i]);
                break;
            case c_adiacenti_mat:
                printf("%s - verifica di adiacienza a coppie fra 3 vertici inseriti [matrice delle adicenze].\n",tab[i]);
                break;
            case c_adiacenti_list:
                printf("%s - verifica di adiacienza a coppie fra 3 vertici inseriti [lista delle adicenze].\n",tab[i]);
                break;
            case c_menu:
                printf("%s - stampa elenco dei comandi.\n",tab[i]);
                break;
            case c_fine:
                printf("%s - termina del programma.\n",tab[i]);
                break;
            default:
                break;
        }
    }
}