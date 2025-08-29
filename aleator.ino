#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Config pini ---
const int inreleu  = 2;
const int inled    = 4;
const int inreleu2 = 8;
const int inled2   = 9;
const int buton    = 6;
const int buzzer   = 10;

// --- Timings ---
const unsigned long TIMP_LED_ON  = 1000;
const unsigned long TIMP_PAUZA   = 500;
const unsigned long DEBOUNCE_MS  = 30;
const unsigned long PAUZA_FINALA = 60000;

// --- Scor ---
int scor = 0;

// --- Debounce / edge detect ---
int lastReading       = HIGH;
int buttonStableState = HIGH;
unsigned long lastDebounceTime = 0;

bool buttonPressedEvent() {
  int reading = digitalRead(buton);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != buttonStableState) {
      buttonStableState = reading;
      if (buttonStableState == LOW) {
        lastReading = reading;
        return true;
      }
    }
  }
  lastReading = reading;
  return false;
}

void setup() {
  pinMode(inreleu, OUTPUT);
  pinMode(inled, OUTPUT);
  pinMode(inreleu2, OUTPUT);
  pinMode(inled2, OUTPUT);
  pinMode(buton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  randomSeed(analogRead(A0));

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Scor: 0");
  lcd.setCursor(0,1);
  lcd.print("Joc start!");
}

void loop() {
  int alegere = random(2);

  if (alegere == 0) {
    rundaCuLed(inled, inreleu);
  } else {
    rundaCuLed(inled2, inreleu2);
  }

  // Pauză = LED-uri stinse → apăsare greșită
  unsigned long start = millis();
  while (millis() - start < TIMP_PAUZA) {
    if (buttonPressedEvent()) {
      if (scor > 0) scor--;
      Serial.print("Gresit (-1). Scor: ");
      Serial.println(scor);

      lcd.setCursor(0,0);
      lcd.print("Scor: ");
      lcd.print(scor);
      lcd.print("    "); // șterge restul liniei
      lcd.setCursor(0,1);
      lcd.print("Gresit!        ");
    }
  }

  if (scor >= 10) {
    finalDeJoc();
    scor = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scor: 0");
    lcd.setCursor(0,1);
    lcd.print("Joc restart!");
  }
}

void rundaCuLed(int ledPin, int releuPin) {
  digitalWrite(ledPin, HIGH);
  digitalWrite(releuPin, HIGH);

  bool aMarcatInRunda = false;
  unsigned long start = millis();
  while (millis() - start < TIMP_LED_ON) {
    if (!aMarcatInRunda && buttonPressedEvent()) {
      scor++;
      aMarcatInRunda = true;
      Serial.print("Corect (+1). Scor: ");
      Serial.println(scor);

      lcd.setCursor(0,0);
      lcd.print("Scor: ");
      lcd.print(scor);
      lcd.print("    ");
      lcd.setCursor(0,1);
      lcd.print("Corect!        ");
    }
  }

  digitalWrite(ledPin, LOW);
  digitalWrite(releuPin, LOW);
}

void finalDeJoc() {
  Serial.println("Stop!");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("STOP joc!");
  lcd.setCursor(0,1);
  lcd.print("Felicitari!");

  digitalWrite(inled, HIGH);
  digitalWrite(inreleu, HIGH);
  digitalWrite(inled2, HIGH);
  digitalWrite(inreleu2, HIGH);

  digitalWrite(buzzer, HIGH);
  delay(3000);
  digitalWrite(buzzer, LOW);

  delay(PAUZA_FINALA);

  digitalWrite(inled, LOW);
  digitalWrite(inreleu, LOW);
  digitalWrite(inled2, LOW);
  digitalWrite(inreleu2, LOW);
}
