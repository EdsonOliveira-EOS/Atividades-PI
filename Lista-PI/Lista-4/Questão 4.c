#include <stdio.h>

int maze(int lines, int columns, int xrebeka, int yrebeka, int amountofmeters, char matriz[lines][columns]){

    if (xrebeka >= columns || xrebeka < 0 || yrebeka >= lines || yrebeka < 0) return 999999;
    if (matriz[yrebeka][xrebeka] == '#' || matriz[yrebeka][xrebeka] == 'X') return 999999;
    if (matriz[yrebeka][xrebeka] == 'd') return amountofmeters;

    matriz[yrebeka][xrebeka] = 'X'; // para ela não ficar voltando imediatamente pelo lugar que veio e ficar dando loop

    int a = maze(lines, columns, xrebeka - 1, yrebeka, amountofmeters + 1, matriz);
    int b = maze(lines, columns, xrebeka + 1, yrebeka, amountofmeters + 1, matriz);
    int c = maze(lines, columns, xrebeka, yrebeka - 1, amountofmeters + 1, matriz);
    int d = maze(lines, columns, xrebeka, yrebeka + 1, amountofmeters + 1, matriz);

    int min;
    if (a < b){min = a;} 
    else {min = b;}
    if (c < min){min = c;}
    if (d < min){min = d;}
    return min;
}

int main(void){

    int lines, columns;
    scanf("%dx%d\n", &lines, &columns);
    char matriz[lines][columns];

    int xrebeka = 0, yrebeka = 0;
    for (int i = 0; i < lines; i++){
        for (int j = 0; j < columns; j++){
            char temp;
            scanf("%c", &temp);
            matriz[i][j] = temp;

            if (temp == 'o'){
                xrebeka = j;
                yrebeka = i;
            }
        }
        char temp2; scanf("%c", &temp2);
    }
    int meters = maze(lines, columns, xrebeka, yrebeka, 0, matriz);
    if (meters < 999999){
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", meters);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }
}
