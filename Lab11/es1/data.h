#ifndef _DATA
#define _DATA

typedef struct data {
    int anno, mese, giorno;
}Data;

Data carica_data(char *d);
int data_cmp(Data d1, Data d2);

#endif

