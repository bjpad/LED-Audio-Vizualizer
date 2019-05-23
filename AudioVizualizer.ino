
#include <FastLED.h>

#define NumLEDS 300
#define DataPin 6

void setup() {
  Serial.begin(3600);
  
  //Telling the library there is a strand of LEDs on pin 6
  //Creating array "leds"
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NumLEDS);
  
}

void TestLEDs() {
  for (int i = 1; i < NumLEDS; i++) {
    leds[i] = CRGB(100, 100, 100);
    leds[i - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5);
  }
  
}
