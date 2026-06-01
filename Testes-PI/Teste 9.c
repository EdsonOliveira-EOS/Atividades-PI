#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checknull(void* p) {
    if(p == NULL) {
        printf("Erro na alocação.\n");
        exit(1);
    }
}

typedef struct {
    int codigo;
    char nome[50];
    float saldo;
} Contas;

typedef struct {
    int codigo;
    char movimento;

    // Depósito
    struct {
        float deposito;
    } D;
    // Saque
    struct {
        float saque;
    } S;
    // Pix
    struct {
        int codigo_conta_receber;
        float valor;
    } Pix;
} Movimentos;

int procurar_conta(Contas *contas, int codigoconta, int quantidade_contas){
    for (int i = 0; i < quantidade_contas; i++){
        if (contas[i].codigo == codigoconta){
            return i; // Se achou, retorna o nosso índice da conta
        }
    }
    return -1; // Se não, retorna -1;
}

void processo(int quantidade_dias){
    // 1. Ler datas
    char nomeoperacoes[22];
    char nomerelatorio[22];
    int dias, mes, anos;
    scanf ("%d/%d/%d", &dias, &mes, &anos);
    sprintf(nomeoperacoes, "operacoes_%d%d%d.txt", dias, mes, anos);
    sprintf(nomerelatorio, "relatorio_%d%d%d.txt", dias, mes, anos);
    // ################################################################################################
    Contas contas[100];
    FILE *p = fopen("contas.txt", "r+"); // Para ler e escrever.
    if (p == NULL){
        printf ("Arquivo não acessado.\n");
        exit(1);
    }
    // 2. Carregar contas
    int quantidade_contas = 0;
    while (fscanf(p, "%d %s %f", &contas[quantidade_contas].codigo, contas[quantidade_contas].nome, &contas[quantidade_contas].saldo) == 3){
        quantidade_contas++;
    }
    fseek (p, 0, SEEK_SET); // Setando o cursor para depois sobrescrever
    // ################################################################################################
    Movimentos movimentos[100];
    FILE *o = fopen(nomeoperacoes, "r"); // Só ler
    if (o == NULL){
        printf ("Arquivo não acessado.\n");
        exit(1);
    }
    // 3. Processar Operações
    int conta_inexistente = 0;
    int saldo_insuficiente = 0;

    char historico [1000] = "";
    char extrato [1000] = "";

    char inconsistencias [1000] = "";
    int quantidade_movimentos = 0;
    while (fscanf(o, "%d %c", &movimentos[quantidade_movimentos].codigo, &movimentos[quantidade_movimentos].movimento) != EOF){
        if (movimentos[quantidade_movimentos].movimento == 'D'){
            fscanf(o, "%f", &movimentos[quantidade_movimentos].D.deposito);
            int achou;
            achou = procurar_conta(contas, movimentos[quantidade_movimentos].codigo, quantidade_contas);
            if (achou == -1){
                conta_inexistente++;

                char inconsistencia[50];
                sprintf(inconsistencia, "%03d %c %.2f CONTA_INEXISTENTE\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].D.deposito);
                strcat (historico, inconsistencia);
                strcat (inconsistencias, inconsistencia);
            } else {
                char aplicado[50];
                sprintf(aplicado, "%03d %c %.2f APLICADA\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].D.deposito);
                strcat (historico, aplicado);

                contas[achou].saldo += movimentos[quantidade_movimentos].D.deposito;
                quantidade_movimentos++;
                // Tenho que ainda dar uma forma de usar isso no extrato
            }
        }
        // ################################################################################################
        else if (movimentos[quantidade_movimentos].movimento == 'S'){
            fscanf(o, "%f", &movimentos[quantidade_movimentos].S.saque);

            int achou;
            achou = procurar_conta(contas, movimentos[quantidade_movimentos].codigo, quantidade_contas);

            if (achou == -1){
                conta_inexistente++;

                char inconsistencia[50];
                sprintf(inconsistencia, "%03d %c %.2f CONTA_INEXISTENTE\n", 
                movimentos[quantidade_movimentos].codigo, 
                movimentos[quantidade_movimentos].movimento, 
                movimentos[quantidade_movimentos].S.saque);
                strcat (historico, inconsistencia);
                strcat (inconsistencias, inconsistencia);   
            } else {
                if (contas[achou].saldo >= movimentos[quantidade_movimentos].S.saque){
                    char aplicado[50];
                    sprintf(aplicado, "%03d %c %.2f APLICADA\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].S.saque);
                    strcat (historico, aplicado);

                    contas[achou].saldo -= movimentos[quantidade_movimentos].S.saque;
                    quantidade_movimentos++;
                } else {
                    saldo_insuficiente++;

                    char inconsistencia[50];
                    sprintf(inconsistencia, "%03d %c %.2f SALDO_INSUFICIENTE\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].S.saque);
                    strcat (historico, inconsistencia);
                    strcat (inconsistencias, inconsistencia);
                }
            }
        }
        // ################################################################################################
        else if (movimentos[quantidade_movimentos].movimento == 'P'){
            fscanf (o, "%d %f", &movimentos[quantidade_movimentos].Pix.codigo_conta_receber, &movimentos[quantidade_movimentos].Pix.valor);

            int achouorigem;
            achouorigem = procurar_conta(contas, movimentos[quantidade_movimentos].codigo, quantidade_contas);
            int achoudestino;
            achoudestino = procurar_conta(contas, movimentos[quantidade_movimentos].Pix.codigo_conta_receber, quantidade_contas);

            if (achouorigem == -1){
                conta_inexistente++;

                char inconsistencia[50];
                sprintf(inconsistencia, "%03d %c %03d %.2f CONTA__ORIGEM_INEXISTENTE\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].Pix.codigo_conta_receber,
                    movimentos[quantidade_movimentos].Pix.valor);
                strcat (historico, inconsistencia);
                strcat (inconsistencias, inconsistencia);   
            } else if (achoudestino == -1){
                conta_inexistente++;

                char inconsistencia[50];
                sprintf(inconsistencia, "%03d %c %03d %.2f CONTA__DESTINO_INEXISTENTE\n", 
                    movimentos[quantidade_movimentos].codigo, 
                    movimentos[quantidade_movimentos].movimento, 
                    movimentos[quantidade_movimentos].Pix.codigo_conta_receber,
                    movimentos[quantidade_movimentos].Pix.valor);
                strcat (historico, inconsistencia);
                strcat (inconsistencias, inconsistencia);   
            } else {
                if (contas[achouorigem].saldo >= movimentos[quantidade_movimentos].Pix.valor){
                    char aplicado[50];
                    sprintf(aplicado, "%03d %c %03d %.2f APLICADA\n", 
                        movimentos[quantidade_movimentos].codigo, 
                        movimentos[quantidade_movimentos].movimento, 
                        movimentos[quantidade_movimentos].Pix.codigo_conta_receber,
                        movimentos[quantidade_movimentos].Pix.valor);
                    strcat (historico, aplicado);

                    contas[achouorigem].saldo -= movimentos[quantidade_movimentos].Pix.valor;
                    contas[achoudestino].saldo += movimentos[quantidade_movimentos].Pix.valor;
                    quantidade_movimentos++;
                } else {
                    saldo_insuficiente++;
                    char inconsistencia[50];
                    sprintf(inconsistencia, "%03d %c %d %.2f SALDO_INSUFICIENTE\n", 
                        movimentos[quantidade_movimentos].codigo, 
                        movimentos[quantidade_movimentos].movimento, 
                        movimentos[quantidade_movimentos].Pix.codigo_conta_receber,
                        movimentos[quantidade_movimentos].Pix.valor);
                    strcat (historico, inconsistencia);
                    strcat (inconsistencias, inconsistencia);   
                }
            }
        }
    }
    // 4. Salva estado;
    for (int i = 0; i < quantidade_contas; i++){
        fprintf (p, "%03d %s %.2f\n", contas[i].codigo, contas[i].nome, contas[i].saldo);
    }
    // 5. Salva histórico;
    FILE *h = fopen("historico.txt", "a");
    if (h == NULL){
        printf ("Arquivo não acessado.\n");
        exit(1);
    }
    fprintf (h, "[%d/%d/%d]\n", dias, mes, anos);
    fprintf (h, "%s", historico);
    fprintf (h, "[/%d/%d/%d]\n", dias, mes, anos);

    // 6. Relatório:
    FILE *r = fopen(nomerelatorio, "a");
    if (r == NULL){
        printf ("Arquivo não acessado.\n");
        exit(1);
    }
    fprintf (r, "DATA: %d/%d/%d\n", dias, mes, anos);
    fprintf (r, "CONTAS NO BANCO: %d\n", quantidade_contas);
    fprintf (r, "OPERACOES APLICADAS: %d\n", quantidade_movimentos);
    fprintf (r, "SALDO INSUFICIENTE: %d\n", saldo_insuficiente);
    fprintf (r, "CONTA INEXISTENTE: %d\n", conta_inexistente);
    fprintf (r, "SALDO BAIXO (< 300.00):\n");
    for (int i = 0; i < quantidade_contas; i++){
        if (contas[i].saldo < 300.00){
            fprintf (r, "%03d %s %.2f\n", contas[i].codigo, contas[i].nome, contas[i].saldo);
        }
    }
    fprintf (r, "INCONSISTENCIAS:\n");
    if (strlen(inconsistencias) == 0){
        sprintf (inconsistencias, "(nenhuma)");
    }
    fprintf (r, "%s\n", inconsistencias);

    // F closes
    fclose(p);
    fclose(h);
    fclose(o);
    fclose(r);
}

int main (){
    int quantidade_dias;
    scanf("%d", &quantidade_dias);

    for (int i = 1; i <= quantidade_dias; i++){
        processo(i);
    }
    // 7. Extrato
    // Infelizmente não deu tempo de fazer, eu saberia fazer notavelmente devido aos códigos acima mas quando terminei o histórico era 16:30, dava tempo não.
}