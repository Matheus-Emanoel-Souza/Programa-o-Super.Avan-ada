#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define BOTAO_NAVE 8
#define BOTAO_CONF 9

typedef enum {
    Arduino = 0,
    pc = 1
    }Remetente;

typedef struct mensage
{
    char m[36];
    Remetente Remet;
    //bool EnviadoPeloArduino;   
} mensage;

typedef struct No 
{
    mensage msg;             
    struct No* next;    
} No;
typedef struct Lista
{
    No*primeiro;
    No*ultimo;
    No*marcador;
    int contador;
}Lista;

No *CriaNoEnviado(mensage m);
No *CriaNoRecebido(mensage m);
void add_na_lista(No* no, Lista* lista);
HANDLE hSerial;

void setup();
void loop();
void Menu();
void prepararParaPC();
void iniciarSerial();
void fecharSerial();
void enviarDados(const char *data);
void receberDados(char *buffer, int length);
void delay(unsigned int milliseconds);  // Ajustado para definir o tipo de argumento
