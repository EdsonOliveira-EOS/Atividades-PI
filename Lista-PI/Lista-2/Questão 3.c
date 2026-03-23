#include <stdio.h>

int main() {
    long long X, N;
    scanf("%lld", &X);
    scanf("%lld", &N);

    int best_canal = -1;
    int best_minuto = -1;
    long long best_term = -1;
    long long best_dist = -1;

    for (int canal = 1; canal <= N; canal++) {
        long long a, b;
        scanf("%lld %lld", &a, &b);

        long long canal_best_term = -1;
        int canal_best_minuto = -1;
        long long canal_best_dist = -1;

        long long f_prev2 = a;
        long long f_prev1 = b;

        for (int i = 1; i <= 10000; i++) {
            long long term;
            if (i == 1)
                term = a;
            else if (i == 2)
                term = b;
            else {
                term = f_prev1 + f_prev2;
                f_prev2 = f_prev1;
                f_prev1 = term;
            }

            long long dist = term - X;
            if (dist < 0) dist = -dist;

            if (canal_best_dist == -1 || dist < canal_best_dist) {
                canal_best_dist = dist;
                canal_best_term = term;
                canal_best_minuto = i;
            }

            // Se o termo j� passou X e a dist�ncia est� aumentando, para
            if (term > X && dist > canal_best_dist)
                break;
        }

        // Compara com o melhor global
        if (best_dist == -1 || canal_best_dist < best_dist) {
            best_dist = canal_best_dist;
            best_canal = canal;
            best_minuto = canal_best_minuto;
            best_term = canal_best_term;
        } else if (canal_best_dist == best_dist) {
            // Mesma dist�ncia: pega canal de �ndice maior
            best_canal = canal;
            best_minuto = canal_best_minuto;
            best_term = canal_best_term;
        }
    }

    // Verifica VIP: soma dos algarismos do melhor termo
    int soma = 0;
    long long temp = best_term;
    while (temp > 0) {
        soma += temp % 10;
        temp /= 10;
    }

    if (soma > 10)
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", best_canal, best_minuto);
    else
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP n�o vai rolar :(\n", best_canal, best_minuto);

    return 0;
}