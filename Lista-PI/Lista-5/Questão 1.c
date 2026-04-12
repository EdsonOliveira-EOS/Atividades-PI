#include <stdio.h>
#include <stdlib.h>

void checknull(void* pointer);
float* LerNotas(float* notas, int n);
float* PlaceNewNotes(float* notas, int n, int newsize);
float calcularMedia(float* notas, int n);
void calcularMaiorMenor(float* notas, int n);
void calcularAcimaDaMedia(float* notas, int n, float mid);
void calcularMediana(float* notas, int n);
void calcularModa(float* notas, int n);
void operations(float* notas, int n);
// --------------------------------------------------------------
int main(void){
    int n;
    scanf("%d", &n);

    float* notas = malloc(n * sizeof(float));
    checknull(notas);
    LerNotas(notas, n);

    printf("Relatorio inicial\n");
    operations(notas, n);

    int k;
    scanf("%d", &k);

    float* temp = realloc(notas, (n + k) * sizeof(float));
    checknull(temp);
    notas = temp;

    int newsize = n + k;
    PlaceNewNotes(notas, n, newsize);

    printf("Relatorio atualizado\n");
    operations(notas, newsize);

    free(notas);
    return 0;
}
// --------------------------------------------------------------
void checknull(void* pointer){
    if (pointer == NULL){
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
}
// --------------------------------------------------------------
float* LerNotas(float* notas, int n){
    for (int i = 0; i < n; i++){
        float temp;
        scanf("%f", &temp);
        notas[i] = temp;
    }
    return notas;
}
// --------------------------------------------------------------
float* PlaceNewNotes(float* notas, int n, int newsize){
    for (int i = n; i < newsize; i++){
        float temp;
        scanf ("%f", &temp);
        notas[i] = temp;
    }
    return notas;
}
// --------------------------------------------------------------
float calcularMedia(float* notas, int n){
    float mid = 0.00;
    for (int i = 0; i < n; i++){
        mid += notas[i];
    }
    mid /= n;
    return mid;
}
// --------------------------------------------------------------
void calcularMaiorMenor(float* notas, int n){
    int best = 0;
    float bestnote = notas[0];
    int worst = 0;
    float worstnote = notas[0];

    for (int i = 1; i < n; i++){
        if (notas[i] > bestnote){
            best = i;
            bestnote = notas[i];
        }
        if (notas[i] < worstnote){
            worst = i;
            worstnote = notas[i];
        }
    }
    printf("Maior nota: %.2f (aluno %d)\n", bestnote, best + 1);
    printf("Menor nota: %.2f (aluno %d)\n", worstnote, worst + 1);
}
// --------------------------------------------------------------
void calcularAcimaDaMedia(float* notas, int n, float mid){
    int aboveaverage = 0;
    for (int i = 0; i < n; i++){
        if (notas[i] > mid){
            aboveaverage++;
        }
    }
    printf("Acima da media: %d\n", aboveaverage);
}
// --------------------------------------------------------------
void calcularMediana(float* notas, int n){
    float* arr = malloc(n * sizeof(float));
    checknull(arr);

    for (int i = 0; i < n; i++){
        arr[i] = notas[i];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j+1]){
                float temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    float medium = 0;
    if (n % 2 != 0){
        medium = arr[(n / 2)];
    } else {
        medium = ((arr[(n / 2) - 1] + arr[(n / 2)]) / 2);
    }
    printf("Mediana: %.2f\n", medium);
    free(arr);
}
// --------------------------------------------------------------
void calcularModa(float* notas, int n){
    int maxfrequency = 0;
    float moda = 0;
    int unique = 1;

    for (int i = 0; i < n; i++){
        int freq = 0;
        for (int j = 0; j < n; j++){
            if (notas[i] == notas[j]){
                freq++;
            }
        }
        if (maxfrequency < freq){
            maxfrequency = freq;
            moda = notas[i];
            unique = 1;
        }
        else if (maxfrequency == freq && notas[i] != moda){
            unique = 0;
        }
    }

    if (maxfrequency <= 1){
        printf("Moda: Nao ha moda unica\n");
    } else if (unique){
        printf("Moda: %.2f\n", moda);
    } else {
        printf("Moda: Nao ha moda unica\n");
    }
}
// --------------------------------------------------------------
void operations(float* notas, int n){
    float mid = calcularMedia(notas, n);
    printf("Media: %.2f\n", mid);
    calcularMaiorMenor(notas, n);
    calcularAcimaDaMedia(notas, n, mid);
    calcularMediana(notas, n);
    calcularModa(notas, n);
    printf("\n");
}