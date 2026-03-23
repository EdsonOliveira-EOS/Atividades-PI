#include <stdio.h>
#include <string.h>
#define isLetter(x) ((x >= 'a' && x <= 'z'))
// Isso é para checar se é uma letra entre a e z pois no meu código eu desconsidero as maiúsculas no array de comparação.

int main(void){

    char stringarray[101];
    char lowerarray[101];
    fgets (stringarray, sizeof(stringarray), stdin);

    for (int i = 0; stringarray[i] != '\0'; i++){

        if (stringarray[i] >= 'A' && stringarray[i] <= 'Z'){
            lowerarray[i] = stringarray[i] + 32;
        } else {
            lowerarray[i] = stringarray[i];
        }
    }
    // Com isso eu tenho um array tudo em minúsculo para comparações.
    int inPhrase = 0;
    int WordsAmount = 0;
    int start[50];
    int sizearray[50];

    for (int i = 0; i < strlen(lowerarray); i++){
        if isLetter(lowerarray[i]){
            if (inPhrase == 0){
                start[WordsAmount] = i;
                inPhrase = 1;
             }
        } else {
            if (inPhrase == 1){
                sizearray[WordsAmount] = i - start[WordsAmount];
                WordsAmount++;
                inPhrase = 0;
            }
        }
    }
    if (inPhrase == 1){
        sizearray[WordsAmount] = strlen(lowerarray) - start[WordsAmount];
        WordsAmount++;
        inPhrase = 0;
    }
    // Graças a Deus eu aprendi esse formato da questão dos anagramas.

    int PhrasePrinted = 0;
    int Pairs = 0;
    for (int i = 0; i < WordsAmount; i++){
        for (int j = i + 1; j < WordsAmount; j++){

            // array da primeira palavra
            int z = 0;
            char firstword[50] = {0};
            for (int array1 = start[i]; array1 < start[i] + sizearray[i]; array1++){
                firstword[z] = lowerarray[array1];
                z++;
            }
            // array da segunda palavra
            int y = 0;
            char secondword[50] = {0};
            for (int array2 = start[j]; array2 < start[j] + sizearray[j]; array2++){
                secondword[y] = lowerarray[array2];
                y++;
            }

            // achar o tamanho
            int tamanho;
            if (strlen(firstword) > strlen(secondword)){
                tamanho = strlen(firstword);
            } else {
                tamanho = strlen(secondword);
            }

            // lógica da comparação letra-a-letra
            int differ = 0;
            int differplace = 0;
            int foundproblem = 0;
            int differ2 = 0;
            for (int z = 0; z < tamanho; z++){
                if (firstword[z] != secondword[z]){
                    if (foundproblem == 0){
                        differplace = z;
                        foundproblem = 1;
                    }
                    differ++;
                }
            }
            for (int b = differplace; b < tamanho; b++){
                if (firstword[b + 1] != secondword[b]){
                    differ2++;
                }
            } 

            if (differ == 1 || (differ2 == 0)){
                if (PhrasePrinted == 0){
                    printf ("Pares de palavras vizinhas encontrados:\n");
                    PhrasePrinted = 1;
                }

                for (int array1 = start[i]; array1 < start[i] + sizearray[i]; array1++){
                    printf ("%c", stringarray[array1]);
                }
                printf (" e ");
                for (int array2 = start[j]; array2 < start[j] + sizearray[j]; array2++){
                    printf ("%c", stringarray[array2]);
                }
                printf ("\n");
                Pairs++;
            }
        }
    }
    if (Pairs == 0){
        printf ("Nao existem palavras vizinhas na frase.");
    } else {
        printf ("\n");
        printf ("Total de pares: %d", Pairs);
    }
    return 0;
}