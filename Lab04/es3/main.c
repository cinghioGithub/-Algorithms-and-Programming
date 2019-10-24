#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define N 20

int start=0;

char *cercaRegexp(char *src, char *regexp);
int gestioneMeta(char *p1, char *p2, int *n, int *i, int k);

int main() {
    char regexp[N] ="\\A[aeiou]5t[123]";
    char line[MAX] = "Ma5t2";
    char *word = line;                   //assegnazione fittizia
    int i=0;

    while(word!=NULL) {
        word = cercaRegexp(line, regexp);
        i=0;
        if(word!=NULL) {
            while (*(word + i) != ' ' && *(word + i) != '\0') {
                printf("%c", *(word + i));
                i++;
            }
            printf(" ");
        }
    }

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i=0, j=0, count=0, c_alpha=0, k=0;
    int flag=0;
    int len_src = strlen(src), len_reg = strlen(regexp);

    for(i=0; i<len_reg; i++){
        if(regexp[i]=='\\'){
            c_alpha++;
            i++;
        }
        else if(regexp[i]=='['){
            c_alpha++;
            i++;
            if(regexp[i]=='^') i++;
            while(isalnum(regexp[i])){
                i++;
            }
        }
        else {
            c_alpha++;
        }
    }

    for(i=start; i<=len_src-c_alpha; i++){
        count=0;
        flag=0;
        k=0;
        for(j=0; j<len_reg && flag==0; j++){
            if(regexp[j]!='.'&& regexp[j]!='\\' && regexp[j]!='[' ){
                if(regexp[j]==src[k+i])
                    count++;
            }
            else
                if(!gestioneMeta(regexp, src, &count, &j,k+i)){
                    flag=1;
                }
            k++;
        }
        if(i==len_src-c_alpha || flag==0) {
            if (count == c_alpha) {
                start = i + c_alpha;
                return &src[i];
            }
        }
    }
    return NULL;
}

int gestioneMeta(char *p1, char *p2,int *n, int *i, int k){
    int flag=0;
    int c=0, ind=(*i);
    switch(p1[ind]) {
        case '.':
            if (isalpha(p2[k])) {
                (*n)++;
                flag=1;
            }
            break;
        case '\\':
            if ((p1[ind+1])=='A') {
                if (isupper(p2[k]) && isalpha(p2[k])) {
                    (*n)++;
                    flag = 1;
                }
            }
            else if((p1[ind+1])=='a'){
                if (islower(p2[k]) && isalpha(p2[k])) {
                    (*n)++;
                    flag = 1;                  
                }
            }
            (*i)++;
            break;
        case '[':
            ind++;
            while (p1[ind] != ']') {
                c++;
                if (p1[ind] != '^') {
                    if (p1[ind] == p2[k]) {
                        (*n)++;
                        flag=1;
                    }
                }
                else{
                    ind++;
                    if(p1[ind] != p2[k]){
                        (*n)++;
                        flag=1;
                    }
                }
                ind++;
            }
            (*i)=ind;
            break;
        default:
            break;
    }
    return flag;
}