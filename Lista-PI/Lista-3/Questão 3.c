#include <stdio.h>
#include <string.h>
#define isLetter(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))

int main(void){

    char stringarray[101];
    char lower[101];

    fgets(stringarray, sizeof(stringarray), stdin);

    for (int i = 0; stringarray[i] != '\0'; i++){
        if (stringarray[i] == '\n'){
            stringarray[i] = '\0';
            break;
        }
    }

    for (int i = 0; stringarray[i] != '\0'; i++){
        if (stringarray[i] >= 'A' && stringarray[i] <= 'Z')
            lower[i] = stringarray[i] + 32;
        else
            lower[i] = stringarray[i];
    }
    lower[strlen(stringarray)] = '\0';

    int inWord = 0;
    int WordsAmount = 0;
    int start[50];
    int size[50];

    for (int i = 0; lower[i] != '\0'; i++){
        if (isLetter(lower[i])){
            if (inWord == 0){
                start[WordsAmount] = i;
                inWord = 1;
            }
        } else {
            if (inWord == 1){
                size[WordsAmount] = i - start[WordsAmount];
                WordsAmount++;
                inWord = 0;
            }
        }
    }
    if (inWord == 1){
        size[WordsAmount] = strlen(lower) - start[WordsAmount];
        WordsAmount++;
    }

    int anagrams = 0;
    int wordprint = 0;

    for (int i = 0; i < WordsAmount; i++){
        for (int j = i + 1; j < WordsAmount; j++){

            int counting1[26] = {0};
            for (int k = start[i]; k < start[i] + size[i]; k++)
                counting1[lower[k] - 'a']++;

            int counting2[26] = {0};
            for (int k = start[j]; k < start[j] + size[j]; k++)
                counting2[lower[k] - 'a']++;

            int anagram = 1;
            for (int k = 0; k < 26; k++){
                if (counting1[k] != counting2[k]){
                    anagram = 0;
                    break;
                }
            }

            if (anagram == 1){
                if (wordprint == 0){
                    printf("Pares de anagramas encontrados:\n");
                    wordprint = 1;
                }
                for (int k = start[i]; k < start[i] + size[i]; k++)
                    printf("%c", stringarray[k]);
                printf(" e ");
                for (int k = start[j]; k < start[j] + size[j]; k++)
                    printf("%c", stringarray[k]);
                printf("\n");
                anagrams++;
            }
        }
    }

    if (anagrams == 0)
        printf("Nao existem anagramas na frase.\n");
    else {
        printf("\n");
        printf("Total de pares: %d\n", anagrams);
    }

    return 0;
}