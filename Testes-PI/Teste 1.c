#include <stdio.h>

int main(){
    int V1, V2, V3, D;
    int caminhodireto = 0;
    int caminhop2 = 0;
    scanf("%d %d %d %d", &V1, &V2, &V3, &D);
    
    // Ver a quantidade de energia dos caminhos
    caminhodireto = V1 + V3;
    caminhop2 = V1 + V2 + V3;

    // João sempre vai escolher o caminho com mais energia.
    // O código vital
    int D1 = D / 10;
    int D2 = D % 10;

    if (D1 > D2){
        caminhodireto += (D1 - D2);
    }
    else if (D2 > D1){
        caminhop2 += (D2 - D1);
    }
    else{
        caminhodireto += (D1 + D2);
        caminhop2 += (D1 + D2);
    }
    // A Escolha do Caminho
    if (caminhodireto > caminhop2){
        if (caminhodireto > 30){printf("Caminho: direto. Xupenio aprova! Nível: ELITE.");}
        else if (caminhodireto >= 10){printf("Caminho: direto. Boa caminhada! Nível: SÓLIDO.");}
        else if (caminhodireto > 0){printf("Caminho: direto. Passou por pouco. Nível: BÁSICO.");}
        else{printf("Caminho: direto. Xupenio reprova. Nível: CRÍTICO.");}
    }
    else if (caminhop2 > caminhodireto || caminhop2 == caminhodireto){
        if (caminhodireto > 30){printf("Caminho: P2. Xupenio aprova! Nível: ELITE.");}
        else if (caminhodireto >= 10){printf("Caminho: P2. Boa caminhada! Nível: SÓLIDO.");}
        else if (caminhodireto > 0){printf("Caminho: P2. Passou por pouco. Nível: BÁSICO.");}
        else{printf("Caminho: P2. Xupenio reprova. Nível: CRÍTICO.");}
    }
    return 0;
}