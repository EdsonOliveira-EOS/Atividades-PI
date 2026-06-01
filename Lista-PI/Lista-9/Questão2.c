#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char matricula[12];
    int prioridade;
    float cr;
    int chegada;
    int timeout;
    int score;
} Aluno;

typedef struct node {
    Aluno info;
    struct node *nextpointer;
} Node;

void checknull(void *pointer) {
    if (pointer == NULL) {
        printf("Não alocado.\n");
        exit(1);
    }
}

void enqueue(Node **inicio, Node **fim, Aluno novo_aluno) {
    Node *novo = (Node *) malloc(sizeof(Node));
    checknull(novo);
    
    novo->info = novo_aluno;
    novo->nextpointer = NULL;
    if (*inicio == NULL) {
        *inicio = novo;
        *fim = novo;
    } else {
        (*fim)->nextpointer = novo;
        *fim = novo;
    }
}

Aluno dequeue(Node **inicio, Node **fim) {
    if (*inicio == NULL) {
        Aluno vazio = {0};
        return vazio;
    }
    Node *new = *inicio;
    Aluno aluno_retorno = new->info;
    *inicio = (*inicio)->nextpointer;
    
    if (*inicio == NULL) {
        *fim = NULL;
    }
    free(new);
    return aluno_retorno;
}

void processar_alunos(Node **req_inicio, Node **req_fim, Node **conf_inicio, Node **conf_fim, int qtd, int *relogio, int *vagas) {
    int processados = 0;

    while (processados < qtd && *req_inicio != NULL) {
        Aluno atual = (*req_inicio)->info;

        if (*relogio < atual.chegada) {
            *relogio = atual.chegada;
        }

        if (*relogio > atual.timeout) {
            dequeue(req_inicio, req_fim);
            printf("[TIMEOUT] mat=%s | Desconectado da fila.\n", atual.matricula);
        } 
        else {
            dequeue(req_inicio, req_fim);

            if (*vagas > 0) {
                printf("[ALOCADO] mat=%s | score=%d | Processado no seg: %d\n", atual.matricula, atual.score, *relogio);
                enqueue(conf_inicio, conf_fim, atual);
                (*vagas)--;
            } else {
                printf("[LOTADO] mat=%s | score=%d | Processado no seg: %d\n", atual.matricula, atual.score, *relogio);
            }

            (*relogio)++;
            processados++;
        }
    }
}

int main() {
    Node *fila_requisicoes_inicio = NULL;
    Node *fila_requisicoes_fim = NULL;
    
    Node *fila_confirmados_inicio = NULL;
    Node *fila_confirmados_fim = NULL;

    char comando[10];
    char nome_disciplina[55];
    int vagas = 0;
    int relogio_servidor = 1;
    while (scanf("%s", comando) != EOF) {
        
        if (strcmp(comando, "START") == 0) {
            scanf("%s %d", nome_disciplina, &vagas);
        } 
        
        else if (strcmp(comando, "ADD") == 0) {
            Aluno novo;
            scanf("%s %d %f %d %d", novo.matricula, &novo.prioridade, &novo.cr, &novo.chegada, &novo.timeout);
            
            novo.score = (int)round(novo.cr * 100.0) / novo.prioridade;
            
            enqueue(&fila_requisicoes_inicio, &fila_requisicoes_fim, novo);
        } 
        
        else if (strcmp(comando, "PROC") == 0) {
            int qtd;
            scanf("%d", &qtd);
            processar_alunos(&fila_requisicoes_inicio, &fila_requisicoes_fim, &fila_confirmados_inicio, &fila_confirmados_fim, qtd, &relogio_servidor, &vagas);
        } 
        
        else if (strcmp(comando, "FIM") == 0) {
            break;
        }
    }

    printf("--- LISTA OFICIAL: %s ---\n", nome_disciplina);
    int posicao = 1;
    
    while (fila_confirmados_inicio != NULL) {
        Aluno aprovado = dequeue(&fila_confirmados_inicio, &fila_confirmados_fim);
        printf("%d. Matricula: %s\n", posicao, aprovado.matricula);
        posicao++;
    }

    while (fila_requisicoes_inicio != NULL) {
        dequeue(&fila_requisicoes_inicio, &fila_requisicoes_fim);
    }

    return 0;
}