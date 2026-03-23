#include <stdio.h>

int main(){
    long long N, A, B;
    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);

    // Soma de 1 ate N
    long long SomaTotal = N * (N + 1) / 2;

    // Soma dos multiplos de A ate N
    long long MA = N / A;
    long long SomaA = A * (MA * (MA + 1)) / 2;

    // Soma dos multiplos de B ate N
    long long MB = N / B;
    long long SomaB = B * (MB * (MB + 1)) / 2;

    // Soma dos multiplos de A*B ate N (A e B sao primos, entao MC = A*B)
    long long AB = A * B;
    long long MAB = N / AB;
    long long SomaAB = AB * (MAB * (MAB + 1)) / 2;

    // Inclusao-exclusao
    long long resultado = SomaTotal - SomaA - SomaB + SomaAB;

    printf("%lld\n", resultado);

    if (resultado % 2 == 0){printf("Lá ele!!!\n");}
    else{printf("Opa xupenio AULAS...\n");}

    return 0;
}
