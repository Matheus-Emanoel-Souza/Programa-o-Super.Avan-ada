#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef enum tipo{
    MULT,TEXT
}TIPOTELA;

typedef struct tela{
    char titulo[40];
    char info[45];
    int opcao;
    TIPOTELA tipo;
}TELA;
//Aqui estou tentando copiar a lógica de "Classe" que se utiliza em C#. A classe apresentará essas seguintes informações -> um titulo, uma informação e o numero da opção.

TELA tela_1[3]=
{
{"--Menu\n","( )PC e ( )ARDUINO",0,MULT},
};

TELA tela_2[3]=
{
{"Escolha uma Opção:\n","( )ENVIAR MENSAGEM  ( )RECEBER MENSAGEM",0,MULT}
};

TELA tela_3[3]=
{
{"ENVIAR MENSAGEM:\n:","1- P/ Escrever, 2-P/ Confirmar",0,MULT}
};

TELA tela_4[3]=
{
{"ler mensagem","Mensangem:",0,TEXT}
};

void main()
{
  
}
//aperta o otão 1 vez para selecionar e 2 para confirmar a opção!!!
