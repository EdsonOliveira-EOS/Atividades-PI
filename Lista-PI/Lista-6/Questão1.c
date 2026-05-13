#include <stdio.h>
#include <stdlib.h>

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
int dobrar (int x) {return x * 2;}
int quadrado (int x) {return x * x;}
int absoluto (int x) {return abs(x)}

void operacoes (int **matriz, int L, int C, int (*func)(int)){
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            matriz[i][j] = func(matriz[i][j]);
        }
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
int main (void){
    int L, C;
    scanf ("%d %d", &L, &C);

    int** matriz;
    matriz = (int**) malloc(L * sizeof(int*));
    checknull (matriz);

    alocarmatriz(matriz, L, C);
    lerelementos(matriz, L, C);

    int op;
    scanf ("%d", &op);

    if (op == 1) {operacoes(matriz, L, C, dobrar);}
    else if (op == 2) {operacoes(matriz, L, C, quadrado);}
    else {operacoes(matriz, L, C, absoluto);}

    printmatriz(matriz, L, C);
    freematriz(matriz, L, C);
}