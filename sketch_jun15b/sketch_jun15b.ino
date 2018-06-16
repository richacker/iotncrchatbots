#include <Adafruit_NeoPixel.h>

#define PIN 21
#define LED_COUNT 1

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_RGB + NEO_KHZ400);



void setup()
{
  leds.begin();
  leds.show();
  
}

void loop()
{
  colorWipe(leds.Color(153, 27, 226), 40);
  delay(1000);
  colorWipe(leds.Color(0, 0, 0), 40);
  delay(1000);
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<leds.numPixels(); i++) {
    leds.setPixelColor(i, c);
    leds.show();
    delay(wait);
  }
}
