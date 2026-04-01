#include <stdio.h>

void printmatrix (int m, int n, char matrix[m][n]){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf ("%c", matrix[i][j]);
        }
        printf ("\n");
    }
}

int main(void){

    int m, n;
    scanf("%d %d\n", &m, &n);
    // m = linhas
    // n = colunas
    char matrix[m][n];

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            char temp;
            scanf("%c", &temp);
            matrix[i][j] = temp;
        }
    
        char temp2; scanf("%c", &temp2);
    }

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (matrix[i][j] == 'P') {
                if (i > 0 && (matrix[i-1][j] == '-' || matrix[i-1][j] == 'x')) {
                    matrix[i-1][j] = '+';
                }
                if (i < m-1 && (matrix[i+1][j] == '-' || matrix[i+1][j] == 'x')) {
                    matrix[i+1][j] = '+';
                }
                if (j > 0 && (matrix[i][j-1] == '-' || matrix[i][j-1] == 'x')) {
                    matrix[i][j-1] = '+';
                }
                if (j < n-1 && (matrix[i][j+1] == '-' || matrix[i][j+1] == 'x')) {
                    matrix[i][j+1] = '+';
                }

                if (i > 0 && j > 0 && (matrix[i-1][j-1] == '-' || matrix[i-1][j-1] == 'x')) {
                    matrix[i-1][j-1] = 'x';
                }
                if (i > 0 && j < n-1 && (matrix[i-1][j+1] == '-' || matrix[i-1][j+1] == 'x')) {
                    matrix[i-1][j+1] = 'x';
                }
                if (i < m-1 && j > 0 && (matrix[i+1][j-1] == '-' || matrix[i+1][j-1] == 'x')) {
                    matrix[i+1][j-1] = 'x';
                }
                if (i < m-1 && j < n-1 && (matrix[i+1][j+1] == '-' || matrix[i+1][j+1] == 'x')) {
                    matrix[i+1][j+1] = 'x';
                }
            }
        }        
    }
    printmatrix(m, n, matrix);
    return 0;
}
