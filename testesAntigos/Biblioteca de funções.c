#include "metodos.h"

No *CriaNoRecebido(mensage m)
{
    No *NovoNo = (No*)malloc(sizeof(No));
    NovoNo->msg = m;
    NovoNo->next = NULL;
    NovoNo->msg.Remet = Arduino;
    return NovoNo;
}
No *CriaNoEnviado(mensage m)
{
    No *NovoNo = (No*)malloc(sizeof(No));;
    NovoNo->msg = m;
    NovoNo->next = NULL;
    NovoNo->msg.Remet = pc;
    return NovoNo;
}

Lista cria_lista()
{
    Lista nova_lista={NULL, NULL,NULL,0};
    return nova_lista;
}

Lista criaHistorico(Lista Hist)
{
    Hist = cria_lista();
    return Hist;
}

void add_na_lista(No* no, Lista* lista)
{
if (lista->contador == 0)
{
    lista->primeiro = no;
}
else{
    lista->ultimo->next = no;        
}    
    lista->ultimo = no;
    lista->marcador = no;
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

void setup(Lista HistoricoMsg) {
    printf("Inicialização\n");
    Menu(HistoricoMsg);
}

void loop(Lista HistoricoMsg) {
    
    delay(1000);
    Menu(HistoricoMsg);
}

void Menu(Lista HistoricoMsg) {
    printf("-----BEM VINDO-----\n");
    printf("1-ENVIAR 2-RECEBER\n");

    int escolha;
    scanf("%d", &escolha);

    if (escolha == 1) {
       prepararParaPC(HistoricoMsg);
    } else if (escolha == 2) {
        escrevermensagem(HistoricoMsg);
    }
}
void escrevermensagem(Lista HistoricoMsg) {
    bool escolhaConcluida = false;

    while (!escolhaConcluida) {
        char escolha[16];
        scanf("%s", escolha);

        int vogais_count = 5;
        if (vogais_count == 5) {
            printf("FOI ENVIADO\n");
            printf("MSG: %s\n", escolha);
            mensage msg = {escolha, Arduino};
            No *Msg_Enviada = CriaNoEnviado(msg);
            add_na_lista(Msg_Enviada,&HistoricoMsg);
            enviarDados(escolha);
            escolhaConcluida = true;
            break;
        }
    }
}
void prepararParaPC(Lista HistoricoMsg) {
    char mensagem[32];
    receberDados(mensagem, 32);
    printf("Mensagem recebida: %s\n", mensagem);
    enviarDados(mensagem);
    mensage msg = {mensagem, pc};
    No *Msg_Enviada = CriaNoRecebido(msg);
    add_na_lista(Msg_Enviada,&HistoricoMsg);
    printf("\n");
}

void ImprimeMsg(mensage msg)
{
    printf("------------------------\n");
    if (msg.Remet == 0)
    {
        printf("Fonte: Arduino");
    }
    else{
        printf("Fonte: PC");
    }
    printf("Mensagem:%s",msg.m);
}
void ExibirHistórico(Lista lista)
{
    lista.marcador = lista.primeiro;
    while (lista.marcador != NULL)
    {
        ImprimeMsg(lista.marcador->msg);
        lista.marcador = lista.marcador->next;
    }
    
}

