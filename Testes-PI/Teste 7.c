#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Nodo Nodo;

typedef struct {
    char rotulo[30];
    int coef1; // Escudo: Absorção Fixa | Regulador: Captação Base | Conversor: Custo Base | Pulso: Emissão Base
    int coef2; // Escudo: Fator de Slot | Regulador: Mult. de Slot | Conversor: Ganho | Pulso: Custo

    // Protocolo Modular: atribuído conforme o tipo durante a montagem.
    // n: ponteiro para o nodo dono do módulo.
    // slot: índice original deste módulo no array modulos[] da struct Nodo — ou seja, a posição (0-based) em que ele foi alocado dentro do nodo dono; deve ser passado exatamente como armazenado, sem reordenação.
    // sinal: intensidade do pulso de corrupção enviado pela Rede Carmesim.
    // resultado: onde o valor calculado deve ser gravado.
    void (*protocolo)(Nodo *n, int slot, int sinal, int *resultado);
} Modulo;

struct Nodo {
    int uid; // Identificador único (0 até N-1)
    char arquitetura[50];
    int carga_atual;
    int num_modulos;
    int sinal_micelio; // Intensidade do pulso de corrupção recebido
    Modulo modulos[]; // Flexible Array Member (FAM)
};

void Escudo_Function(Nodo *n, int slot, int sinal, int *resultado){
    int absorcao_final = sinal - n->modulos[slot].coef1 - (slot * n->modulos[slot].coef2);
    if (absorcao_final < 0){absorcao_final = 0;}
    *resultado = absorcao_final;
}
void Regulador_Function(Nodo *n, int slot, int sinal, int *resultado){
    int Captado = n->modulos[slot].coef1 + (slot * n->modulos[slot].coef2);
    n->carga_atual += Captado;
    *resultado = n->carga_atual;
}
void Conversor_Function(Nodo *n, int slot, int sinal, int *resultado){
    int Custo = n->modulos[slot].coef1 + slot;
    int Ganho = n->modulos[slot].coef2;

    if (n->carga_atual < Custo){*resultado = 0;}
    else {n->carga_atual = n->carga_atual - Custo + Ganho; *resultado = Ganho;}
}
void Pulso_Function(Nodo *n, int slot, int sinal, int *resultado){
    int Custo = n->modulos[slot].coef2;

    if (n->carga_atual < Custo){*resultado = 0;}
    else {
        int emissao = n->modulos[slot].coef1 + n->carga_atual + slot - sinal;
        if (emissao < 0){emissao = 0;}
        
        n->carga_atual -= Custo;
        *resultado = emissao+1;
    }
}

int main (void){
    int n;
    scanf("%d", &n);
    Nodo *protocolo[n];

    for(int i = 0; i < n; i++){
        int id, carga_inicial, q;
        char arquiteturastr[50];
        scanf("%d %s %d %d", &id, arquiteturastr, &carga_inicial, &q);
        
        protocolo[i] = malloc(sizeof(Nodo) + q * sizeof(Modulo));
        if (protocolo[i] == NULL){
            printf ("Erro de Alocação\n");
            for (int k = 0; k < i; i++){
                free(protocolo[k]);
            }
            exit(1);
        }

        strcpy(protocolo[i]->arquitetura, arquiteturastr);
        protocolo[i]->uid = id;
        protocolo[i]->carga_atual = carga_inicial;
        protocolo[i]->num_modulos = q;

        for (int j = 0; j < q; j++){
            char tipo;
            scanf(" %c %s %d %d", &tipo, protocolo[i]->modulos[j].rotulo, &protocolo[i]->modulos[j].coef1, &protocolo[i]->modulos[j].coef2);

            if (tipo == 'E'){protocolo[i]->modulos[j].protocolo = &Escudo_Function;}
            if (tipo == 'R'){protocolo[i]->modulos[j].protocolo = &Regulador_Function;}
            if (tipo == 'C'){protocolo[i]->modulos[j].protocolo = &Conversor_Function;}
            if (tipo == 'P'){protocolo[i]->modulos[j].protocolo = &Pulso_Function;}
        }
        scanf("%d", &protocolo[i]->sinal_micelio);
    }

    // Sortar os ids
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (protocolo[j]->uid > protocolo[j+1]->uid){
                Nodo *temp = protocolo[j];
                protocolo[j] = protocolo[j+1];
                protocolo[j+1] = temp;
            }
        }
    }

    // Relatório
    printf ("[RELATORIO DE REDE: PROTOCOLO RAIZ CARMESIM]\n");
    for (int i = 0; i < n; i++){
        printf ("UID: %d | NÓ: %s | CARGA: %d\n", protocolo[i]->uid, protocolo[i]->arquitetura, protocolo[i]->carga_atual);

        // Prioridade 1: Escudo
        for (int j = 0; j < protocolo[i]->num_modulos; j++){
            int resultado = 0;
            if (protocolo[i]->modulos[j].protocolo == Escudo_Function){
                protocolo[i]->modulos[j].protocolo(protocolo[i], j, protocolo[i]->sinal_micelio, &resultado);
                printf ("-> [ESCUDO] %s | Absorção registrada: %d\n", protocolo[i]->modulos[j].rotulo, resultado);
            }
        }
        // Prioridade 2: Regulador 
        for (int j = 0; j < protocolo[i]->num_modulos; j++){
            int resultado = 0;
            if (protocolo[i]->modulos[j].protocolo == Regulador_Function){
                protocolo[i]->modulos[j].protocolo(protocolo[i], j, protocolo[i]->sinal_micelio, &resultado);
                printf ("-> [REGULADOR] %s | Carga sincronizada: %d\n", protocolo[i]->modulos[j].rotulo, resultado);
            }
        }
        // Prioridade 3: Conversor
        for (int j = 0; j < protocolo[i]->num_modulos; j++){
            int resultado = 0;
            if (protocolo[i]->modulos[j].protocolo == Conversor_Function){
                protocolo[i]->modulos[j].protocolo(protocolo[i], j, protocolo[i]->sinal_micelio, &resultado);
                if (resultado == 0){printf ("-> [CONVERSOR] %s | Conversão inviável!\n", protocolo[i]->modulos[j].rotulo);}
                else {printf ("-> [CONVERSOR] %s | Energia convertida: %d\n", protocolo[i]->modulos[j].rotulo, resultado);}
            }
        }
        // Prioridade 4: Pulso
        for (int j = 0; j < protocolo[i]->num_modulos; j++){
            int resultado = 0;

            if (protocolo[i]->modulos[j].protocolo == Pulso_Function){
                protocolo[i]->modulos[j].protocolo(protocolo[i], j, protocolo[i]->sinal_micelio, &resultado);
                if (resultado == 0){printf ("-> [PULSO] %s | Carga crítica!\n", protocolo[i]->modulos[j].rotulo);}
                else {printf ("-> [PULSO] %s | Emissão calculada: %d | Carga restante: %d\n", protocolo[i]->modulos[j].rotulo, resultado-1, protocolo[i]->carga_atual);}
            }
        }
        printf ("CARGA FINAL: %d\n", protocolo[i]->carga_atual);
        printf ("=========================================\n");
    }
    printf ("Rede estabilizada. Micélio contido.\n");

    for (int i = 0; i < n; i++){
        free(protocolo[i]);
    }
}