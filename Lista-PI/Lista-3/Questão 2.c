#include <stdio.h>

int main(void){

    int N, X, Y;
    int costumers[100000];
    scanf ("%d %d %d", &N, &X, &Y);

    for (int i = 1; i <= N; i++){
        if (X > 0 && i % X == 0){costumers[i] = 1;} else {costumers[i] = 0;}
    }

    for (int j = 1; j <= Y; j++){
        int sevenhours = 420;
        int comparinghour = 0;
        int hours, minutes;
        int position;
        int cans;
        scanf ("%d:%d %d", &hours, &minutes, &cans);

        comparinghour += minutes;
        comparinghour += (hours * 60);

        position = (comparinghour - sevenhours) / 3;
        costumers[position] = cans;
    }

    int counting = 0;
    for (int k = 1; k <= N; k++){
        int cansleft;
        int objectivecans = 50;
        counting += costumers[k];

        if (counting >= objectivecans){

            int totalminutes = 420 + (k * 3);
            int hour = totalminutes / 60;
            int minute = totalminutes % 60;

            if (costumers[k] == 1){
                printf ("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d lata.", k, hour, minute, costumers[k]);
            } else {
                printf ("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.", k, hour, minute, costumers[k]);
            }
            return 0;
        }

        if (k == N){
            cansleft = objectivecans - counting;
            if (cansleft != 1){
                printf ("Ainda nao foram vendidas latas suficientes. Faltam %d latas.", cansleft);
            } else {
                printf ("Ainda nao foram vendidas latas suficientes. Falta %d lata.", cansleft);
            }
        }
    }
}