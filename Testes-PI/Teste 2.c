#include <stdio.h>

int main(void){

    int q;
    scanf ("%d", &q);

    // inicialização de variáveis para guardar informações
    int espaços = 0;
    int veiodeB = 0;
    int veiodeD = 0;
    int linha = 0;

    // pontinho inicial (fofinho)
    printf (".");

    for (int i = 0; i < q; i++){

        int X;
        char C;
        scanf ("%d %c", &X, &C);

        // primeiro, checar a posição direita
        if (C == 'D'){

            // Contagem das linhas (útil para ver o ''informação inválida'')
            linha += X;

            if (veiodeB == 0){
                for (int D = 0; D < espaços; D++){printf (" ");}
            } else {
                for (int D = 0; D < espaços; D++){printf (" ");}
                printf ("X");
            }
            for (int d = 0; d < X; d++){printf (".");}
            // contagem dos espaços
            espaços += X;
            // placeholders da posição anterior
            veiodeD = 1;
            veiodeB = 0;
        }

        // posição esquerda
        if (C == 'E'){

            espaços -= X;
            if (((espaços + linha) - X) < 0){
                printf ("Informacao invalida");
                return 0;
            }
            if (veiodeD == 0){
                for (int E = 0; E < espaços; E++){printf (" ");}

                for (int e = 0; e < X; e++){
                    printf (".");
                    if (veiodeB == 1){
                        if (e == (X - 1)){
                            printf ("X");
                        }
                    }
                }
            }
            // placeholders da posição anterior
            veiodeB = 0;
            veiodeD = 0;
        }
    
        // para baixo
        if (C == 'B'){

            printf ("\n");
            for (int b = 0; b < X; b++){
                for (int B = 0; B < espaços; B++){printf (" ");}
                printf (".\n");
            }
            if  (i == (q - 1)){
                for (int B = 0; B < espaços; B++){printf (" ");}
                printf (".");
            }
            // placeholders da posição anterior
            veiodeD = 0;
            veiodeB = 1;
        }
    }
}