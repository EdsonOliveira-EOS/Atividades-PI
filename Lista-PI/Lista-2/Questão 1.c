#include <stdio.h>
#include <stdlib.h>

int main() {
    char entrada;
    scanf("%c", &entrada);

    int linhas = entrada - 'A' + 1; // colocar algo menos 'A' + 1 ''revela'' a letra usada, e nesse caso, as linhas v�o indo at� chegar na entrada
    int colunas = 2 * linhas - 1; // Observando o padr�o da nossa matriz, a coluna sempre seria o dobro - 1
    int centro = linhas - 1; // E por ser uma matriz impar, � linhas - 1

    for (int i = 1; i <= linhas; i++){
        for (int j = 0; j < colunas; j++){
            int distancia = abs(j - centro);

            if (distancia <= i - 1){
                printf ("%c", 'A' + (i-1) - distancia);
            }
            else {
                printf(".");
            }
            
        }
        printf ("\n");
    }

    return 0;
}