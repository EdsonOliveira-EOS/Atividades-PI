#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char species[50];
} Iris;

void calcular_medias(Iris *dados, int n,
                     float *m_sl, float *m_sw,
                     float *m_pl, float *m_pw) {
    *m_sl = *m_sw = *m_pl = *m_pw = 0;
    for (int i = 0; i < n; i++) {
        *m_sl += dados[i].sepal_length;
        *m_sw += dados[i].sepal_width;
        *m_pl += dados[i].petal_length;
        *m_pw += dados[i].petal_width;
    }
    *m_sl /= n;
    *m_sw /= n;
    *m_pl /= n;
    *m_pw /= n;
}

void calcular_moda(Iris *dados, int n, char *moda) {
    char especies[20][50];
    int contagens[20] = {0};
    int n_especies = 0;

    for (int i = 0; i < n; i++) {
        int encontrado = 0;
        for (int j = 0; j < n_especies; j++) {
            if (strcmp(dados[i].species, especies[j]) == 0) {
                contagens[j]++;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(especies[n_especies], dados[i].species);
            contagens[n_especies] = 1;
            n_especies++;
        }
    }

    int idx_moda = 0;
    for (int j = 1; j < n_especies; j++) {
        if (contagens[j] > contagens[idx_moda] ||
           (contagens[j] == contagens[idx_moda] &&
            strcmp(especies[j], especies[idx_moda]) < 0)) {
            idx_moda = j;
        }
    }
    strcpy(moda, especies[idx_moda]);
}

void processar_arquivo(int num) {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "iris%d.txt", num);

    FILE *f = fopen(nome_arquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s.\n", nome_arquivo);
        return;
    }

    char cabecalho[200];
    fgets(cabecalho, sizeof(cabecalho), f);

    Iris *dados = NULL;
    int n = 0;

    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        if (strncmp(linha, "media", 5) == 0 ||
            strncmp(linha, "moda", 4) == 0) continue;

        Iris temp;
        if (sscanf(linha, "%f,%f,%f,%f,%49[^\n]",
                   &temp.sepal_length, &temp.sepal_width,
                   &temp.petal_length, &temp.petal_width,
                   temp.species) == 5) {

            Iris *novo = realloc(dados, (n + 1) * sizeof(Iris));
            if (novo == NULL) {
                printf("Erro de alocacao de memoria.\n");
                free(dados);
                fclose(f);
                return;
            }
            dados = novo;
            dados[n] = temp;
            n++;
        }
    }
    fclose(f);

    if (n == 0) {
        printf("Nenhum dado encontrado em %s.\n", nome_arquivo);
        free(dados);
        return;
    }

    float m_sl, m_sw, m_pl, m_pw;
    calcular_medias(dados, n, &m_sl, &m_sw, &m_pl, &m_pw);

    char moda[50];
    calcular_moda(dados, n, moda);

    printf("\n=== %s ===\n", nome_arquivo);
    printf("%s", cabecalho);
    for (int i = 0; i < n; i++) {
        printf("%.1f,%.1f,%.1f,%.1f,%s\n",
               dados[i].sepal_length, dados[i].sepal_width,
               dados[i].petal_length, dados[i].petal_width,
               dados[i].species);
    }
    printf("media = %.2f, %.2f, %.2f, %.2f\n", m_sl, m_sw, m_pl, m_pw);
    printf("moda = %s\n", moda);

    f = fopen(nome_arquivo, "a");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        free(dados);
        return;
    }
    fprintf(f, "media = %.2f, %.2f, %.2f, %.2f\n", m_sl, m_sw, m_pl, m_pw);
    fprintf(f, "moda = %s\n", moda);
    fclose(f);

    free(dados);
}

int main() {
    int n_arquivos;
    scanf("%d", &n_arquivos);

    for (int i = 1; i <= n_arquivos; i++) {
        processar_arquivo(i);
    }

    return 0;
}