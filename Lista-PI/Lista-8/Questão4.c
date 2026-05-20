#include <stdio.h>
#include <string.h>

// ─── Structs ───────────────────────────────────────────────
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    int codigo;
    char tipo;
    int quantidade;
} Movimento;

// ─── Funções auxiliares ────────────────────────────────────

int buscar_produto(Produto *produtos, int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) return i;
    }
    return -1;
}

void processar_movimento(Movimento mov, Produto *produtos, int n,
                         int *aplicados, int *recusados,
                         int *sem_cadastro, char *inconsistencias) {
    int idx = buscar_produto(produtos, n, mov.codigo);

    if (idx == -1) {
        (*sem_cadastro)++;
        char linha[100];
        sprintf(linha, "%d %c %d PRODUTO_INEXISTENTE\n",
                mov.codigo, mov.tipo, mov.quantidade);
        strcat(inconsistencias, linha);
        return;
    }

    if (mov.tipo == 'E') {
        produtos[idx].quantidade += mov.quantidade;
        (*aplicados)++;
    } else if (mov.tipo == 'S') {
        if (produtos[idx].quantidade >= mov.quantidade) {
            produtos[idx].quantidade -= mov.quantidade;
            (*aplicados)++;
        } else {
            (*recusados)++;
            char linha[100];
            sprintf(linha, "%d %c %d ESTOQUE_INSUFICIENTE\n",
                    mov.codigo, mov.tipo, mov.quantidade);
            strcat(inconsistencias, linha);
        }
    }
}

void gerar_estoque(Produto *produtos, int n) {
    FILE *f = fopen("estoque_atualizado.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d %s %d %.2f\n",
                produtos[i].codigo, produtos[i].nome,
                produtos[i].quantidade, produtos[i].preco);
    }
    fclose(f);
}

void gerar_relatorio(Produto *produtos, int n,
                     int aplicados, int recusados,
                     int sem_cadastro, char *inconsistencias) {
    FILE *f = fopen("relatorio.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(f, "PRODUTOS PROCESSADOS: %d\n", n);
    fprintf(f, "MOVIMENTOS APLICADOS: %d\n", aplicados);
    fprintf(f, "SAIDAS RECUSADAS: %d\n", recusados);
    fprintf(f, "MOVIMENTOS SEM CADASTRO: %d\n", sem_cadastro);

    fprintf(f, "ESTOQUE BAIXO:\n");
    for (int i = 0; i < n; i++) {
        if (produtos[i].quantidade <= 5) {
            fprintf(f, "%d %s %d\n",
                    produtos[i].codigo, produtos[i].nome,
                    produtos[i].quantidade);
        }
    }

    fprintf(f, "INCONSISTENCIAS:\n");
    fprintf(f, "%s", inconsistencias);

    fclose(f);
}

// ─── Main ──────────────────────────────────────────────────

int main() {
    Produto produtos[100];
    int n_produtos = 0;

    int movimentos_aplicados = 0;
    int saidas_recusadas = 0;
    int sem_cadastro = 0;
    char inconsistencias[2000] = "";

    // Ler produtos.txt
    FILE *arq_prod = fopen("produtos.txt", "r");
    if (arq_prod == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    while (fscanf(arq_prod, "%d %s %d %f",
                  &produtos[n_produtos].codigo,
                  produtos[n_produtos].nome,
                  &produtos[n_produtos].quantidade,
                  &produtos[n_produtos].preco) == 4) {
        n_produtos++;
    }
    fclose(arq_prod);

    // Processar movimentos.txt
    FILE *arq_mov = fopen("movimentos.txt", "r");
    if (arq_mov == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }
    Movimento mov;
    while (fscanf(arq_mov, "%d %c %d",
                  &mov.codigo, &mov.tipo, &mov.quantidade) == 3) {
        processar_movimento(mov, produtos, n_produtos,
                            &movimentos_aplicados,
                            &saidas_recusadas,
                            &sem_cadastro,
                            inconsistencias);
    }
    fclose(arq_mov);

    // Gerar saídas
    gerar_estoque(produtos, n_produtos);
    gerar_relatorio(produtos, n_produtos, movimentos_aplicados,
                    saidas_recusadas, sem_cadastro, inconsistencias);

    return 0;
}