#include <stdio.h>
#include <stdlib.h>
#include "data.h"

Data carica_data(char *d){
    Data data;
    sscanf(d, "%d/%d/%d", &data.anno, &data.giorno, &data.mese);
    return data;
}

int data_cmp(Data d1, Data d2){         //confronto di date 1 se d1>d2, -1 se d1<d2, 0 se d1==d2
    if(d1.anno > d2.anno){
        return 1;
    }
    else {
        if(d1.anno < d2.anno)
            return -1;
        else{
            if(d1.mese > d2.mese)
                return 1;
            else{
                if(d1.mese < d2.mese)
                    return -1;
                else{
                    if(d1.giorno > d2.giorno)
                        return 1;
                    else{
                        if(d1.giorno < d2.giorno)
                            return -1;
                        else
                            return 0;
                    }
                }
            }
        }
    }
}