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
    struct Tarefa *nextpointer;
} Tarefa;

void inserir (int id, int prioridade, Tarefa **startpointer, Tarefa **endpointer){

    // Alocar dinamicamente
    Tarefa *nova = malloc(sizeof(Tarefa));
    checknull(nova);

    // Colocar os dados
    nova->id = id;
    nova->prioridade = prioridade;
    nova->nextpointer = NULL;

    // Se startpointer == NULL, quer dizer que a lista está vazia.
    if (*startpointer == NULL){ 
        (*startpointer) = nova;
        (*endpointer) = nova;
    } else { 
        // Se não tá vazia, o ponteiro do fim vai apontar para o próximo da lista e o ponteiro do final vai apontar para NULL
        (*endpointer)->nextpointer = nova;
        (*endpointer) = nova;
    }
}       

void remover (Tarefa **startpointer, Tarefa **endpointer){
    if ((*startpointer) == NULL){ // Se a lista estiver vazia
        printf ("Fila vazia\n");
        return;
    }
    
    Tarefa (*temp) = (*startpointer);
    printf ("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);
    
    (*startpointer) = (*startpointer)->nextpointer;

    if ((*startpointer) == NULL){
        (*endpointer) = NULL;
    }
    free (temp);
}
void listar (Tarefa *startpointer){
    if (startpointer == NULL){ // Se a lista estiver vazia
        printf ("Fila vazia\n");
    } else {
        Tarefa *atual = startpointer;
        while (atual != NULL){
            printf ("id=%d prioridade=%d\n", atual->id, atual->prioridade);
            atual = atual->nextpointer;
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
    return 0;
}