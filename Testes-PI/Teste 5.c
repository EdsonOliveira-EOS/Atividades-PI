#include <stdio.h>
#include <stdlib.h>

void checknull(void* pointer);

int main(void){

    int* listnumbers = NULL;
    int size = 0;
    int n;

    while (scanf("%d", &n) != EOF){
        size++;
        int* temp = realloc(listnumbers, size * sizeof(int));
        checknull(temp);
        listnumbers = temp;
        listnumbers[size - 1] = n;
    }

    printf ("Sequencia original: ");
    for (int i = 0; i < size; i++){
        printf ("%d ", listnumbers[i]);
    }
    printf ("\n");
    printf ("Comprimento original: %d\n", size);

    // Fazer a soma harmonizada
    int* harmonized = malloc (size * sizeof(int));
    checknull(harmonized);
    int harmonizedsize = size;
    int i = 0;
    int idx = 1;

    while (i < harmonizedsize){
        int x = listnumbers[i];
        harmonized[i] = x;

        if (harmonized[i] == listnumbers[idx]){
            int merged = 1;
            while (merged){
                if (harmonized[i] == listnumbers[idx]){
                    x = listnumbers[idx];
                    if (x != 7){
                        x = listnumbers[idx] + 1;
                    } else {
                        x = 1;
                    }
                    harmonized[i] = x;
                    harmonizedsize--;
                    idx++;
                    } else {
                        merged = 0;
                        i += 2;
                        idx = i + 1;
                }
            }
            if (i != 1){
                i--;
            }
        } else {
            i++;
            idx++;
        }

    }
    int* harmonized2 = malloc (harmonizedsize * sizeof(int));
    checknull(harmonized);
    int harmonizedcount = 0;

    for (int i = 0; i < harmonizedsize; i++){
        if (harmonized[i] == harmonized[i+1]){
            harmonized2[harmonizedcount] = harmonized[i] + 1;
            i++;
            harmonizedcount++;
        } else {
            harmonized2[harmonizedcount] = harmonized[i];
            harmonizedcount++;
        }
    }

    int harmonizedsum = 0;

    printf ("Sequencia harmonizada: ");
    for (int i = 0; i < harmonizedcount; i++){
        printf ("%d ", harmonized2[i]);
        harmonizedsum += harmonized2[i];
    }
    printf ("\n");
    printf ("Comprimento final: %d\n", harmonizedcount);
    printf ("Soma harmonizada: %d\n", harmonizedsum);

    free(listnumbers);
    free(harmonized);

}

void checknull(void* pointer){
    if (pointer == NULL){
        printf ("Erro ao alocar memoria");
        exit(1);
    }
}