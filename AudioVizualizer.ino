
#include <FastLED.h>

#define NumLEDS 300
#define DataPin 6
int LoopColorChange = 255/NumLEDS;

void setup() {
  Serial.begin(3600);
  
  //Telling the library there is a strand of LEDs on pin 6
  //Creating array "leds"
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NumLEDS);
  TestLEDS();
  
  
}
//////////////////////////////////////////////////////////////////
void TestLEDS() {
  for (int i = 0; i < NumLEDS; i++) {
    leds[i] = CRGB(100, 100, i*LoopColorChange);
    leds[i - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5);
  }
  for (int i = NumLEDS; i > 0;i--) {
    leds[i] = CRGB(100, 100, i*LoopColorChange);
    leds[i+1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5)
  } 
}
