#include <LiquidCrystal.h>

// Definição dos tipos de tela
typedef enum tipo {
    MULT,
    TEXT
} TIPOTELA;

// Definição da estrutura de tela
typedef struct tela {
    char titulo[40];
    char info[45];
    int opcao;
    TIPOTELA tipo_tela;
} TELA;

// Definição das telas Tela_1 e Tela_2
TELA Tela_1[3] = {
    {"          ---MENU---", " ( )PC e ( )ARDU", 0, MULT},
    {"          ---ESCREVA SUA MENSAGEM---", "", 0, TEXT},
    {"          ---TELA 3---", "1- p NEMU, 2- p VOLTAR e 3 sair", 0, MULT},
};

TELA Tela_2[2] = {
    {"          ---AGUARDANDO---", "", 0, TEXT},
    {"          ---MENSAGEM RECEBIDA---", "", 0, TEXT},
};

// Inicialização do objeto LiquidCrystal
LiquidCrystal lcd_1(2, 3, 4, 5, 6, 7);

bool status_b1 = false;
bool status_b2 = false;

void imprimirTela_1(int ntela) {

  lcd_1.setCursor(0, 0); // Posiciona o cursor na primeira linha, primeira coluna
  lcd_1.print("BEM VINDO"); // Imprime "BEM VINDO" na primeira linha
 

  lcd_1.clear(); // Limpa o display LCD
  lcd_1.setCursor(0, 0); // Posiciona o cursor na primeira linha, primeira coluna
  lcd_1.print(Tela_1[ntela].titulo); // Imprime o título da tela
  lcd_1.setCursor(0, 1); // Posiciona o cursor na segunda linha, primeira coluna
  lcd_1.print(Tela_1[ntela].info); // Imprime a informação da tela
}

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2); // Inicialização do LCD com 16 colunas e 2 linhas

  pinMode(8, INPUT); // Define o pino do botão 1 como entrada
  pinMode(9, INPUT); // Define o pino do botão 2 como entrada

}



int main() {
  status_b1 = digitalRead(8);
  status_b2 = digitalRead(9);

  lcd_1.setCursor(5, 0); // Posiciona o cursor na primeira linha, primeira coluna
  lcd_1.print("BEM VINDO"); // Imprime "BEM VINDO" na primeira linha
  lcd_1.setCursor(1, 2); // Posiciona o cursor na primeira linha, primeira coluna
  lcd_1.print("(1)INICIAR"); // Imprime "BEM VINDO" na primeira linha
	
  if (status_b1 != 0) { // Verifica se o botão 1 foi pressionado
     lcd_1.clear();     
		imprimirTela_1(0); // Imprime a tela 1
  }
}