#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
    uint32_t rawbits;
    struct {
        unsigned int id : 10;
        unsigned int status : 3;
        unsigned int bateria : 1;
        int temperatura : 12;
        unsigned int controle : 6;
    } bitfield;
} Pacotes;

int main (void){
    int tamanhoarbitrario = 1;
    int tamanho = 0;

    Pacotes *Processamento = malloc (tamanhoarbitrario * sizeof(Pacotes));
    if (Processamento == NULL){
        printf ("Não alocado\n");
        exit(1);
    }
    uint32_t entrada;
    while (scanf("%x", &entrada) == 1 && entrada != 0){
        if (tamanho == tamanhoarbitrario){
            tamanhoarbitrario *= 2;
            Pacotes *temp = realloc(Processamento, tamanhoarbitrario * sizeof(Pacotes));
            if (temp == NULL){
                printf ("Não alocado\n");
                free(Processamento);
                exit(1);
            }
            Processamento = temp;
        }
        Processamento[tamanho].rawbits = entrada;
        tamanho++;
    }

    for (int i = 0; i < tamanho; i++){
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, Processamento[i].rawbits);
        printf("ID do Sensor : %d\n", Processamento[i].bitfield.id);
        printf("Status : %d\n", Processamento[i].bitfield.status);
        printf("Bateria Baixa: %s\n", Processamento[i].bitfield.bateria ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura : %d graus\n", Processamento[i].bitfield.temperatura);
        printf("----------------------------------------\n");
    }
    free(Processamento);

    return 0;
}