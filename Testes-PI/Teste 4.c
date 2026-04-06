// Infelizmente não terminei a tempo

#include <stdio.h>

int main(){

    int m;
    scanf ("%d\n", &m);
    // m = linhas, n = colunas

    int matriz[20][20];

    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            int temp;
            scanf("%d", &temp);
            matriz[i][j] = temp;
        }
        char temp2; scanf("%c", &temp2);
    }

    int contador = 0;
    int visitado[100] = {0};
    int amountofvisits = 0;

    // sequencia
    int sequenciax[100] = {0};
    int seqx = 0;
    int sequenciay[100] = {0};
    int seqy = 0;
    
    while (contador != m*m){
        for (int i = 0; i < m; i++){
            for (int j = 0; j < m; j++){

                if (((matriz[i][j] % 10) + (matriz[i][j] / 10)) == 10){
                    int temp = matriz[i][j];

                    sequenciax[seqx] = i;
                    seqx++;
                    sequenciay[seqy] = j;
                    seqy++;

                        // vetor
                    int dx[] = {0, 1};
                    // para a direita
                    while (dx[j+1] < m){
                        int newj = j + dx[j+1];

                        dx[j+1] += 1;
                        if (((matriz[i][newj] % 10) + (matriz[i][newj] / 10)) == 10){
                            if (matriz[i][newj] < temp){
                                visitado[amountofvisits] = i;
                                visitado[amountofvisits+1] = j;
                                amountofvisits += 2;

                                sequenciax[seqx] = i;
                                seqx++;
                                sequenciay[seqy] = newj;
                                seqy++;
                                temp = matriz[i][newj];
                            }
                        }
                    }

                    // para baixo
                    int dy[] = {1, 0};
                    while (dy[i] < m){
                        int newi = i + dy[i];

                        dy[i] += 1;
                        if (((matriz[newi][m-1] % 10) + (matriz[newi][m-1] / 10)) == 10){
                            if (matriz[newi][m-1] < temp){
                                visitado[amountofvisits] = m-1;
                                visitado[amountofvisits+1] = m-1;
                                amountofvisits += 2;

                                sequenciax[seqx] = newi;
                                seqx++;
                                sequenciay[seqy] = m-1;
                                seqy++;
                                temp = matriz[newi][m-1];
                            }
                        }
                    }

                    // para a esquerda
                    int dz[] = {0, -1};
                    while (dz[j-1] >= -m){
                        int newj = j + dz[j-1];
                        dz[j-1] -= 1;

                        int teste = matriz[i][newj];

                        if (((matriz[i][newj] % 10) + (matriz[i][newj] / 10)) == 10){
                            if (matriz[i][newj] < temp){
                                visitado[amountofvisits] = i;
                                visitado[amountofvisits+1] = newj;
                                amountofvisits += 2;

                                sequenciax[seqx] = i;
                                seqx++;
                                sequenciay[seqy] = newj;
                                seqy++;
                                temp = matriz[i][newj];
                            }
                        }
                    }

                    // Para cima
                    int dw[] = {-1, 0};
                    while (dw[i] >= -m){
                        int newi = i + dw[i];
                        dw[i] -= 1;

                        if (((matriz[newi][j] % 10) + (matriz[newi][j] / 10)) == 10){
                            if (matriz[newi][j] < temp){
                                visitado[amountofvisits] = newi;
                                visitado[amountofvisits+1] = j;
                                amountofvisits += 2;

                                sequenciax[seqx] = newi;
                                seqx++;
                                sequenciay[seqy] = j;
                                seqy++;
                                temp = matriz[newi][j];
                            }
                        }

                        
                    }
                    // Só para testar o código
                    i = 50;
                    j = 50;
                    contador = m*m;

                }
            }
        }

        // Só para testar o código
        contador = m*m;
    }

    printf ("%d\n", seqx);

    for (int i = 0; i < seqx; i++){
        printf ("(%d,%d)\n", sequenciax[i], sequenciay[i]);
    }

}
