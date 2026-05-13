#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void formatarNome(char *str){
    if (str[0] != '\0'){
        str[0] = toupper(str[0]);
        for (int i = 1; str[i] != '\0'; i++){
            str[i] = tolower(str[i]);
        }
    }
}

typedef struct{
    char cidadela[50];
    int habitantes;
    char periculosidade[50];
    char funcaopais[50];
} cidadelas;

int main (void){

    cidadelas informacoes[100];

    char frase[200];
    int mensagens = 0;
    int chave = -1;
    
    while (scanf(" %[^\n]", frase) != EOF){

        // Cidadela
        int j = 0;
        for (int i = 0; frase[i] != '\0'; i++){
            if (frase[i] >= 'A' && frase[i] <= 'Z'){
                informacoes[mensagens].cidadela[j] = frase[i];
                j++;
            }
        }
        informacoes[mensagens].cidadela[j] = '\0';

        // Habitantes
        int k = 0;
        char stringnumero[50];
        int especial = 0;
        for (int i = 0; frase[i] != '\0'; i++){
            if (frase[i] >= '0' && frase[i] <= '9'){
                stringnumero[k] = frase[i];
                k++;
            }
            if (frase[i] == '!'){especial = 1;}
        }
        stringnumero[k] = '\0';
        if (especial){chave = atoi(stringnumero); chave -= 1;} 
        else{informacoes[mensagens].habitantes = atoi(stringnumero);}

        // periculosidade
        int l = 0;
        for (int i = 0; frase[i] != '\0'; i++){
            if (frase[i] == '*'){
                informacoes[mensagens].periculosidade[l] = frase[i];
                l++;
            }
        }
        informacoes[mensagens].periculosidade[l] = '\0';

        // Funcao
        int m = 0;
        for (int i = 0; frase[i] != '\0'; i++){
            if (frase[i] == ' ' && frase[i+1] == ' '){
                informacoes[mensagens].funcaopais[m] = frase[i+2];
                i++;
                m++;
            }
        }
        informacoes[mensagens].funcaopais[m] = '\0';

        mensagens++;
    }

    if (chave < 0){printf ("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");} 
    else {
        // Ordenação
        for (int i = 0; i < mensagens - 1; i++){
            for (int j = 0; j < mensagens - i - 1; j++){
                int trocar = 0;

                if (informacoes[j].habitantes < informacoes[j+1].habitantes){
                    trocar = 1;
                } else if (informacoes[j].habitantes == informacoes[j+1].habitantes){
                    if (strlen(informacoes[j].periculosidade) < strlen(informacoes[j+1].periculosidade)){
                        trocar = 1;
                    } else if (strlen(informacoes[j].periculosidade) == strlen(informacoes[j+1].periculosidade)){
                        if (strcmp(informacoes[j].cidadela, informacoes[j+1].cidadela) > 0){
                            trocar = 1;
                        }
                    }
                }
                if (trocar){
                cidadelas temp = informacoes[j];
                informacoes[j] = informacoes[j+1];
                informacoes[j+1] = temp;
                }
            }
        }

        formatarNome(informacoes[chave].cidadela);
        formatarNome(informacoes[chave].funcaopais);

        printf ("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade %s. ", informacoes[chave].cidadela, informacoes[chave].habitantes, informacoes[chave].funcaopais, informacoes[chave].periculosidade);

        if (informacoes[chave].habitantes > 1000 && strlen(informacoes[chave].periculosidade) > 3){
            printf ("Talvez seja melhor desistir...\n");
        }
        else {
            if (informacoes[chave].habitantes > 1000){
                printf ("Um lugar denso, vai ser difícil achar ela. ");
            }
            if (strlen(informacoes[chave].periculosidade) > 3){
                printf ("Vai ser complicado entrar lá.\n");
            }
        }
    }
}