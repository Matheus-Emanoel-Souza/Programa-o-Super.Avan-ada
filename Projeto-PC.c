#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define BOTAO_NAVE 8
#define BOTAO_CONF 9

char vogais[] = {'a', 'e', 'i', 'o', 'u'};
int ind = 0;
char vogais_selecionadas[5];
int vogais_count = 0;

HANDLE hSerial;

void setup();
void loop();
void Menu();
void prepararParaPC();
void escolherVogais();
void iniciarSerial();
void fecharSerial();
void enviarDados(const char *data);
void receberDados(char *buffer, int length);

int main() {
    iniciarSerial();
    setup();
    while (1) {
        loop();
    }
    fecharSerial();
    return 0;
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
        printf("Error setting device parameters\n");
        exit(EXIT_FAILURE);
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting timeouts\n");
        exit(EXIT_FAILURE);
    }
}

void fecharSerial() {
    CloseHandle(hSerial);
}

void enviarDados(const char *data) {
    DWORD bytes_written;
    if (!WriteFile(hSerial, data, strlen(data), &bytes_written, NULL)) {
        printf("Error writing to serial port\n");
    }
}

void receberDados(char *buffer, int length) {
    DWORD bytes_read;
    if (!ReadFile(hSerial, buffer, length, &bytes_read, NULL)) {
        printf("Error reading from serial port\n");
    }
    buffer[bytes_read] = '\0';
}

void setup() {
    printf("Inicialização\n");
    Menu();
}

void loop() {
    Menu();
}

void Menu() {
    printf("BEM VINDO\n");
    printf("1-PC 2-ARDU\n");

    int botaoNave = 0;
    int botaoConf = 0;

  //  printf("Pressione 1 para BOTAO_NAVE ou 2 para BOTAO_CONF: ");
    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
        botaoNave = 1;
    } else if (escolha == 2) {
        botaoConf = 1;
    }

    if (botaoNave) {
        prepararParaPC();
    }
    if (botaoConf) {
        escolherVogais();
    }
}

void prepararParaPC() {
    printf("Esperando...\n");

    char mensagem[32];
    receberDados(mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);
    enviarDados(mensagem);
    printf("\n");
}

void escolherVogais() {
    printf("ESCREVA: %c\n", vogais[ind]);

    bool escolhaConcluida = false;

    while (!escolhaConcluida) {
        // int botaoNave = 0;
        // int botaoConf = 0;

        // printf("Pressione 1 para BOTAO_NAVE ou 2 para BOTAO_CONF: ");
        // int escolha;
        char escolha[16];
        scanf("%s", escolha);
        // // printf("Msg enviada: %s", escolha);
        // // enviarDados(escolha);
        // // escolhaConcluida = true;
        // if (escolha == 1) {
        //     botaoNave = 1;
        // } else if (escolha == 2) {
        //     botaoConf = 1;
        // }

        // if (botaoNave) {
        //     ind = (ind + 1) % 5;
        //     printf("ESCREVA: %c\n", vogais[ind]);
        // }

        // if (botaoConf) {
        //     vogais_selecionadas[vogais_count] = vogais[ind];
        //     vogais_count++;
        //     printf("Vogais Selecionadas: %s\n", vogais_selecionadas);
        vogais_count = 5;
        if (vogais_count == 5) {
            printf("FOI ENVIADO\n");
            printf("MSG: %s\n", vogais_selecionadas);
            enviarDados(escolha);
            escolhaConcluida = true;
            break;
        }
        // }
    }

    for (int i = 0; i < 5; i++) {
        vogais_selecionadas[i] = '\0';
    }
    vogais_count = 0;
}