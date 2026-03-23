#include <stdio.h>

int main(void){

    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);

    int primeiro = -1;
    int Q = 0;

    for (int i = N; i < K; i++){

        int numerosprimos = 0;
        int valido = 1;
        int num = i;

        // remove todos os fatores 2 sem invalidar
        while (num % 2 == 0) {
            num /= 2;
        }

        // testa apenas fatores �mpares
        for (int contaprimos = 3; contaprimos * contaprimos <= num && valido; contaprimos += 2){
            if (num % contaprimos == 0) {
                num /= contaprimos;
                if (num % contaprimos == 0) {
                    valido = 0;
                    break;
                } else {
                    numerosprimos++;
                }
            }
        }

        // se sobrou um fator �mpar maior que sqrt
        if (valido && num > 1) {
            numerosprimos++;
        }

        if (valido && numerosprimos == P) {
            if (primeiro == -1) {
                primeiro = i;
            } else {
                Q++;
            }
        }
    }

    if (primeiro == -1) {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    } else {
        printf("%d %d\n", primeiro, Q);
    }

    return 0;
}