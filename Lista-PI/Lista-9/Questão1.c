#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checknull (void *pointer){
    if (pointer == NULL){
        printf ("Não alocado.\n");
        exit(1);
    }
}

typedef struct node {
    char data;
    struct node *nextpointer;
} Node;

void push (char info, Node **top){
    Node *nova = malloc (sizeof(Node));
    checknull (nova);

    nova->data = info;        
    nova->nextpointer = *top;   
    *top = nova;                
}

void pop (Node **top){
    if (*top == NULL) return;

    Node *aux = *top;
    *top = (*top)->nextpointer; 
    free(aux);
}

void printstack(Node *top) {
    Node *nova = top;

    while (nova != NULL){
        printf ("%c\n", nova->data);
        nova = nova->nextpointer;
    }
}

char verificar_fusao(char c1, char c2) {
    if ((c1 == 'g' && c2 == 'b') || (c1 == 'b' && c2 == 'g')) return 'c';
    if ((c1 == 'r' && c2 == 'b') || (c1 == 'b' && c2 == 'r')) return 'm';
    if ((c1 == 'r' && c2 == 'g') || (c1 == 'g' && c2 == 'r')) return 'y';
    return 0; 
}

void checar_reacoes(Node **top) {
    while (1) {
        if (*top == NULL || (*top)->nextpointer == NULL) break;

        char cor1 = (*top)->data;
        char cor2 = (*top)->nextpointer->data;
        char nova_cor = verificar_fusao(cor1, cor2);

        if (nova_cor != 0) {
            pop(top);
            pop(top);
            push(nova_cor, top);
            continue;
        }

        if ((*top)->nextpointer->nextpointer != NULL) {
            char cor3 = (*top)->nextpointer->nextpointer->data;

            if (cor1 == cor2 && cor2 == cor3) {
                pop(top);
                pop(top);
                pop(top);
                continue; 
            }
        }
        break;
    }
}

int main (){
    Node *top = NULL;
    char c;

    while (scanf(" %c", &c) != EOF){
        push(c, &top);
        checar_reacoes(&top);
        
        if (top == NULL){
            printf ("Pilha vazia!\n\n");
        } else {
            printstack(top);
            printf ("\n");
        }
    }
    printf("Thank You So Much For Playing My Game!\n");
    while (top != NULL){pop(&top);}
    
    return 0;
}