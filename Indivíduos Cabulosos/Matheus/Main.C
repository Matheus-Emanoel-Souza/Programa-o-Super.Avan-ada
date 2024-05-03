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
{"ESCREVA SUA MENSANGE",0,TEXT},
{"TELA 3", "1 p/ menu, 2 p/ VOLTAR, 3 Sair",0,MULT},
};

TELA tela_2[3]=
{

};

TELA tela_3[3]=
{

};

//aperta o otão 1 vez para selecionar e 2 para confirmar a opção!!!
