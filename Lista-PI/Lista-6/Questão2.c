#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INBOUNDS(x, y, L, C) ((x) >= 0 && (x) < (L) && (y) >= 0 && (y) < (C))
#define max(a, b) ((a) > (b) ? (a) : (b))
// ------------------------------------------------------------------------
void checknull (void* pointer){
    if (pointer == NULL){
        printf ("Memoria não alocada\n");
        exit(1);
    }
}
// ------------------------------------------------------------------------
void alocarmatriz (int **matriz, int L, int C){
    for (int i = 0; i < L; i++){
        matriz[i] = (int*) malloc(C * sizeof(int));
        if (matriz[i] == NULL){
            printf ("Falha na alocação da coluna [%d]\n", i);
            for (int j = 0; j < i; j++){
                free(matriz[j]);
            }
            free(matriz);
            exit(1);
        }
    }
}
// ------------------------------------------------------------------------
void lerelementos(int **matriz, int L, int C){
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            scanf ("%d", &matriz[i][j]);
        }
    }
}
// ------------------------------------------------------------------------
void printmatriz (int **matriz, int L, int C){
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            printf ("%d ", matriz[i][j]);
        }
        printf ("\n");
    }
}
// ------------------------------------------------------------------------
void freematriz (int **matriz, int L, int C){
    for (int i = 0; i < L; i++){
        free(matriz[i]);
    }
    free(matriz);
}
// ------------------------------------------------------------------------
void explosaoarcana (int **newmatriz, int L, int C, int coordx, int coordy, int turnos){
    printf ("Estado do mapa após usar a Explosão Arcana:\n");

    for (int i = -2; i <= 2; i++){
        for (int j = -2; j <= 2; j++){
            if (abs(i) == 2 && abs(j) == 2) {continue;}
            int nx = coordx + i;
            int ny = coordy + j;
            if (INBOUNDS(nx, ny, L, C)){
                int dano = 0;
                if (abs(i) + abs(j) <= 1) {dano = 50;}
                else {dano = 25;}
                if (newmatriz[nx][ny] - dano < 0) {newmatriz[nx][ny] = 0;}
                else {newmatriz[nx][ny] -= dano;}
            }
        }
    }
    printmatriz(newmatriz, L, C);
    printf ("\n");
}
// ------------------------------------------------------------------------
void nuvemvenenosa (int **newmatriz, int L, int C, int coordx, int coordy, int turnos){
    printf ("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");

    for (int t = 0; t < turnos; t++){
        int *vizinhos = malloc(21 * sizeof(int));
        checknull(vizinhos);

        int idx = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <= 2; j++){
                if (abs(i) == 2 && abs(j) == 2) {continue;}
                int nx = coordx + i;
                int ny = coordy + j;
                vizinhos[idx] = 0;
                if (INBOUNDS(nx, ny, L, C)){
                    for (int di = -1; di <= 1; di++){
                        for (int dj = -1; dj <= 1; dj++){
                            if (abs(di) + abs(dj) != 0){
                                int vx = nx + di;
                                int vy = ny + dj;
                                if (INBOUNDS(vx, vy, L, C) && newmatriz[vx][vy] > 0) {vizinhos[idx]++;}
                            }
                        }
                    }
                }
                idx++;
            }
        }
        idx = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <= 2; j++){
                if (abs(i) == 2 && abs(j) == 2) {continue;}
                int nx = coordx + i;
                int ny = coordy + j;
                if (INBOUNDS(nx, ny, L, C)){
                    int dano = 5 + (8 * vizinhos[idx]);
                    if (newmatriz[nx][ny] - dano < 0) {newmatriz[nx][ny] = 0;}
                    else {newmatriz[nx][ny] -= dano;}
                }
                idx++;
            }
        }
        free(vizinhos);
        printmatriz(newmatriz, L, C);
        printf("\n");

        int aindavivos = 0;
        for (int i = -2; i <= 2; i++){
            for (int j = -2; j <= 2; j++){
                if (abs(i) == 2 && abs(j) == 2) {continue;}
                int nx = coordx + i;
                int ny = coordy + j;
                if (INBOUNDS(nx, ny, L, C) && newmatriz[nx][ny] > 0) {aindavivos++;}
            }
        }
        if (aindavivos == 0) {break;}
    }
}
// ------------------------------------------------------------------------
void grid (int **matriz, int L, int C, int coordx, int coordy, int turnos, void (*ataque)(int**, int, int, int, int, int)){
    int **newmatriz = malloc (L * sizeof(int*));
    checknull (newmatriz);
    alocarmatriz(newmatriz, L, C);
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            newmatriz[i][j] = matriz[i][j];
        }
    }
    ataque(newmatriz, L, C, coordx, coordy, turnos);
    freematriz(newmatriz, L, C);
}
// ------------------------------------------------------------------------
int main (void){
    int L, C;
    scanf ("%d %d", &L, &C);

    int** matriz;
    matriz = (int**) malloc(L * sizeof(int*));
    checknull (matriz);
    alocarmatriz(matriz, L, C);
    lerelementos(matriz, L, C);

    printf ("Estado inicial do mapa:\n");
    printmatriz(matriz, L, C);
    printf ("\n");

    int coordx, coordy;
    scanf ("%d %d", &coordx, &coordy);

    char str[50];
    scanf("%49s", str);

    if (strncmp(str, "EXPLOSAO_ARCANA", strlen("EXPLOSAO_ARCANA")) == 0) {grid(matriz, L, C, coordx, coordy, 1, explosaoarcana);}
    else if (strncmp(str, "NUVEM_VENENOSA", strlen("NUVEM_VENENOSA")) == 0) {grid(matriz, L, C, coordx, coordy, 3, nuvemvenenosa);}

    freematriz(matriz, L, C);
}