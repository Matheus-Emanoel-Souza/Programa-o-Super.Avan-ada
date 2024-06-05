#include <stdio.h>
#include <windows.h>

#define TAMANHO_CODIGO 5

void lerCodigo(HANDLE hSerial) {
    char buffer[TAMANHO_CODIGO] = {0};
    DWORD bytesRead;

    if (ReadFile(hSerial, buffer, TAMANHO_CODIGO, &bytesRead, NULL)) {
        printf("Código recebido: %s\n", buffer);
    } else {
        printf("Erro ao ler o código.\n");
    }
}

void escreverCodigo(HANDLE hSerial) {
    char mensagem[TAMANHO_CODIGO + 1] = {0};
    printf("Digite uma mensagem com no máximo 5 caracteres: ");
    scanf("%5s", mensagem);

    DWORD bytesWritten;
    if (!WriteFile(hSerial, mensagem, TAMANHO_CODIGO, &bytesWritten, NULL)) {
        printf("Erro ao escrever na porta serial.\n");
    }
}

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };

    hSerial = CreateFile("\\\\.\\COM6", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Erro ao abrir a porta serial COM6.\n");
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams) || !SetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro ao configurar parâmetros da porta serial.\n");
        CloseHandle(hSerial);
        return 1;
    }

    while (1) {
        escreverCodigo(hSerial);
        lerCodigo(hSerial);
    }

    CloseHandle(hSerial);
    return 0;
}
