#include<LiquidCrystal.h>

LiquidCrystal lcd_1(2, 3, 4, 5, 6, 7);

char vogais[] = {'a', 'e', 'i', 'o', 'u'};
int ind = 0;
char vogais_selecionadas[5];
int vogais_count = 0;

#define BOTAO_NAVE 8
#define BOTAO_CONF 9

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2);

  pinMode(BOTAO_NAVE, INPUT);
  pinMode(BOTAO_CONF, INPUT);

  Menu();
}

void loop() {
  Menu();
}

void Menu() {
  lcd_1.setCursor(3, 0);
  lcd_1.print("BEM VINDO");
  lcd_1.setCursor(2, 1);
  lcd_1.print("1-PC 2-ARDU ");

  if (digitalRead(BOTAO_NAVE) == HIGH) {
    prepararParaPC();
  }
  if (digitalRead(BOTAO_CONF) == HIGH) {
    escolherVogais();
  }
}

void prepararParaPC() {
  lcd_1.clear();
  lcd_1.print("Esperando...");
  Serial.print("DIGITE SUA MENSAGEM");

  while (!Serial.available()) {
    delay(100);
  }

  String mensagem = Serial.readString();
  Serial.println(mensagem);

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("MSG RECEBIDA:");
  lcd_1.setCursor(3, 1);
  lcd_1.print(mensagem);
  delay(7500);
  lcd_1.clear();
  loop();
}

void escolherVogais() {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("ESCREVA");
  lcd_1.setCursor(0, 1);
  lcd_1.print(vogais[ind]);
  delay(1000);

  bool escolhaConcluida = false;

  while (!escolhaConcluida) {
    if (digitalRead(BOTAO_NAVE) == HIGH) {
      ind = (ind + 1) % 5;
      lcd_1.setCursor(0, 1);
      lcd_1.print(vogais[ind]);
      delay(1000);
    }

    if (digitalRead(BOTAO_CONF) == HIGH) {
      vogais_selecionadas[vogais_count] = vogais[ind];
      vogais_count++;

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
        loop();
        escolhaConcluida = true;
      }

      while (digitalRead(BOTAO_CONF) == HIGH) {
        delay(50);
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    vogais_selecionadas[i] = '\0';
    Serial.print(vogais_selecionadas[i]);
  }
  vogais_count = 0;
}
