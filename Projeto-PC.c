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
    No* marcador;
    int contador;
} Lista;

HANDLE hSerial;

Lista cria_lista();
No* cria_no(Mensage msg, Remetente remet);
void add_na_lista(No* no, Lista* lista);
void imprime_msg(Mensage msg);
void exibir_historico(Lista *lista);
void delay(unsigned int milliseconds);
void iniciarSerial();
void fecharSerial();
void enviarDados(const char *data);
void receberDados(char *buffer, int length);
void setup();
void loop();
void Menu();
void prepararParaPC(Lista *Exibir_historicoMSG);
void escrevermensagem(Lista *Exibir_historicoMSG);
//void limparSerialMonitor();

void limparEntradaSerial() {
    char buffer[256];
    DWORD bytes_read;

    // Continue lendo enquanto houver dados na entrada serial
    while (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytes_read, NULL) && bytes_read > 0) {
        // Fazer nada com os dados lidos
    }
}

void limparSerialMonitor() {
    system("cls");
    printf("Monitor Serial Limpo\n");
}

void delay(unsigned int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}

void iniciarSerial() {
    hSerial = CreateFile(
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
            printf("A porta serial não existe!\n");
        } else {
            printf("Erro ao inicializar a porta serial\n");
        }
        exit(EXIT_FAILURE);
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao obter o estado do dispositivo\n");
        exit(EXIT_FAILURE);
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao definir os parâmetros do dispositivo\n");
        exit(EXIT_FAILURE);
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Erro ao definir os tempos limite\n");
        exit(EXIT_FAILURE);
    }
}

void fecharSerial() {
    CloseHandle(hSerial);
}

void enviarDados(const char *data) {
    DWORD bytes_written;
    if (!WriteFile(hSerial, data, strlen(data), &bytes_written, NULL)) {
        printf("Erro ao escrever na porta serial\n");
    }
}

void receberDados(char *buffer, int length) {
    DWORD bytes_read;
    
    if (!ReadFile(hSerial, buffer, length, &bytes_read, NULL)) {
        printf("Erro ao ler a partir da porta serial\n");
    }
    
    
    buffer[bytes_read] = '\0';
}

void setup(Lista *Exibir_historicoMSG) {
    printf("Bem vindo!!!\n");
    Menu(Exibir_historicoMSG);
}
    
void Menu(Lista *Exibir_historicoMSG) {
    limparEntradaSerial();
    limparSerialMonitor();
    printf("-----GRUPO BAO-----\n");
    printf("1-ENVIAR 2-RECEBER 3-HISTORICO\n");

    int escolha;
    scanf("%d", &escolha);
    
    switch (escolha)
    {
    case 1:
        escrevermensagem(Exibir_historicoMSG);
        break;
    case 2:
        prepararParaPC(Exibir_historicoMSG);
        break;
    case 3:
        printf("Historico de mensagens:\n");
        exibir_historico(Exibir_historicoMSG);
        break;
    
    default:
    printf("Numero invalido.\n");
        break;
    }

}

void prepararParaPC(Lista *Exibir_historicoMSG) {

    char mensagem[32];
    receberDados(mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);

    
    // Criar nó e adicionar à lista
    Mensage msg;
    strcpy(msg.msg, mensagem);
    msg.remet = Arduino;
    No* novo_no = cria_no(msg, Arduino);
    add_na_lista(novo_no,Exibir_historicoMSG);
    enviarDados(mensagem);
    
    printf("\n");
}

void escrevermensagem(Lista *Exibir_historicoMSG) {
    bool escolhaConcluida = false;

    while (!escolhaConcluida) {
        char escolha[36];
        
        // Lê uma linha de entrada, incluindo espaços
        printf("Digite sua mensagem: ");
        scanf(" %[^\n]", escolha);

        if (strlen(escolha) > 0) {
            printf("FOI ENVIADO\n");
            printf("MSG: %s\n", escolha);

            // Criar nó e adicionar à lista
            Mensage m;
            strcpy(m.msg, escolha);
            m.remet = PC;
            No* novo_no = cria_no(m, PC);
            add_na_lista(novo_no, Exibir_historicoMSG);
            enviarDados(escolha);

            escolhaConcluida = true;
        }
    }
}

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
    } else {
        lista->ultimo->next = no;
    }
    lista->marcador=no;
    lista->ultimo = no;
    lista->contador++;
}

void imprime_msg(Mensage msg) {
    printf("------------------------\n");
    printf("Fonte: %s\n", msg.remet == Arduino ? "Arduino" : "PC");
    printf("Mensagem: %s\n", msg.msg);
}

void exibir_historico(Lista *lista) {
    lista->marcador = lista->primeiro;
    while (lista->marcador != NULL) {
        imprime_msg(lista->marcador->msg);
        lista->marcador = lista->marcador->next;
    }
}

int main() {
    Lista Exibir_historicoMSG = cria_lista();
    iniciarSerial();
    setup(&Exibir_historicoMSG);
    bool continua = true;

    while (continua)
    {
        delay(1000);
        Menu(&Exibir_historicoMSG);
    }
    
    fecharSerial();
    return 0;
}