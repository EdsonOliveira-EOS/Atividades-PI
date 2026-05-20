#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void checknull (void* pointer){
    if (pointer == NULL){
        printf ("Memoria não alocada\n");
        exit(1);
    }
}

typedef union {
    uint64_t raw;
    struct {
        uint64_t tipo : 2;
        uint64_t id_subsistema : 6;
        uint64_t eixo : 2;  
        uint64_t temperatura : 10;
        uint64_t velocidade_angular : 18;
        uint64_t paridade : 26; // Ignorar
    } tipo0;
    // ##### ##### ##### ##### ##### ##### ##### #####
    struct {
        uint64_t tipo : 2;
        uint64_t idsubsistema : 6;
        uint64_t tensao_painel : 12;
        uint64_t corrente_consumo : 12;
        uint64_t status_baterias_bit_0 : 1; // São 4 bits separados para maneirar melhor, mas a ''família toda'' de status_bateria dá 4 bits certinho.
        uint64_t status_baterias_bit_1 : 1;
        uint64_t status_baterias_bit_2 : 1;
        uint64_t status_baterias_bit_3 : 1;
        uint64_t checksum : 28; // Ignorar
    } tipo1;
    // ##### ##### ##### ##### ##### ##### ##### #####
    struct {
        uint64_t tipo : 2;
        uint64_t idsubsistema : 6;
        uint64_t codigo_erro : 8;
        uint64_t criticidade : 3;
        uint64_t timestamp : 20;
        uint64_t padding : 25; // Ignorar        
    } tipo2;
} Pacotes;

