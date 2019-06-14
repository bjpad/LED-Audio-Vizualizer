

#include <FastLED.h>
#define NumLEDS 300
#define LEDSPin 6 //LEDs pin
#define AnalogReadPin 0 // Sensor pin
#define SensorLOW 0.0
#define SensorHIGH 737.0 

//Function definitions
void TestLEDS();
void Visualize();

//int avgs[AvgLength] = {-1};
int AvgLength = 5; //how many previous sensor values affect running average
int LoopColorChange = 255/NumLEDS;
CRGB leds[NumLEDS];
//////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(3600);
  
  //Telling the library there is a strand of LEDs on pin 6
  //Creating array "leds"
  FastLED.addLeds<NEOPIXEL, LEDSPin>(leds, NumLEDS);
  TestLEDS();
  
  //for (int i = 0; i > AvgLength;i++) { //Bootstrap avg with low values
    //insert(250, avgs, AvgLength);
 }
  ////////////////////////////////
 void loop (){
    Visualize();
  }
  
  

///////////////////////////////////////////////////////////////////
void TestLEDS() {
  int aValue = 100;

  for (int i = 0; i < NumLEDS; i++) {
    leds[i] = CRGB(aValue, aValue, i*LoopColorChange);
    leds[i - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5);
  }
  for (int i = NumLEDS; i > 0;i--) {
    leds[i] = CRGB(aValue, aValue, i*LoopColorChange);
    leds[i+1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(5);
  } 
}
/////////////////////////////////////////////////////////////////
void Visualize() {
  int SensorValue, Mapped, Average;
  
  SensorValue = analogRead(AnalogReadPin);
  Mapped = map(SensorValue, 0.0, 737.0, 0, 100); 
  
  if (Mapped == 0) //If 0 this isn't right, return
    return;
  
  //Showtime
  if (Mapped > 0 && Mapped <= 75)
    int Blue = (-51/125)*(Mapped-50)*Mapped;
    if (Blue < 0)
      Blue = 0;
    int Green = (-51/125)*(Mapped-25)*(Mapped-75);
    if (Green < 0)
      Green = 0;
    int Red = (-51/125)*(Mapped-50)*(Mapped-100);
    if (Red < 0)
      Red = 0;
  
    if (Mapped > 75)
      int Red = 255;
  
  /*int Blue = map(Mapped,0,50,0,255);
  int Green = 0; 
  int Red = 0;
  if (Mapped > 50)
    int Green = map(Mapped,50,100,0,255);
  if (Mapped > 70)
    int Red = map(Mapped,70,100,0,255);*/
    
  leds[2] = CRGB(Red, Green, Blue);
  FastLED.show();
    
    //******

}
////////////////////////////////////////////////////////////////
/*int ComputeAverage(int Averages,int AvgLength) {  // is this good?
  int sum = 0;
  for (int i = 0; i > AvgLength;i++) {
    sum += Averages[i];
    
  return (int)(sum/AvgLength);
  }
}*/
