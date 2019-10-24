#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define D 11
#define N_C 8

typedef struct node persona, *link;

struct node {           //definizione della struttura nodo
    char cod[N];
    char nome[N];
    char cognome[N];
    char data[D];
    char via[N];
    char citta[N];
    int cap;
    link next;
};

typedef enum {
    c_tastiera, c_file, c_ricerca, c_codice, c_data, c_fine, c_print, c_help
}command;

link carica_file(link head);
link carica_tastiera(link head);
link ricerca(link head, command cmd, int *c);
link estrazione_data(link *head, link x, link p, int *flag, char *data_i, char *data_f);
void print_list(link head);
void print_help(char tab[][N]);
link new_persona();
command comando(char *cmd, char tab[][N]);


int main() {
    link head=NULL;   //puntatore al primo elemento della lista
    link tmp, x, p, estrazione;
    char command[N], data_i[D], data_f[D];
    char tab[N_C][N]={"tastiera","file","ricerca","codice","data", "fine", "print", "help"};
    int cmd, c;
    int flag=1, flag_data=1;
    
    do{
        printf("Inserire comando ([help] per elenco comandi): ");
        scanf("%s", command);
    
        cmd = comando(command, tab);
        
        switch(cmd){
            case c_tastiera:
                head = carica_tastiera(head);
                break;
            case c_file:
                head = carica_file(head);
                break;
            case c_ricerca:
                c=0;
                tmp = ricerca(head, cmd, &c);
                if(c==0 && tmp==NULL){
                    printf("Errore - Lista vuota.\n");
                }
                else{
                    if(tmp==NULL){
                        printf("Elemento non trovato.\n");
                    }
                    else{
                        printf("%s %s %s %s %s %s %d\n",tmp->cod, tmp->nome, tmp->cognome, tmp->data, tmp->via, tmp->citta, tmp->cap);
                    }
                }
                break;
            case c_codice:
                c=0;
                tmp = ricerca(head, cmd, &c);
                if(c==0 && tmp==NULL){
                    printf("Errore - Lista vuota.\n");
                }
                else{
                    if(tmp==NULL){
                        printf("Elemento non trovato.\n");
                    }
                    else{
                        printf("%s %s %s %s %s %s %d\n",tmp->cod, tmp->nome, tmp->cognome, tmp->data, tmp->via, tmp->citta, tmp->cap);
                    }
                    free(tmp);
                }
                break;
            case c_data:
                flag_data=1;
                tmp = head;
                p = NULL;
                if(tmp==NULL){
                    printf("Errore - Lista vuota.\n");
                    flag_data=0;
                }
                else{
                    printf("Inserire la data di inizio e di fine [gg/mm/aaaa gg/mm/aaaa]: ");
                    if(scanf("%s %s", data_i, data_f)!=2){
                        flag_data=0;
                        printf("Errore - troppi pochi argomenti.\n");
                    }
                    for(x=head; x!=NULL && strcmp(x->data, data_i)<0; p = x, x = x->next);  //scorrimento della lista fino a trovare il primo elemento che sarà da estrarre
                    if(x==NULL){
                        printf("Errore - Nessun elemento compreso nell'intervallo.\n");
                        flag_data=0;
                    }
                    tmp = x;
                }
                while(flag_data){
                    tmp = estrazione_data(&head, tmp, p, &flag_data, data_i, data_f);
                    if(tmp!=NULL){
                        printf("%s %s %s %s %s %s %d\n",tmp->cod, tmp->nome, tmp->cognome, tmp->data, tmp->via, tmp->citta, tmp->cap);  //stampa ed estrazione del nodo selezionato
                        estrazione = tmp;
                        tmp = tmp->next;
                        free(estrazione);
                    }
                }
                break;
            case c_print:
                print_list(head);
                break;
            case c_help:
                print_help(tab);
                break;
            case c_fine:
                flag=0;
                break;
            case -1:
                printf("Errore - comando non esistente.\n");
                break;
            default:
                break;
        }
    }while(flag);
    return 0;
}

command comando(char *cmd, char tab[][N]){     //conversione del comando da stringa a command
    command c = -1;
    for(int i=0; i<N_C; i++){
        if(!strcmp(cmd,tab[i])) {
            c = i;
            break;
        }
    }
    return c;
}

link new_persona(){                         //funzione per la creazione di un nuovo nodo
    link next = (link)malloc(sizeof(*next));
    if(next==NULL){
        printf("Errore allocazione.\n");
    }
    next->next=NULL;
    return next;
}

