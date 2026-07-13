#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pulsePin = A0;
const int threshold = 550;

bool pulseDetected = false;

unsigned long lastBeatTime = 0;
float bpm = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Heart Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {

  int signal = analogRead(pulsePin);

  // Beat detection
  if (signal > threshold && !pulseDetected) {

    pulseDetected = true;

    unsigned long currentBeat = millis();

    if (lastBeatTime > 0) {

      unsigned long interval = currentBeat - lastBeatTime;

      bpm = 60000.0 / interval;

      Serial.print("BPM: ");
      Serial.println(bpm);

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("BPM:");
      lcd.print((int)bpm);

      lcd.setCursor(0, 1);

      if (bpm < 60) {
        lcd.print("Bradycardia");
      }
      else if (bpm > 100) {
        lcd.print("Tachycardia");
      }
      else {
        lcd.print("Normal");
      }
    }

    lastBeatTime = currentBeat;
  }

  if (signal < threshold) {
    pulseDetected = false;
  }

  delay(5);
}