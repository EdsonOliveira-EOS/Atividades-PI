#include <stdio.h>

// Recurs�ozinha que eu preferi fazer para essa quest�o para ficar simples
void water(int i, int j, int m, int n, char matriz[m][n]){
    if (i >= m || i < 0 || j >= n || j < 0) return;
    if (matriz[i][j] == '#') return;
    if (matriz[i][j] == 'o') return;

    matriz[i][j] = 'o';
    if (i + 1 < m && matriz[i+1][j] == '#'){
        water(i, j-1, m, n, matriz);
        water(i, j+1, m, n, matriz);
    }
    else {
        water(i+1, j, m, n, matriz);
    }
}

// Fun��o de printar matriz s� para encher o papo n�
void printmatriz (int m, int n, char matrix[m][n]){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf ("%c", matrix[i][j]);
        }
        printf ("\n");
    }
}

int main(void){
    int m, n;
    scanf ("%d %d\n", &m, &n);
    char matriz[m][n];

    int xcoordinatewater = 0;
    int ycoordinatewater = 0;

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            char temp;
            scanf("%c", &temp);
            matriz[i][j] = temp;

            if (temp == 'o'){
                xcoordinatewater = j;
                ycoordinatewater = i;
            }
        }
        char temp2; scanf("%c", &temp2);
    }

    matriz[ycoordinatewater][xcoordinatewater] = '.'; // Isso daqui foi um comodismo porque eu tinha que fazer a recurs�o acabar quando a matriz em ij desse o para evitar dar problema, kk
    water(ycoordinatewater, xcoordinatewater, m, n, matriz);
    printmatriz(m, n, matriz);
}
