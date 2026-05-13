#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int calibrar(int x) {return x + 5;}
int saturar(int x) {if (x > 80){return 80;} else {return x;}}
int amplificador(int x) {return x * 2;}

void modificar (int **matriz, int L, int C, int n){
    int (*filtro)(int) = NULL;
    if (n == 1){filtro = calibrar;} 
    else if (n == 2){filtro = saturar;}
    else if (n == 3){filtro = amplificador;}
    
    if (filtro != NULL){
        for (int i = 0; i < L; i++){
            for (int j = 0; j < C; j++){
                matriz[i][j] = filtro(matriz[i][j]);
            }
        }
    }

    else if (n == 4){
        int k;
        scanf("%d", &k);
        int (*filtro[k])(int);
        for (int f = 0; f < k; f++){
            int id;
            scanf ("%d", &id);

            if (id == 1){filtro[f] = calibrar;} 
            else if (id == 2){filtro[f] = saturar;}
            else if (id == 3){filtro[f] = amplificador;}
        }

        for (int v = 0; v < k; v++){
            for (int p = 0; p < L; p++){
                for (int u = 0; u < C; u++){
                    matriz[p][u] = (filtro[v])(matriz[p][u]);
                }
            }
        }
    }
}

// ------------------------------------------------------------------------
int main(void){
    int L, C;
    scanf ("%d %d", &L, &C);

    int** matriz;
    matriz = (int**) malloc(L * sizeof(int*));
    checknull (matriz);

    alocarmatriz(matriz, L, C);
    lerelementos(matriz, L, C);

    int n;
    while (scanf("%d", &n) != 0){
        if (n == 0){break;}
        modificar(matriz, L, C, n);
    }

    printf ("Matriz processada:\n");
    printmatriz(matriz, L, C);

    int bestvalue = 0;
    int coordx, coordy;
    for (int i = 0; i < L; i++){
        for (int j = 0; i < C; i++){
            if (matriz[i][j] > bestvalue){
                bestvalue = matriz[i][j]
                coordx = i;
                coordy = j;
            }
        }
    }
    printf ("\n")
    printf ("Sensor critico: %d\n", bestvalue);
    printf ("Posicao: (%d,%d)\n", coordx, coordy);

    freematriz(matriz, L, C);
}