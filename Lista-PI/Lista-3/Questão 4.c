#include <stdio.h>

int main(void){
    int R;
    scanf("%d", &R);

    char final[60000];
    int pos = 0;
    for (int i = 0; i < R; i++){
        char str[61];
        int clock;
        scanf("%s %d", str, &clock);

        // L�gica dos flashes
        for (int j = 0; j < clock; j++){
            int number = 0;
            int turnedon = 0;
            while (turnedon == 0 && str[number] != '\0'){
                if (str[number] == 'O'){
                    str[number] = 'X';
                    number++;
                } else {
                    str[number] = 'O';
                    turnedon = 1;
                }
            }
        }
        printf("%s\n", str);

        if (i > 0){
            char last = final[pos - 1];
            char first = str[0];
            int evensize = (pos % 2 == 0);

            if (evensize && last == first){
                final[pos] = '@';
                pos++;
            } else if (!evensize && last == first){
                final[pos] = '#';
                pos++;
            } else if (evensize && last != first){
                final[pos] = '$';
                pos++;
            } else {
                final[pos] = '%';
                pos++;
            }
        }
        for (int j = 0; str[j] != '\0'; j++){
            final[pos] = str[j];
            pos++;
        }
    }
    final[pos] = '\0';
    printf("%s\n", final);

    return 0;
}