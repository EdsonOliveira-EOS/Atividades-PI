// Refazendo para treinar

#include <stdio.h>
#include <stdlib.h>

void checknull (void* pointer);
// ----------------------------------------------------
float* getgrades(float* StudentGrades, int n);
float* getnewgrades(float* NewGrades, int newsize, int n);
// ----------------------------------------------------
void operations(float* StudentGrades, int n);

float medium (float* StudentGrades, int n);
void grading(float* StudentGrades, int n);
void abovemedium(float* StudentGrades, int n, float medium);
void median(float* StudentGrades, int n);
void mode(float* StudentGrades, int n);
// ----------------------------------------------------
int main(void){

    int n;
    scanf ("%d", &n);

    float* StudentGrades = malloc(n * sizeof(float));
    checknull (StudentGrades);

    printf ("Relatorio inicial\n");
    getgrades(StudentGrades, n);
    operations(StudentGrades, n);

    int k;
    scanf("%d", &k);
    int newsize = n + k;

    float* NewGrades = realloc(StudentGrades, newsize * sizeof(float));
    checknull(NewGrades);
    StudentGrades = NewGrades;
    printf ("Relatorio atualizado\n");

    getnewgrades(StudentGrades, newsize, n);
    operations(StudentGrades, newsize);

    free(StudentGrades);

}
// ----------------------------------------------------
void checknull (void* pointer){
    if (pointer == NULL){
        printf ("Memoria não alocada\n");
        exit(1);
    }
}
// ----------------------------------------------------
float* getgrades(float* StudentGrades, int n){

    for (int i = 0; i < n; i++){
        float temp;
        scanf("%f", &temp);
        StudentGrades[i] = temp;
    }
    return StudentGrades;
}
// ----------------------------------------------------
float* getnewgrades(float* StudentGrades, int newsize, int n){
    for (int i = n; i < newsize; i++){
        float temp;
        scanf("%f", &temp);
        StudentGrades[i] = temp;
    }
    return StudentGrades;
}
// ----------------------------------------------------
void operations(float* StudentGrades, int n){

    float avg = medium(StudentGrades, n);

    grading(StudentGrades, n);
    abovemedium(StudentGrades, n, avg);
    median(StudentGrades, n);
    mode(StudentGrades, n);

    printf ("\n");
}
// ----------------------------------------------------
float medium (float* StudentGrades, int n){
    float medium = 0;
    for (int i = 0; i < n; i++){
        medium += StudentGrades[i];
    } medium /= n;
    printf ("Media: %.2f\n", medium);

    return medium;
}
// ----------------------------------------------------
void grading(float* StudentGrades, int n){
    float bestgrade = 0, worstgrade = 11;
    int bestidx = 0, worstidx = 0;

    for (int i = 0; i < n; i++){
        if (StudentGrades[i] > bestgrade){
            bestgrade = StudentGrades[i];
            bestidx = i+1;
        }
        if (StudentGrades[i] < worstgrade){
            worstgrade = StudentGrades[i];
            worstidx = i+1;
        }
    }
    printf ("Maior nota: %.2f (aluno %d)\n", bestgrade, bestidx);
    printf ("Menor nota: %.2f (aluno %d)\n", worstgrade, worstidx);
}
// ----------------------------------------------------
void abovemedium(float* StudentGrades, int n, float medium){
    int StudentsAboveMedium = 0;

    for (int i = 0; i < n; i++){
        if (StudentGrades[i] > medium){
            StudentsAboveMedium++;
        }
    }
    printf ("Acima da media: %d\n", StudentsAboveMedium);
}
// ----------------------------------------------------
void median(float* StudentGrades, int n){
    
    float* crescentgrades = malloc(n * sizeof(float));
    checknull(crescentgrades);

    for (int i = 0; i < n; i++){
        crescentgrades[i] = StudentGrades[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (crescentgrades[j] > crescentgrades[j+1]){
                float temp = crescentgrades[j];
                crescentgrades[j] = crescentgrades[j+1];
                crescentgrades[j+1] = temp;
            }
        }
    }

    float median = 0;
    if (n % 2 == 0){median = (((crescentgrades[n / 2]) + (crescentgrades[(n / 2) - 1])) / 2);} 
    else {median = crescentgrades[(n / 2)];}

    printf ("Mediana: %.2f\n", median);
    free(crescentgrades);
}
// ----------------------------------------------------
void mode(float* StudentGrades, int n){
    int maxfrequency = 0;
    float modegrade = 0;
    int unique = 1;

    for (int i = 0; i < n; i++){
        int frequency = 0;
        for (int j = 0; j < n; j++){
            if (StudentGrades[i] == StudentGrades[j]){
                frequency++;
            }
        }
        if (frequency > maxfrequency){
            modegrade = StudentGrades[i];
            maxfrequency = frequency;
            unique = 1;
        } 
        else if (frequency == maxfrequency && modegrade != StudentGrades[i]){
            unique = 0;
        }
    }

    if (maxfrequency <= 1){
        printf ("Moda: Nao ha moda unica\n");
    }
    else if (unique){
        printf ("Moda: %.2f\n", modegrade);
    } else {
        printf ("Moda: Nao ha moda unica\n");
    }
}