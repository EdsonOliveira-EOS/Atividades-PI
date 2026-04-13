// Refazendo a questão para treino

#include <stdio.h>
#include <stdlib.h>

void checknull(void* pointer);

int main(void){

    int* list = NULL; // Sempre é bom começar um ponteiro com NULL e não com 0 caso não guardar nada
    int n;
    int size = 0;

    while (scanf("%d", &n) != EOF){
        size++;
        int* temp = realloc(list, size * sizeof(int));
        checknull(temp);
        list = temp;
        list[size - 1] = n;
    } // Com isso eu tenho a lista enorme com as entradas
    printf ("Mais um bom dia de trabalho!\n");

    int* oddnumbers = malloc(size * sizeof(int));
    int* evenNumbers = malloc(size * sizeof(int));
    checknull(oddnumbers);
    checknull(evenNumbers);
    int counto = 0, counte = 0;

    for (int i = 0; i < size; i++){
        if (list[i] % 2 != 0){
            oddnumbers[counto] = list[i];
            counto++;
        } else {
            evenNumbers[counte] = list[i];
            counte++;
        }
    }

    for (int i = 0; i < counto; i++){
        printf("%d\n", oddnumbers[i]);
    }
    for (int i = 0; i < counte; i++){
        printf ("%d\n", evenNumbers[i]);
    }
    printf ("Vou visitar esses lugares de novo... algum dia.");

    free(list);
    free(oddnumbers);
    free(evenNumbers);
}

void checknull(void* pointer){
    if (pointer == NULL){
        printf ("Memória não disponível\n");
        exit(1);
    }
}