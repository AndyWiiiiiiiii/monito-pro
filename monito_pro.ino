#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int btnSaluda = 5;
const int btnDerecha = 2;
const int btnIzquierda = 4;
const int btnSalto = 3; 

int columna = 7; 
int fila = 1; 

// Caracteres del monito
byte mono0[8] = { B00000, B01010, B11111, B01110, B10100, B00100, B01010, B00000 };
byte mono1[8] = { B00000, B01010, B11111, B01110, B00101, B00100, B01010, B00000 };

// las funciones definidias, asi no tenemos super epikos errores

void actualizarPantalla(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  lcd.setCursor(columna, fila);
  lcd.write(byte(0));
}

void dibujarCuerpo(int frame) {
  lcd.setCursor(columna, fila);
  lcd.write(byte(frame));
}

void saltar() {
  fila = 0; // Sube 
  actualizarPantalla("AAAAAA");
  delay(1000); 
  
  fila = 1; // Baja a la fila de abajo, ps nimod que a la de arriba broski
  actualizarPantalla("auch");
}

void saludar() {
  actualizarPantalla("jeloouu");
  for(int i=0; i<3; i++) {
    dibujarCuerpo(1); delay(200);
    dibujarCuerpo(0); delay(200);
  }
}

// aqui va lo principal

void setup() {
  pinMode(btnSaluda, INPUT_PULLUP);
  pinMode(btnDerecha, INPUT_PULLUP);
  pinMode(btnIzquierda, INPUT_PULLUP);
  pinMode(btnSalto, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0, mono0);
  lcd.createChar(1, mono1);
  
  actualizarPantalla("monito pro");
}
//los botones 
void loop() {
  // Botón para Saludar
  if (digitalRead(btnSaluda) == LOW) {
    saludar();
  }

  // Corre a la derecha
  if (digitalRead(btnDerecha) == LOW) {
    if (columna < 15) {
      columna++;
      actualizarPantalla("correle correle>");
      delay(100);
    }
  }

  // Corre a la izquierda
  if (digitalRead(btnIzquierda) == LOW) {
    if (columna > 0) {
      columna--;
      actualizarPantalla("<correle correle");
      delay(100);
    }
  }

  // Salta así como inmigrante a la frontera
  if (digitalRead(btnSalto) == LOW) {
    saltar();
  }
}
