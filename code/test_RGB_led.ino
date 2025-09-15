#include <Adafruit_NeoPixel.h>

#define PIN_LED    21   // GPIO collegato al WS2812
#define NUM_PIXELS 1    // Solo 1 LED RGB integrato

Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();  // Inizializza il LED
  pixels.setBrightness(50);  // Da 0 a 255
}

void loop() {
  // Rosso
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
  delay(500);

  // Verde
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
  delay(500);

  // Blu
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay(500);

  // Spento
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(500);
}
