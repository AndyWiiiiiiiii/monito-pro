#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int btnSaluda = 5, btnIzquierda = 4, btnSalto = 3, btnDerecha = 2;

int columna = 2, fila = 1; 
int cactusCol = 15, aveCol = 25; 
int puntos = 0;
bool juegoVivo = true, escenaFinal = false;

// Caracteres
byte mono0[8] = { B00000, B01010, B11111, B01110, B10100, B00100, B01010, B00000 };
byte mono1[8] = { B00000, B01010, B11111, B01110, B00101, B00100, B01010, B00000 };
byte cactus[8] = { B00100, B00101, B10101, B10101, B10110, B00100, B00100, B00100 };
byte ave[8] = { B00000, B00100, B10101, B01110, B10101, B00100, B00000, B00000 };

void setup() {
  pinMode(btnSaluda, INPUT_PULLUP);
  pinMode(btnIzquierda, INPUT_PULLUP);
  pinMode(btnSalto, INPUT_PULLUP);
  pinMode(btnDerecha, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.createChar(0, mono0);
  lcd.createChar(1, mono1);
  lcd.createChar(2, cactus);
  lcd.createChar(3, ave);
  
  lcd.print("¡DALE VRO!");
  delay(1000);
}

void loop() {
  if (juegoVivo && !escenaFinal) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("sc:"); lcd.print(puntos);
    
    // Dibujar personajes
    lcd.setCursor(columna, fila); lcd.write(byte(0)); 
    if (cactusCol < 16) { lcd.setCursor(cactusCol, 1); lcd.write(byte(2)); }
    if (aveCol < 16) { lcd.setCursor(aveCol, 0); lcd.write(byte(3)); }

    // --- MOVIMIENTO CON REGLA DE SEPARACIÓN (Mínimo 2 cuadros) ---
    static unsigned long tJuego = 0;
    if (millis() - tJuego > 120) { // Velocidad rápida
      cactusCol--;
      aveCol--;

      // Reset Cactus: Checa que el ave no esté cerca (columnas 13-15)
      if (cactusCol < 0) {
        if (aveCol < 13) { 
          cactusCol = 15;
          puntos++;
        } else { cactusCol = 17; } // Espera turno
      }

      // Reset Ave: Checa que el cactus no esté cerca
      if (aveCol < 0) {
        if (cactusCol < 13) {
          aveCol = 15;
          puntos++;
        } else { aveCol = 17; } // Espera turno
      }
      tJuego = millis();
    }

    if (puntos >= 15) escenaFinal = true;

    // Controles
    if (digitalRead(btnDerecha) == LOW && columna < 15) { columna++; delay(20); }
    if (digitalRead(btnIzquierda) == LOW && columna > 0) { columna--; delay(20); }
    if (digitalRead(btnSalto) == LOW && fila == 1) { fila = 0; } 
    else if (fila == 0) { 
      static int tAire = 0;
      tAire++; if (tAire > 3) { fila = 1; tAire = 0; }
    }

    // Colisión técnica
    if ((columna == cactusCol && fila == 1) || (columna == aveCol && fila == 0)) juegoVivo = false;
    
    delay(40);

  } else if (escenaFinal) {
    animacionVictoria();
  } else {
    lcd.clear();
    lcd.setCursor(3, 0); lcd.print("VALIO KOLA");
    lcd.setCursor(0, 1); lcd.print("B5: REINTENTAR");
    if (digitalRead(btnSaluda) == LOW) reiniciar();
    delay(200);
  }
}

void animacionVictoria() {
  lcd.clear();
  // Fila 0: Texto completo
  lcd.setCursor(0, 0);
  lcd.print("LA MERA CHISPA"); 
  
  // Fila 1: Texto y Monitos (Separados para no tocarse)
  lcd.setCursor(0, 1);
  lcd.print("DEL BOILER"); 
  
  // Ponemos a los monitos al final de la fila 1 (posiciones 14 y 15)
  // Así están en la misma fila que "DEL CALDO" pero sin encimarse
  int p1 = 14; 
  int p2 = 15;
  
  for(int i=0; i<10; i++) {
    // Frame 0
    lcd.setCursor(p1, 1); lcd.write(byte(0));
    lcd.setCursor(p2, 1); lcd.write(byte(0));
    delay(250);
    
    // Frame 1
    lcd.setCursor(p1, 1); lcd.write(byte(1));
    lcd.setCursor(p2, 1); lcd.write(byte(1));
    delay(250);
    
    if (digitalRead(btnSaluda) == LOW) { reiniciar(); return; }
  }
  
  lcd.clear();
  lcd.print("B5 PARA VOLVER");
  while(digitalRead(btnSaluda) == HIGH); 
  reiniciar();
}

void reiniciar() {
  juegoVivo = true; escenaFinal = false; puntos = 0;
  cactusCol = 15; aveCol = 25; columna = 2; fila = 1;
}