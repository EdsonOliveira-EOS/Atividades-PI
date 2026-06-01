#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checknull (void *pointer){
    if (pointer == NULL){
        printf ("Não alocado.\n");
        exit(1);
    }
}

typedef struct Tarefa {
    int id;
    int prioridade;
    struct Tarefa *prox; 
} Tarefa;

void inserir (int id, int prioridade, Tarefa **startpointer, Tarefa **endpointer){

    Tarefa *nova = malloc(sizeof(Tarefa));
    checknull(nova);

    nova->id = id;
    nova->prioridade = prioridade;
    nova->prox = NULL;

    if (*startpointer == NULL){ 
        (*startpointer) = nova;
        (*endpointer) = nova;
    } else { 
        (*endpointer)->prox = nova;
        (*endpointer) = nova;
    }
}       

void remover (Tarefa **startpointer, Tarefa **endpointer){
    if ((*startpointer) == NULL){ 
        printf ("Fila vazia\n");
        return;
    }
    
    Tarefa *temp = (*startpointer);
    printf ("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);
    
    (*startpointer) = (*startpointer)->prox;

    if ((*startpointer) == NULL){
        (*endpointer) = NULL;
    }
    free (temp);
}

void listar (Tarefa *startpointer){
    if (startpointer == NULL){ 
        printf ("Fila vazia\n");
    } else {
        Tarefa *atual = startpointer;
        while (atual != NULL){
            printf ("id=%d prioridade=%d\n", atual->id, atual->prioridade);
            atual = atual->prox;
        }
    }
}

int main(){
    Tarefa *startpointer = NULL;
    Tarefa *endpointer = NULL;

    char comando;
    while (scanf(" %c", &comando) == 1 && comando != 'F'){
        int id, prioridade;
        switch(comando){
            case 'I': 
                scanf (" %d %d", &id, &prioridade);
                inserir(id, prioridade, &startpointer, &endpointer);
                break;
            case 'R': 
                remover(&startpointer, &endpointer);
                break;
            case 'L': 
                listar(startpointer);
                break;
        }
    }
    while (startpointer != NULL) {
        Tarefa *temp = startpointer;
        startpointer = startpointer->prox;
        free(temp);
    }

    return 0;
}