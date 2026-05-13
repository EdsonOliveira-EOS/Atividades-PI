#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    char genero[50];
    char estudio[50];
    char console[50];
    int nota;
    int anolancamento;
} colecao;

int main (void){

    int n;
    scanf("%d", &n);

    colecao jogos[n];

    for (int i = 0; i < n; i++){
        scanf("%s %s %s %s %d %d", jogos[i].nome, jogos[i].genero, jogos[i].estudio, jogos[i].console, &jogos[i].nota, &jogos[i].anolancamento);

        if (jogos[i].nota > 7){printf ("AWESOME! Mais um GOTY pra minha coleção!\n");}
        else if (jogos[i].nota < 4){printf("Era melhor jogar mais um jogo de Mahjong.\n");}
    }

    char funcao[50];
    while (scanf("%s", funcao) != EOF){
        int contador = 0;
        // printano
        if (strncmp(funcao, "printAno", strlen("printAno")) == 0){
            int ano;
            scanf("%d", &ano);
            
            for (int i = 0; i < n; i++){
                if (jogos[i].anolancamento == ano){
                    printf ("%s\n", jogos[i].nome);
                    contador++;
                }
            }

            if (contador > 0){printf ("Tenho %d jogos || %d.\n", contador, ano);}
            else {printf ("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");}

        }
        // printletra
        if (strncmp(funcao, "printLetra", strlen("printLetra")) == 0){
            char letra;
            scanf(" %c", &letra);

            for (int i = 0; i < n; i++){
                if (jogos[i].nome[0] == letra){
                    printf ("%s\n", jogos[i].nome);
                    contador++;
                }
            }
            if (contador > 0){printf ("Tenho %d jogos || %c.\n", contador, letra);}
            else {printf ("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");}
        }
        // PrintStudio
        if (strncmp(funcao, "printStudio", strlen("printStudio")) == 0){
            char studio[50];
            scanf("%s", studio);

            for (int i = 0; i < n; i++){
                if (strncmp(jogos[i].estudio, studio, strlen(studio)) == 0){
                    printf ("%s\n", jogos[i].nome);
                    contador++;
                }
            }
            if (contador > 0){printf ("Tenho %d jogos || %s.\n", contador, studio);}
            else {printf ("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");}
        }

        // PrintConsole
        if (strncmp(funcao, "printConsole", strlen("printConsole")) == 0){
            char consolep[50];
            scanf("%s", consolep);

            for (int i = 0; i < n; i++){
                if (strncmp(jogos[i].console, consolep, strlen(consolep)) == 0){
                    printf ("%s\n", jogos[i].nome);
                    contador++;
                }
            }

            if (contador > 0){printf ("Tenho %d jogos || %s.\n", contador, consolep);}
            else {printf ("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");}
        }
        // PrintColecao
        if (strncmp(funcao, "printColecao", strlen("printColecao")) == 0){
            for (int i = 0; i < n; i++){
                printf ("%s %d\n", jogos[i].nome, jogos[i].nota);
            }
        }
    }
    printf ("Enjoei de jogar, agora vou ver TV.\n");
}