int main (void){

    int capacidade = 4;
    int tamanho = 0;
    Pacotes *Processamento = malloc (capacidade * sizeof(Pacotes));
    checknull (Processamento);

    uint64_t entrada;
    while (scanf("%llx", (unsigned long long*) &entrada) == 1 && entrada != 0){
        if (tamanho == capacidade){
            capacidade += 4; // Aumenta a capacidade em 4, aritmético sem dobrar.
            Pacotes *temp = realloc (Processamento, capacidade * sizeof(Pacotes));
            checknull (temp);
            Processamento = temp; // Ao fazer isso ele dá free automaticamente no temp
        }
        Processamento[tamanho].raw = entrada;
        // Lógica de descartar aqui
        if (Processamento[tamanho].tipo0.tipo == 3 || (Processamento[tamanho].tipo2.tipo == 2 && Processamento[tamanho].tipo2.criticidade > 4)){ // Caso for tipo 3 ou tipo for 2 e a criticidade for maior que 4
            tamanho--; // Isso é para sobrescrever o tamanho, isso vai tirar um tamanho e vai fazer o tamanho ''estagnar'', então o próximo vai simplesmente sobrescrever o de cima.
        }
        tamanho++;
    }

    // Isso daqui é para caso for o ''último'' tiver ainda pegando espaço e era um dos que era para tirar, ele vai ''emprensar'' o vetor e vai descartar automaticamente o último vetor colocado.
    Pacotes *temp2 = realloc (Processamento, tamanho *sizeof(Pacotes));
    checknull (temp2);
    Processamento = temp2; // Ao fazer isso ele dá free automaticamente no temp2.
    // ##############
    float totaltemperatura = 0;
    int pacotestipo0 = 0;
    // ##############
    float totalcorrente = 0;
    int pacotestipo1 = 0;
    // ##############
    int alertas = 0;

    printf ("RELATÓRIO DE TELEMETRIA - CUBESAT\n");
    for (int i = 0; i < tamanho; i++){
        printf ("[Registro %d] RAW: 0x%016llX\n", i+1, (unsigned long long) Processamento[i].raw);

        if (Processamento[i].tipo0.tipo == 0){
            printf ("-> Tipo: Navegação\n");
            printf ("-> ID do Subsistema Origem: %d\n", Processamento[i].tipo0.id_subsistema);
            printf ("-> Temperatura: %d°C\n", Processamento[i].tipo0.temperatura);
            totaltemperatura += Processamento[i].tipo0.temperatura;
            printf ("-> Velocidade Angular: %d rad/s\n", Processamento[i].tipo0.velocidade_angular);

            if (Processamento[i].tipo0.eixo == 0){printf ("-> Eixo: X\n");}
            else if (Processamento[i].tipo0.eixo == 1) {printf ("-> Eixo: Y\n");}
            else if (Processamento[i].tipo0.eixo == 2){printf ("-> Eixo: Z\n");} 
            else {printf ("-> Eixo: Calibração\n");}
            pacotestipo0++;
        }
        else if (Processamento[i].tipo0.tipo == 1) { 
            printf ("-> Tipo: Energia\n");
            printf ("-> ID do Subsistema Origem: %d\n", Processamento[i].tipo0.id_subsistema);
            printf ("-> Tensão do Painel: %d mV\n", Processamento[i].tipo1.tensao_painel);
            printf ("-> Corrente de Consumo: %d mA\n", Processamento[i].tipo1.corrente_consumo);
            totalcorrente += Processamento[i].tipo1.corrente_consumo;

            if (Processamento[i].tipo1.status_baterias_bit_0 == 0 && Processamento[i].tipo1.status_baterias_bit_1 == 0 && Processamento[i].tipo1.status_baterias_bit_2 == 0 && Processamento[i].tipo1.status_baterias_bit_3 == 0){
                printf ("-> Status da Baterias: OK\n");
            } else {
                printf ("-> Status da Baterias: Falha no(s) quadrante(s) ");
                if (Processamento[i].tipo1.status_baterias_bit_0 == 1){
                    printf ("0 ");
                }
                if (Processamento[i].tipo1.status_baterias_bit_1 == 1){
                    printf ("1 ");
                }
                if (Processamento[i].tipo1.status_baterias_bit_2 == 1){
                    printf ("2 ");
                }
                if (Processamento[i].tipo1.status_baterias_bit_3 == 1){
                    printf ("3 ");
                }
                printf ("\n");
            }
            pacotestipo1++;
        }

        else if (Processamento[i].tipo0.tipo == 2){
            printf ("-> Tipo: Alerta do Sistema\n");
            printf ("-> ID do Subsistema Origem: %d\n", Processamento[i].tipo0.id_subsistema);
            printf ("-> Código do Erro: %d\n", Processamento[i].tipo2.codigo_erro);

            if (Processamento[i].tipo2.criticidade == 0){printf ("-> Nível de Criticidade: Info\n");}
            else if (Processamento[i].tipo2.criticidade == 1){printf ("-> Nível de Criticidade: Warning\n");}
            else if (Processamento[i].tipo2.criticidade == 2) {
                printf ("-> Nível de Criticidade: Severe\n");
                alertas++;
            }
            else {
                printf ("-> Nível de Criticidade: Fatal\n");
                alertas++;
            }
            printf ("-> Timestamp Relativo: %d ms\n", Processamento[i].tipo2.timestamp);
        }
    }
    if (pacotestipo0 > 0){
        totaltemperatura /= pacotestipo0;
    }
    if (pacotestipo1 > 0){
        totalcorrente /= pacotestipo1;
    }
    printf ("\nESTATÍSTICAS CONSOLIDADAS\n");
    printf ("- Total de pacotes válidos processados: %d\n", tamanho);
    printf ("- Média de Temperatura Externa (Tipo 0): %.2f°C\n", totaltemperatura);
    printf ("- Média de Corrente de Consumo (Tipo 1): %.2f mA\n", totalcorrente);
    printf ("- Alertas Críticos Detectados (Severe/Fatal): %d\n", alertas);

    free(Processamento); // Free final, e como foi só um malloc, é apenas um free dito que reallocs já dão free automaticamente.
}