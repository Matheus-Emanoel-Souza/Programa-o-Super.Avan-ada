# include<LiquidCrystal.h>

#define BOTAO_1 2
#define BOTAO_2 3
//AQUI EU DEFINO QUAIS PINOS CADA BOTÃO ESTÁ LOCALIZADO.

int contador_botao_1 = 0;
int contador_botao_2 = 0;
//AQUI EU COLOCO UM CONTADOR PARA CADA BOTÃO, A IDEIA É UTILIZAR A MATEMATICA DE LAMPADA.

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//DEFINI OS PINOS QUE O LCD ESTÁ LOCALIZADO.

void setup() 
{
    lcd.begin(16,2);//AQUI EU CHAMO A FUNÇÃO DA BIBLIOTECA(CRISTALlIQUID) E PASSO O TAMANHO DA TELA DE LCD 16 POR 2
    pinMode(BOTAO_1, INPUT);
    pinMode(BOTAO_2, INPUT);
    lcd.setCursor(0,0);//TESTAR RETIRAR ESTE ARGUMENTO.
    lcd.print("Contador 1: 0");
    lcd.setCursor(0,1);
    lcd.print("Contador 2: 0");
}

void loop
{
  if (digitalRead(BOTAO_1) == HIGH) 
  {
    delay(50);
    contador_botao_1++;
    atualizarLCD();
  }

  if (digitalRead(BOTAO_2) == HIGH) 
  {
    delay(50);
    contador_botao_2++;
    atualizarLCD();
  }
}

void atualizarLCD() {
  lcd.clear();
  // Exibe os contadores atualizados no LCD
  lcd.print("Contador 1: ");
  lcd.print(contador_botao_1);
  lcd.setCursor(0, 1);
  lcd.print("Contador 2: ");
  lcd.print(contador_botao_2);
}