link carica_tastiera(link head){        //funzione per il caricamento da tastiera di un nuovo nodo
    link tmp, x, p;
    tmp = new_persona(head);
    printf("Inserire <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>: ");
    scanf("%s %s %s %s %s %s %d", tmp->cod, tmp->nome, tmp->cognome, tmp->data, tmp->via, tmp->citta, &(tmp->cap));
    if(head ==  NULL){
        head = tmp;
        return head;
    }
    x=head;
    p=NULL;
    for(x=head;x!=NULL;p=x, x=x->next){             //scorrimento della lista per l'inserimento nella posizione corretta del nuovo nodo
        if(strcmp(tmp->data,x->data)<0){
            tmp->next=x;
            if(x==head)
                head=tmp;
            else
                p->next=tmp;
            return head;                          
        }
    }
    p->next=tmp;
    return head;
}

link carica_file(link head){        //caricamento della lista da file
    FILE *fp;
    int flag=0;
    char file[N];
    
    printf("Inserire nome del file: ");
    scanf("%s", file);
    
    fp = fopen(file, "r");
    if(fp == NULL){
        printf("Errore apertura file.\n");
        return NULL;
    }
    
    link tmp, x, p;
    tmp = new_persona(head);
    while(!feof(fp)){
        tmp = new_persona(head);
        fscanf(fp,"%s %s %s %s %s %s %d", tmp->cod, tmp->nome, tmp->cognome, tmp->data, tmp->via, tmp->citta, &(tmp->cap));
        if(fp!=EOF){
            if(head ==  NULL){
                head = tmp;
            }
            else{
                x=head;
                p=NULL;
                flag=0;
                for(x=head;x!=NULL;p=x, x=x->next){     //scorrimento della lista per l'inserimento nella posizione corretta del nuovo nodo
                    if(strcmp(tmp->data,x->data)<0){
                        tmp->next=x;
                        if(x==head){        //controllo che il nodo non sa da inserire in testa all lista
                            head=tmp;
                            flag=1;
                        }
                        else{
                            p->next=tmp;    //inserimento del nodo in mezzo alla lista
                            flag=1;
                        }
                        break;                          
                    }
                }
                if(!flag){
                    p->next=tmp;        //inserimento del nodo in coda alla lista
                }
            }
        }
        else
            free(tmp);
    }
    
    fclose(fp);
    return head;
}

link ricerca(link head, command cmd, int *c){
    link x, p=NULL;
    char cod[N];
    
    if(head==NULL)
        return head;
    
    printf("Inserire il codice: ");
    scanf("%s", cod);
    
    for(x=head; x!=NULL; p = x, (*c)++, x = x->next){   //ricerca lineare per codice
        if(!strcmp(x->cod, cod)){
            if(cmd==c_ricerca){         //nel caso il comando c_ricerca
                return x;
            }
            else{                   //nel caso il comando sia c_codice
                p = x->next;        //assegnazione per la successiva liberazione di x
                return x;
            }
        }
    }
}

link estrazione_data(link *head, link x, link p, int *flag, char *data_i, char *data_f){
    if(strcmp(x->data,data_i)>=0 && strcmp(x->data, data_f)<=0){  //controllo che il nodo sia conpreso nell'intervallo di date specificato
        if(p==NULL){
            (*head) = x->next;
        }
        else{
            if(x->next!=NULL)
                p->next = x->next;
        }
        return x;       //ritorno del nodo da estrarre
    }
    else{
        (*flag)=0;
        return NULL;
    }
}

void print_list(link head){
    FILE *fp;
    link x;
    char file[N];
    
    if(head==NULL){
        printf("Errore - Lista vuota.\n");
        return;
    }
    
    printf("Inserire il nome del file: ");
    scanf("%s", file);
    
    fp=fopen(file, "w");
    if(fp==NULL){
        printf("Errore paertura file\n");
        return;
    }
    
    for(x=head; x!=NULL; x = x->next){
        fprintf(fp, "%s %s %s %s %s %s %d\n",x->cod, x->nome, x->cognome, x->data, x->via, x->citta, x->cap);
    }
    
    fclose(fp);
}

void print_help(char tab[][N]){
    for(int i=0; i<N_C; i++){
        printf("-%s: ", tab[i]);
        switch(i){
            case c_tastiera:
                printf("Inserimento di un nodo da tastiera\n");
                break;
            case c_file:
                printf("Inserimento di uno o piu' nodi da file\n");
                break;
            case c_ricerca:
                printf("Ricerca di un nodo per codice [AXXXX]\n");
                break;
            case c_codice:
                printf("Estrazione di un nodo per codice [AXXXX]\n");
                break;
            case c_data:
                printf("Estrazione dei nodi compresi in dato intervallo di date\n");
                break;
            case c_print:
                printf("Stampa della lista su file\n");
                break;
            case c_help:
                printf("Stampa elenco dei comandi\n");
                break;
            case c_fine:
                printf("Termina l'esecuzione\n");
                break;
            default:
                break;
        }
    }
}