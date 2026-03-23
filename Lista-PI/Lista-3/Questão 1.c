#include <stdio.h>

int main(void){
    int testcases;
    scanf ("%d", &testcases);

    for (int i = 0; i < testcases; i++){
        int sequencysize;
        scanf ("%d", &sequencysize);

        int array[100];
        for (int j = 0; j < sequencysize; j++){scanf ("%d", &array[j]);}

        int beststart = 0, bestsize = 0;
        int actualstart = 0, actualsize = 1;

        for (int l = 1; l < sequencysize; l++){
            if (array[l] < array[l - 1]){
                actualsize++;
            } else {
                if (actualsize > bestsize && actualsize >= 2){
                    bestsize = actualsize;
                    beststart = actualstart;
                }
                actualstart = l;
                actualsize = 1;
            }
        }
        if (actualsize > bestsize && actualsize >= 2){
            bestsize = actualsize;
            beststart = actualstart;
        }
        printf ("%d\n", bestsize);
        if (bestsize > 0){
            for (int j = beststart; j < beststart + bestsize; j++){
                printf("%d ", array[j]);
            }
            printf("\n");
        }
    }
    return 0;
}