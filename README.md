#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   
//TESTE DE TELA//


typedef enum tipo
{
    MULT,
    TEXT
}TIPOTELA;

typedef struct tela
{
    char titulo[40];
    char info[45];
    int opcao;
    TIPOTELA tipo_tela;
}TELA;

TELA Tela_1[3] =
{
    {"          ---MENU---", " ( )PC e ( )ARDU", 0, MULT},
    {"          ---ESCREVA SUA MENSAGEM---", 0},
    {"          ---TELA 3---", "1- p NEMU, 2- p VOLTAR e 3 sair", 0, MULT},
};

TELA Tela_2[3] =
{
    {"          ---AGUARDANDO---", 0},
    {"          ---MESAGEM RECEBIDA---", 0},
};
void imprimirTela_1(int ntela)
{
    system("cls");
    printf("%s\n", Tela_1[ntela].titulo);
    printf("%s\n", Tela_1[ntela].info);
}

void imprimirTela_2(int ntela)
{
    system("cls");
    printf("%s\n", Tela_2[ntela].titulo);


}

int main()
{
    int estado = 0;
    int escolha = 0;

while(estado != 100){
    switch (estado)
    {
    case 0:
        imprimirTela_1(0);
        scanf("%i", &escolha);
        if(escolha == 1)
        {
            estado = 1;
            imprimirTela_2(0);      
        }
        else if(escolha == 2)
        {
            estado = 2;
            imprimirTela_1(1);
        }
        escolha = 0;
        break;
    default:
        break;
    }
}

}
