#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

void subrotina_defesa(Mecha *m, int slot, int input, int *output){
    int danofinal = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (danofinal < 0){danofinal = 0;}
    *output = danofinal;
}

void subrotina_utilidade(Mecha *m, int slot, int input, int *output){
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
    *output = m->energia_atual;
}

void subrotina_ataque(Mecha *m, int slot, int input, int *output){
    if (m->energia_atual < m->sistemas[slot].atrib2){*output = 0;}
    else {int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input; *output = dano; m->energia_atual -= m->sistemas[slot].atrib2;}
}

int main (void){

    int n;
    scanf("%d", &n);

    Mecha *esquadrao[n];
    for (int i = 0; i < n; i++){
        int id, Q, energia;
        char modelo[50];
        scanf("%d %s %d %d", &id, modelo, &energia, &Q);

        esquadrao[i] = malloc(sizeof(Mecha) + Q * sizeof(SubSistema));
        if (esquadrao[i] == NULL){printf ("Falha de Memória\n"); for (int k = 0; k < i; k++) free(esquadrao[k]); exit(1);}
        esquadrao[i]->id = id;
        esquadrao[i]->energia_atual = energia;
        esquadrao[i]->num_sistemas = Q;
        strcpy(esquadrao[i]->modelo, modelo);

        // Subsistemas:
        for (int j = 0; j < Q; j++){
            char tipo;
            scanf(" %c %s %d %d", &tipo, esquadrao[i]->sistemas[j].nome, &esquadrao[i]->sistemas[j].atrib1, &esquadrao[i]->sistemas[j].atrib2);

            if (tipo == 'D'){esquadrao[i]->sistemas[j].subrotina = subrotina_defesa;}
            else if (tipo == 'U'){esquadrao[i]->sistemas[j].subrotina = subrotina_utilidade;}
            else if (tipo == 'A'){esquadrao[i]->sistemas[j].subrotina = subrotina_ataque;}
        }
        scanf("%d", &esquadrao[i]->valor_wintermute);
    }

    // Ordenação:
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (esquadrao[j]->id > esquadrao[j+1]->id){
                Mecha *temp = esquadrao[j];
                esquadrao[j] = esquadrao[j+1];
                esquadrao[j+1] = temp;
            }
        }
    }
    
    // Fase de combate:
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");
    for (int i = 0; i < n; i++){
        int output = 0;
        printf ("ID: %d | MECHA: %s | ENERGIA: %d\n", esquadrao[i]->id, esquadrao[i]->modelo, esquadrao[i]->energia_atual);

        // Defesa
        for (int j = 0; j < esquadrao[i]->num_sistemas; j++){
            if (esquadrao[i]->sistemas[j].subrotina == subrotina_defesa){
                esquadrao[i]->sistemas[j].subrotina(esquadrao[i], j, esquadrao[i]->valor_wintermute, &output);
                printf ("-> [DEFESA] %s | Dano final sofrido: %d\n", esquadrao[i]->sistemas[j].nome, output);
            }
        }
        // Utilidade
        for (int j = 0; j < esquadrao[i]->num_sistemas; j++){
            if (esquadrao[i]->sistemas[j].subrotina == subrotina_utilidade){
                esquadrao[i]->sistemas[j].subrotina(esquadrao[i], j, esquadrao[i]->valor_wintermute, &output);
                printf ("-> [UTILIDADE] %s | Energia atual: %d\n", esquadrao[i]->sistemas[j].nome, output);
            }
        }
        // Ataque
        for (int j = 0; j < esquadrao[i]->num_sistemas; j++){
            if (esquadrao[i]->sistemas[j].subrotina == subrotina_ataque){
                esquadrao[i]->sistemas[j].subrotina(esquadrao[i], j, esquadrao[i]->valor_wintermute, &output);
                if (output == 0){printf ("-> [ATAQUE] %s | Energia insuficiente!\n", esquadrao[i]->sistemas[j].nome);}
                else {printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", esquadrao[i]->sistemas[j].nome, output, esquadrao[i]->energia_atual);}
            }
        }
        printf ("ENERGIA FINAL: %d\n", esquadrao[i]->energia_atual);
        printf ("-----------------------------------------\n");
    }
    printf ("Esquadrao pronto para o combate.\n");

    for (int i = 0; i < n; i++) {
        free(esquadrao[i]);
    }
}