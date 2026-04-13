#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checknull(void* pointer);
// --------------------------------------------------
int main(void){
    int n;
    scanf("%d", &n);

    char* strings[n];
    char temp[256];

    for (int i = 0; i < n; i++){
        scanf("%255s", temp);
        strings[i] = malloc((strlen(temp) + 1) * sizeof(char));
        checknull(strings[i]);
        strcpy(strings[i], temp);
    }

    int total = 0;
    for (int i = 0; i < n; i++){
        total += strlen(strings[i]);
    }

    char* MERGED_STRING = malloc((total + 1) * sizeof(char));
    checknull(MERGED_STRING);

    int amountofcharacters = 0;
    int maxlen = 0;
    for (int i = 0; i < n; i++){
        if (strlen(strings[i]) > maxlen){
            maxlen = strlen(strings[i]);
        }
    }

    for (int j = 0; j < maxlen; j++){
        for (int i = 0; i < n; i++){
            if (j < strlen(strings[i])){
                MERGED_STRING[amountofcharacters] = strings[i][j];
                amountofcharacters++;
            }
        }
    }
    MERGED_STRING[amountofcharacters] = '\0';
    printf("%s\n", MERGED_STRING);

    char* MERGED_STRING_AFTER_FUSION = malloc((total + 1) * sizeof(char));
    checknull(MERGED_STRING_AFTER_FUSION);
    strcpy(MERGED_STRING_AFTER_FUSION, MERGED_STRING);

    int idx = 0;
    int k;
    int merged = 1;
    while (merged){
        merged = 0;
        idx = 0;
        while (MERGED_STRING_AFTER_FUSION[idx] != '\0'){
            if (MERGED_STRING_AFTER_FUSION[idx] == MERGED_STRING_AFTER_FUSION[idx+1]){
                char c = MERGED_STRING_AFTER_FUSION[idx];
                if (c != 'z'){MERGED_STRING_AFTER_FUSION[idx] = c + 1;} 
                else {MERGED_STRING_AFTER_FUSION[idx] = 'a';}

                k = idx + 1;
                while (MERGED_STRING_AFTER_FUSION[k] != '\0'){
                    MERGED_STRING_AFTER_FUSION[k] = MERGED_STRING_AFTER_FUSION[k+1];
                    k++;
                }

                merged = 1;
                idx++;
            } else {
                idx++;
            }
        }
    }
    printf("%s\n", MERGED_STRING_AFTER_FUSION);

    for (int i = 0; i < n; i++){
        free(strings[i]);
    }
    free(MERGED_STRING);
    free(MERGED_STRING_AFTER_FUSION);

    return 0;
}
// --------------------------------------------------
void checknull(void* pointer){
    if (pointer == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
}
