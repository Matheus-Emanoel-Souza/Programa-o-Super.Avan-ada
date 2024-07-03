#include <LiquidCrystal.h>

LiquidCrystal lcd_1(2, 3, 4, 5, 6, 7);

#define BOTAO_NAVE 8
#define BOTAO_CONF 9

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2); // Inicialização do LCD com 16 colunas e 2 linhas

  pinMode(BOTAO_NAVE, INPUT); // Define o pino do botão de navegação como entrada
  pinMode(BOTAO_CONF, INPUT); // Define o pino do botão de confirmação como entrada

  Menu(0);
}

void loop() {
  Menu(0);
}

void Menu(int ind) {
  char vogais[] = {'a', 'e', 'i', 'o', 'u'};

  lcd_1.setCursor(3, 0); // Posiciona o cursor na primeira linha, quarta coluna
  lcd_1.print("BEM VINDO"); // Imprime "BEM VINDO" na primeira linha
  lcd_1.setCursor(2, 1); // Posiciona o cursor na segunda linha, terceira coluna
  lcd_1.print("1-PC 2-ARDU "); // Imprime "1-PC 2-ARDU" na segunda linha
  
  if (digitalRead(BOTAO_NAVE) == HIGH) {
    prepararParaPC();
  }
  if (digitalRead(BOTAO_CONF) == HIGH) {
    escolherVogais(0);
  }
}

void prepararParaPC() {
  lcd_1.clear();
  lcd_1.print("Esperando...");
  delay(500); // Adiciona uma pequena pausa para garantir que a mensagem seja exibida

  String mensagem = readSerialMessage();
  
  lcd_1.clear();
  lcd_1.print(mensagem);
  delay(7500);
  lcd_1.clear();
}

String readSerialMessage() {
  String message = "";
  while (!Serial.available()) {
    delay(100); // Aguarda até que haja dados disponíveis
  }
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      break; // Termina a leitura quando um caractere de nova linha é recebido
    }
    message += c; // Adiciona o caractere à mensagem
  }
  return message;
}

void escolherVogais(int ind) {
  char vogais[] = {'a', 'e', 'i', 'o', 'u'};
  char vogais_selecionadas[5];
  int vogais_count = 0;
  bool escolhaConcluida = false;

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("ESCREVA");
  lcd_1.setCursor(0, 1);
  lcd_1.print(vogais[ind]);
  delay(1000);

  while (!escolhaConcluida) {
    if (digitalRead(BOTAO_NAVE) == HIGH) {
      ind = (ind + 1) % 5;
      lcd_1.setCursor(vogais_count, 1);
      lcd_1.print(vogais[ind]);
      delay(1000); // debounce
    }
      
    if (digitalRead(BOTAO_CONF) == HIGH) {
      vogais_selecionadas[vogais_count] = vogais[ind];
      vogais_count++;
      lcd_1.setCursor(vogais_count, 1);
      lcd_1.print(vogais[ind]);
      
      if (vogais_count == 5) {
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("FOI ENVIADO");
        lcd_1.setCursor(0, 1);
        lcd_1.print("MSG: ");
  
        Serial.println(" ");
        for (int i = 0; i < 5; i++) {
          lcd_1.print(vogais_selecionadas[i]);
          Serial.print(vogais_selecionadas[i]);
        }
        delay(7500);
        lcd_1.clear();
        escolhaConcluida = true;
      }
      
      while (digitalRead(BOTAO_CONF) == HIGH) {
        delay(100);
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    vogais_selecionadas[i] = '\0';
  } 
  vogais_count = 0;
}