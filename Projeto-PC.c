#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define BOTAO_NAVE 8
#define BOTAO_CONF 9

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

HANDLE iniciar_serial() {
    HANDLE hSerial = CreateFile(
        "COM8",
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("Serial port doesn't exist!\n");
        }
        printf("Error initializing serial port\n");
        exit(EXIT_FAILURE);
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting device state\n");
        exit(EXIT_FAILURE);
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao definir parâmetros do dispositivo\n");
        exit(EXIT_FAILURE);
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Erro ao definir tempos limite\n");
        exit(EXIT_FAILURE);
    }
    
    return hSerial;
}

void fechar_serial(HANDLE hSerial) {
    CloseHandle(hSerial);
}

void enviar_dados(HANDLE hSerial, const char *data) {
    DWORD bytes_written;
    if (!WriteFile(hSerial, data, strlen(data), &bytes_written, NULL)) {
        printf("Erro ao gravar na porta serial\n");
        iniciar_serial();
    }
}

void receber_dados(HANDLE hSerial, char *buffer, int length) {
    DWORD bytes_read;
    if (!ReadFile(hSerial, buffer, length, &bytes_read, NULL)) {
        printf("Erro ao ler a partir da porta serial\n");
    }
    buffer[bytes_read] = '\0';
}

void delay_ms(unsigned int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

void setup() {
    printf("Inicialização\n");
}

void loop(Lista* historico_msg, HANDLE hSerial) {
    delay_ms(1000);
    menu(historico_msg, hSerial);
}

void menu(Lista* historico_msg, HANDLE hSerial) {
    printf("-----BEM VINDO-----\n");
    printf("1-ENVIAR 2-RECEBER\n");

    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
        preparar_para_pc(historico_msg, hSerial);
    } else if (escolha == 2) {
        escrever_mensagem(historico_msg, hSerial);
    }
}

void preparar_para_pc(Lista* historico_msg, HANDLE hSerial) {
    char mensagem[32];
    receber_dados(hSerial, mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);
    enviar_dados(hSerial, mensagem);
    Mensage msg = {.remet = Arduino};
    strncpy(msg.msg, mensagem, sizeof(msg.msg));
    No* msg_recebida = cria_no(msg, Arduino);
    add_na_lista(msg_recebida, historico_msg);
}

void escrever_mensagem(Lista* historico_msg, HANDLE hSerial) {
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
        enviar_dados(hSerial, escolha);
        escolha_concluida = true;
    }
}

int main() {
    HANDLE hSerial = iniciar_serial();
    setup();
    Lista historico_msg = cria_lista();
    while (1) {
        loop(&historico_msg, hSerial);
    }
    fechar_serial(hSerial);
    return 0;
}
