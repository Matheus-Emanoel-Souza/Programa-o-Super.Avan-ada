#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Estruturas
typedef enum {
    Arduino,
    PC
} Remetente;

typedef struct {
    char msg[36];
    Remetente remet;
} Mensage;

typedef struct No {
    Mensage msg;
    struct No* next;
} No;

typedef struct {
    No* primeiro;
    No* ultimo;
    int contador;
} Lista;

// Protótipos das funções
Lista cria_lista();
No* cria_no(Mensage msg, Remetente remet);
void add_na_lista(No* no, Lista* lista);
void imprime_msg(Mensage msg);
void exibir_historico(Lista lista);
// Funções de comunicação serial comentadas
// HANDLE iniciar_serial();
// void fechar_serial(HANDLE hSerial);
// void enviar_dados(HANDLE hSerial, const char *data);
// void receber_dados(HANDLE hSerial, char *buffer, int length);

void delay_ms(unsigned int milliseconds);
void setup();
void loop(Lista* historico_msg, int* continuar_execucao);
void menu(Lista* historico_msg, int* continuar_execucao);
void preparar_para_pc(Lista* historico_msg);
void escrever_mensagem(Lista* historico_msg);

// Função principal
int main() {
    setup();
    Lista historico_msg = cria_lista();
    int continuar_execucao = 1;
    
    while (continuar_execucao) {
        loop(&historico_msg, &continuar_execucao);
    }
    
    exibir_historico(historico_msg);
    
    return 0;
}

// Implementação das funções
Lista cria_lista() {
    Lista nova_lista = {NULL, NULL, 0};
    return nova_lista;
}

No* cria_no(Mensage msg, Remetente remet) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    novo_no->msg = msg;
    novo_no->msg.remet = remet;
    novo_no->next = NULL;
    return novo_no;
}

void add_na_lista(No* no, Lista* lista) {
    if (lista->contador == 0) {
        lista->primeiro = no;
        lista->ultimo = no;
    } else {
        lista->ultimo->next = no;
        lista->ultimo = no;
    }
    lista->contador++;
}

void imprime_msg(Mensage msg) {
    printf("------------------------\n");
    printf("Fonte: %s\n", msg.remet == Arduino ? "Arduino" : "PC");
    printf("Mensagem: %s\n", msg.msg);
}

void exibir_historico(Lista lista) {
    No* marcador = lista.primeiro;
    while (marcador != NULL) {
        imprime_msg(marcador->msg);
        marcador = marcador->next;
    }
}

// Funções de comunicação serial comentadas
/*
HANDLE iniciar_serial() {
    // Código para iniciar a comunicação serial
}

void fechar_serial(HANDLE hSerial) {
    // Código para fechar a comunicação serial
}

void enviar_dados(HANDLE hSerial, const char *data) {
    // Código para enviar dados pela serial
}

void receber_dados(HANDLE hSerial, char *buffer, int length) {
    // Código para receber dados pela serial
}
*/

void delay_ms(unsigned int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

void setup() {
    printf("Inicialização\n");
}

void loop(Lista* historico_msg, int* continuar_execucao) {
    delay_ms(1000);
    menu(historico_msg, continuar_execucao);
}

void menu(Lista* historico_msg, int* continuar_execucao) {
    printf("-----BEM VINDO-----\n");
    printf("0-Sair 1-ENVIAR 2-RECEBER\n");

    int escolha;
    scanf("%d", &escolha);
    
    if (escolha == 0) {
        *continuar_execucao = 0; // Sinaliza para sair do loop
        return;
    }  
    
    if (escolha == 1) {
        preparar_para_pc(historico_msg);
    } else if (escolha == 2) {
        escrever_mensagem(historico_msg);
    }
}

void preparar_para_pc(Lista* historico_msg) {
    char mensagem[32];
    // receber_dados(hSerial, mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);
    // enviar_dados(hSerial, mensagem);
    Mensage msg = {.remet = Arduino};
    strncpy(msg.msg, mensagem, sizeof(msg.msg));
    No* msg_recebida = cria_no(msg, Arduino);
    add_na_lista(msg_recebida, historico_msg);
}

void escrever_mensagem(Lista* historico_msg) {
    bool escolha_concluida = false;

    while (!escolha_concluida) {
        char escolha[36];
        scanf("%s", escolha);

        printf("FOI ENVIADO\n");
        printf("MSG: %s\n", escolha);
        Mensage msg = {.remet = PC};
        strncpy(msg.msg, escolha, sizeof(msg.msg));
        No* msg_enviada = cria_no(msg, PC);
        add_na_lista(msg_enviada, historico_msg);
        // enviar_dados(hSerial, escolha);
        escolha_concluida = true;
    }
}
