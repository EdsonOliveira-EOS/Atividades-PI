#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define noslimites(x, y, M, N) ((x) >= 0 && (x) < (M) && (y) >= 0 && (y) < (N))
// Obrigado heitor por fazer um teste IGUALZINHO a sua questão, te amo!
// ########################################################################################################
void checknull(void *pointer){
    if (pointer == NULL){
        printf ("Memória não alocada\n");
        exit(1);
    }
}
// ########################################################################################################
void alocarmatriz(int **matriz, int M, int N){
    for (int i = 0; i < M; i++){
        matriz[i] = malloc(N * sizeof(int));
        if (matriz[i] == NULL){
            printf ("Memória não alocada\n");
            for (int j = 0; j < i; j++){
                free(matriz[j]);
            }
            free(matriz);
            exit(1);
        }
    }
}
// ########################################################################################################
void lerelementos(int **matriz, int M, int N){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}
// ########################################################################################################
void printmatriz (int **matriz, int M, int N){
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            printf ("%d ", matriz[i][j]);
        }
        printf ("\n");
    }
}
// ########################################################################################################
void freematriz (int **matriz, int M){
    for (int i = 0; i < M; i++){
        free(matriz[i]);
    }
    free(matriz);
}
// ########################################################################################################
void retardantequimico(int **novamatriz, int M, int N, int x, int y){

    printf ("Estado do mapa após usar o Retardante Químico:\n");
    for (int i = -2; i <= 2; i++){
        for (int j = -2; j <= 2; j++){
            if (abs(i) == 2 && abs(j) == 2){continue;}
            int ax = x + i;
            int ay = y + j;

            if (noslimites(ax, ay, M, N)){
                int reducao = 0;
                if (abs(i) + abs(j) <= 1){reducao = 50;}
                else {reducao = 25;}

                if (novamatriz[ax][ay] - reducao < 0){novamatriz[ax][ay] = 0;}
                else {novamatriz[ax][ay] -= reducao;}
            }
        }
    }
    printmatriz(novamatriz, M, N);
}
void chuvaartificial(int **novamatriz, int M, int N, int x, int y){

    printf ("Estado do mapa, por turno, após usar a Chuva Artificial:\n");
    // calcular vizinhos
    for (int i = 0; i < 3; i++){
        int vizinhos[21] = {0};
        int idx = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <=2; j++){
                if (abs(i) == 2 && abs(j) == 2){continue;}
                int ax = x + i;
                int ay = y + j;

                
                if (noslimites(ax, ay, M, N)){
                    for (int di = -1; di <= 1; di++){
                        for (int dj = -1; dj <= 1; dj++){
                            if (abs(di) == 0 && abs(dj) == 0){continue;}
                            int vx = ax + di;
                            int vy = ay + dj;
                            
                            if (noslimites(vx, vy, M, N)){
                                if (novamatriz[vx][vy] > 0){vizinhos[idx]++;} 
                            }
                            
                        }
                    }
                }
                idx++;
            }
        }
        int idx2 = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <=2; j++){
                if (abs(i) == 2 && abs(j) == 2){continue;}
                int ax = x + i;
                int ay = y + j;

                if (noslimites(ax, ay, M, N)){
                    int reducao = (3 + (6 * vizinhos[idx2]));

                    if (novamatriz[ax][ay] - reducao < 0){novamatriz[ax][ay] = 0;}
                    else {novamatriz[ax][ay] -= reducao;}
                }
                idx2++;
            }
        }

        printmatriz(novamatriz, M, N);
        printf("\n");

        int aindavivos = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <=2; j++){
                if (abs(i) == 2 && abs(j) == 2){continue;}
                int ax = x + i;
                int ay = y + j;

                if (noslimites(ax, ay, M, N)){
                    if (novamatriz[ax][ay] > 0){aindavivos++;}
                }
            }
        }
        if (aindavivos == 0){break;}
    }
}

void ataque (int **matriz, int M, int N, int x, int y, void (*habilidade)(int**, int, int, int, int)){

    int **novamatriz = malloc(M * sizeof(int*));
    checknull (novamatriz);
    alocarmatriz(novamatriz, M, N);

    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            novamatriz[i][j] = matriz[i][j];
        }
    }
    habilidade(novamatriz, M, N, x, y);
    freematriz(novamatriz, M);
}
// ########################################################################################################
int main(void){

    int M, N;
    scanf("%d %d", &M, &N);

    int **matriz = malloc(M * sizeof(int*));
    checknull(matriz);
    alocarmatriz(matriz, M, N);
    lerelementos (matriz, M, N);

    printf ("Estado inicial do mapa:\n");
    printmatriz (matriz, M, N);
    printf ("\n");

    int x, y;
    scanf("%d %d", &x, &y);

    char str[50];
    scanf("%49s", str);

    if (strncmp(str, "RETARDANTE_QUIMICO", strlen("RETARDANTE_QUIMICO")) == 0){ataque(matriz, M, N, x, y, retardantequimico);}
    else if (strncmp(str, "CHUVA_ARTIFICIAL", strlen("CHUVA_ARTIFICIAL")) == 0){ataque(matriz, M, N, x, y, chuvaartificial);}

    freematriz(matriz, M);
}