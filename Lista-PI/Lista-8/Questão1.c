#include <stdio.h>

typedef union {
    unsigned char byte; 
    struct {
        unsigned int errobit : 1;
        unsigned int operacaobit : 3;
        unsigned int sensorbit : 4;
    } bitfield;
} Simulador;

int main (void){
    Simulador Bits;
    scanf("%hhu", &Bits.byte);

    printf (
        "Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n",
        Bits.byte,
        Bits.bitfield.errobit,
        Bits.bitfield.operacaobit,  
        Bits.bitfield.sensorbit
    );
}