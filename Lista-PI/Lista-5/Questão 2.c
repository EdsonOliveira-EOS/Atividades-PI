#include <stdio.h>
#include <stdlib.h>

void checknull(void* pointer){
    if (pointer == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
}

int main(void){

    int* lista = NULL;
    int n;
    int tamanho = 0;

    while (scanf("%d", &n) != EOF){
        tamanho++;
        int* temp = realloc (lista, tamanho * sizeof(int));
        checknull(temp);
        lista = temp;
        lista[tamanho - 1] = n;
    }
    printf ("Mais um bom dia de trabalho!\n");

    int* arrayodds = malloc (tamanho * sizeof(int));
    checknull(arrayodds);
    int sizeo = 0;
    
    int* arraypairs = malloc (tamanho * sizeof(int));
    checknull(arraypairs);
    int sizep = 0;

    for (int i = 0; i < tamanho; i++){
        if (lista[i] % 2 != 0){
            arrayodds[sizeo] = lista[i];
            sizeo++;
        } else {
            arraypairs[sizep] = lista[i];
            sizep++;
        }
    }

    // Printar os ímpares
    for (int i = 0; i < sizeo; i++){
        printf ("%d\n", arrayodds[i]);
    }
    // Printar os ímpares
    for (int i = 0; i < sizep; i++){
        printf ("%d\n", arraypairs[i]);
    }
    printf ("Vou visitar esses lugares de novo... algum dia.");

    free(lista);
}