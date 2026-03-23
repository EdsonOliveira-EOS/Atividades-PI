#include <stdio.h>
#include <stdlib.h>
int main(void){
    int q;
    int passosdireita = 0;
    scanf ("%d", &q);
    int veiodeb = 0;
    for (int i = 0; i < q; i++){
        int x;
        char c;
        scanf ("%d %c", &x, &c);
        if (c == 'D'){
            for (int espacos = 0; espacos < passosdireita; espacos++){
                printf (" ");
            }
            if (veiodeb == 1){
                printf(".");
                passosdireita += x;
            } else {
                passosdireita += x - 1;
            }
            for (int pontosD = 0; pontosD < x; pontosD++){
                printf (".");
            }
            printf ("\n");
            veiodeb = 0;
        }
        else if (c == 'E'){
            if (veiodeb == 1){
                if (passosdireita <= x){
                    printf ("Informacao invalida\n");
                    return 0;
                }
            } else {
                if (passosdireita < x){
                    printf ("Informacao invalida\n");
                    return 0;
                }
            }
            passosdireita -= x;
            for (int espacos = 0; espacos < passosdireita; espacos++){
                printf (" ");
            }
            if (veiodeb == 1){
                printf(".");
            }
            for (int pontosC = 0; pontosC < x; pontosC++){
                printf(".");
            }
            printf("\n");
            veiodeb = 0;
        }
        else if (c == 'B'){
            for (int pontosB = 0; pontosB < x; pontosB++){
                if (pontosB < x - 1){
                    for (int espacos = 0; espacos < passosdireita; espacos++){
                        printf (" ");
                    }
                    printf (".");
                    printf ("\n");
                }
            }
            veiodeb = 1;
        }
    }
    if (veiodeb == 1){
        for (int espacos = 0; espacos < passosdireita; espacos++){
            printf(" ");
        }
        printf(".\n");
    }
}