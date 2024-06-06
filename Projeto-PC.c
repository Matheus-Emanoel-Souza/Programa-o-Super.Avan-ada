#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define BOTAO_NAVE 8
#define BOTAO_CONF 9




int vogais_count = 0;

HANDLE hSerial;

void setup();
void loop();
void Menu();
void prepararParaPC();
void iniciarSerial();
void fecharSerial();
void enviarDados(const char *data);
void receberDados(char *buffer, int length);
void delay();

int main() {
    iniciarSerial();
    setup();
    while (1) {
        loop();
    }
    fecharSerial();
    return 0;
}

void delay(unsigned int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
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
}

void fecharSerial() {
    CloseHandle(hSerial);
}

void enviarDados(const char *data) {
    DWORD bytes_written;
    if (!WriteFile(hSerial, data, strlen(data), &bytes_written, NULL)) {
        printf("Erro ao gravar na porta serial\n");
    }
}

void receberDados(char *buffer, int length) {
    DWORD bytes_read;
    if (!ReadFile(hSerial, buffer, length, &bytes_read, NULL)) {
        printf("Erro ao ler a partir da porta serial\n");
    }
    buffer[bytes_read] = '\0';
}

void setup() {
    printf("Inicialização\n");
    
    Menu();
}

void loop() {
    delay(1000);
    Menu();
}

void Menu() {
    printf("-----BEM VINDO-----\n");
    printf("1-ENVIAR 2-RECEBER\n");

    int botaoNave = 0;
    int botaoConf = 0;


    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
       prepararParaPC();
    } else if (escolha == 2) {
        escrevermensagem();
    }

}

void prepararParaPC() {
    
    char mensagem[32];
    receberDados(mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);
    enviarDados(mensagem);
    printf("\n");
}

void escrevermensagem() {
    
 
    bool escolhaConcluida = false;

    while (!escolhaConcluida) {
       
        char escolha[16];
        scanf("%s", escolha);
      
        int vogais_count = 5;
        if (vogais_count == 5) {
            printf("FOI ENVIADO\n");
            printf("MSG: %s\n", escolha);
            enviarDados(escolha);
            escolhaConcluida = true;
            break;
        }
        
    }

    
}