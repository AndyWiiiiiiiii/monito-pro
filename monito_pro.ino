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

// --- FUNCIONES DE APOYO (Definidas antes para evitar errores) ---

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
  fila = 0; // Sube a la fila de arriba
  actualizarPantalla("AAAAAA");
  delay(1000); 
  
  fila = 1; // Baja a la fila de abajo
  actualizarPantalla("auch");
}

void saludar() {
  actualizarPantalla("jeloouu");
  for(int i=0; i<3; i++) {
    dibujarCuerpo(1); delay(200);
    dibujarCuerpo(0); delay(200);
  }
}

// --- CONFIGURACIÓN PRINCIPAL ---

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

void loop() {
  // Botón Saludar
  if (digitalRead(btnSaluda) == LOW) {
    saludar();
  }

  // Botón Derecha
  if (digitalRead(btnDerecha) == LOW) {
    if (columna < 15) {
      columna++;
      actualizarPantalla("correle correle>");
      delay(100);
    }
  }

  // Botón Izquierda
  if (digitalRead(btnIzquierda) == LOW) {
    if (columna > 0) {
      columna--;
      actualizarPantalla("<correle correle");
      delay(100);
    }
  }

  // Botón Salto
  if (digitalRead(btnSalto) == LOW) {
    saltar();
  }
}