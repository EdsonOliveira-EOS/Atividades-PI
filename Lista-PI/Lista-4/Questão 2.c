#include <stdio.h>

void findmostvaluable(int matriz[4][4]){
    int maxTerm = -1; 
    int maxX = 0; 
    int maxY = 0;
    for (int l = 0; l < 4; l++){
        for (int c = 0; c < 4; c++){
            if (matriz[l][c] > maxTerm){
                maxTerm = matriz[l][c];
                maxX = c;
                maxY = l;
            }

        }
    }
    printf("Coordenada X:%d, Y:%d\n", maxX, maxY);
}

int main(void){
    int matriz[4][4] = {0};
    char movement;
    int x = 0;
    int y = 0;

    matriz[y][x]++;
    for (int i = 0; i < 20; i++){
        scanf(" %c", &movement);
        if (movement == 'c' && y > 0){y--; matriz[y][x]++;}
        else if (movement == 'b' && y < 3){y++; matriz[y][x]++;}
        else if (movement == 'e' && x > 0){x--; matriz[y][x]++;}
        else if (movement == 'd' && x < 3){x++; matriz[y][x]++;}
    }

    findmostvaluable(matriz);
}
