#include <stdio.h>
#include <stdlib.h>

typedef struct nodo node, *link;

struct nodo{
    int val;
    link next;
};

link newnode(link h);

int main() {
    link head=NULL;
    
    while(1){
        head = newnode(head);
        for(link i=head; i!=NULL; i=i->next)
            printf("%d\n", i->val);
    }
    return 0;
}

link newnode(link h){
    int val;
    link i,x = (link)malloc(sizeof(node));
    x->next=NULL;
    if(h==NULL){
        h=x;
        printf("Ins val: ");
        scanf("%d", &(h->val));
        return h;
    }
    
    for( i=h; i->next!=NULL; i=i->next);
    i->next=x;
    printf("Ins val: ");
    scanf("%d", &((i->next)->val));  
    return h;
}

