#include <stdio.h>
#include <stdlib.h>

float* LerNotas(float* notas, int n){
    for (int i = 0; i < n; i++){
        float temp;
        scanf("%f", &temp);
        notas[i] = temp;
    }
    return notas;
}

void operations(float* notas, int n){
    // Calcular a média
    float mid = 0.00;
    for (int i = 0; i < n; i++){
        mid += notas[i];
    } mid /= n;
    printf ("Media: %.2f\n", mid);

    // Melhor Nota e pior nota
    int best = 1;
    float bestnote = notas[0];
    int worst = 1;
    float worstnote = notas[0];

    for (int i = 1; i < n; i++){
        if (notas[i] > bestnote){
            best = i+1;
            bestnote = notas[i];
        }

        if (notas[i] < worstnote){
            worst = i+1;
            worstnote = notas[i];
        }
    }
    printf ("Maior nota: %.2f (aluno %d)\n", bestnote, best);
    printf ("Menor nota: %.2f (aluno %d)\n", worstnote, worst);

    // Acima da Média
    int aboveaverage = 0;
    for (int i = 0; i < n; i++){
        if (notas[i] > mid){
            aboveaverage++;
        }
    }
    printf ("Acima da media: %d\n", aboveaverage);

    // Mediana
    // Primeiro sortar a lista
    float* arr = malloc(n * sizeof(float));
    for (int i = 0; i < n; i++){
        arr[i] = notas[i];  // copia valor por valor
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
    printf ("Mediana: %.2f\n", medium);

    // Moda
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
        printf ("Moda: %.2f\n", moda);
    } else {
        printf ("Moda: Nao ha moda unica\n");
    }

    free (arr);
    printf ("\n");
}

float* PlaceNewNotes(float* notas, int n, int newsize){
    for (int i = n; i < newsize; i++){
        float temp;
        scanf ("%f", &temp);
        notas[i] = temp;
    }
    return notas;
}

int main (void){
    int n;
    scanf ("%d", &n);

    float* notas = malloc(n * sizeof(float));
    if (notas == NULL){
        printf ("Erro ao alocar memória!\n");
        return 0;
    } 
    LerNotas(notas, n);

    printf ("Relatorio inicial\n");
    operations(notas, n);

    // Hora da alocação
    int k;
    scanf ("%d", &k);

    float* temp = realloc(notas, (n + k) * sizeof(float));
    if (temp == NULL){
        printf ("Erro ao alocar memória!\n");
        free(notas);
        return 0;
    }
    notas = temp;

    int newsize = n+k;
    PlaceNewNotes(notas, n, newsize);

    printf ("Relatorio atualizado\n");
    operations(notas, newsize);
    free(notas);
}