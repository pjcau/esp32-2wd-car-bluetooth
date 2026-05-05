#include <Arduino.h>

#define PIN_LED 8   // LED blu integrato sul Super Mini (attivo basso)

static inline void ledOn()  { digitalWrite(PIN_LED, LOW); }
static inline void ledOff() { digitalWrite(PIN_LED, HIGH); }

void setup() {
  pinMode(PIN_LED, OUTPUT);
  ledOff();
}

void loop() {
  // Tre blink lenti
  for (int i = 0; i < 3; i++) {
    ledOn();
    delay(500);
    ledOff();
    delay(500);
  }

  // Cinque blink veloci
  for (int i = 0; i < 5; i++) {
    ledOn();
    delay(100);
    ledOff();
    delay(100);
  }

  // Fade in / fade out (PWM, attivo basso → invertiamo il duty)
  for (int v = 0; v <= 255; v += 5) {
    analogWrite(PIN_LED, 255 - v);
    delay(15);
  }
  for (int v = 255; v >= 0; v -= 5) {
    analogWrite(PIN_LED, 255 - v);
    delay(15);
  }

  ledOff();
  delay(500);
}
