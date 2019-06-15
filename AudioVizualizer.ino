

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
  int aValue = 10;

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
  int SensorValue, Mapped, Average, Blue, Green, Red;
  
  SensorValue = analogRead(AnalogReadPin);
  Mapped = map(SensorValue, 0.0, 737.0, 0, 100); 
  
  if (Mapped == 0) //If 0 this isn't right, return
    return;
//A TEST
  //leds[3] = CRGB(0,255,0);
  //FastLED.show();
  
  //Showtime
  if (Mapped > 0 && Mapped <= 50)
    Blue = map((50-Mapped)*Mapped,0,625,0,255);
  if (Mapped > 25 && Mapped <= 75)
    Green = map((25-Mapped)*(75-Mapped),0,625,0,255);
  if (Mapped > 50 && Mapped <= 75)
    Red = map((50-Mapped)*(100-Mapped),0,625,0,255);
  if (Mapped > 75)
    Red = 200;
  
  leds[3] = CRGB(Red, Green, Blue);
  FastLED.show();
  
  int LitGroup = 8, BreakGroup = 4, Count; 
  for (Count = 1; Count < NumLEDS; Count++){
    for (int i = 0; i <= LitGroup + BreakGroup; i++) {
      //leds[Count+i-1] = leds[Count+i+1];
      
      if (i < BreakGroup)
        leds[Count+i] = CRGB(0, 0, 0);
        //leds[Count+i] = leds[Count+i+1];
      
      if (i > BreakGroup && i <= LitGroup + BreakGroup) //Light them up
         leds[Count+i] = CRGB(Red, Green, Blue); //Lit LED group
         //leds[Count+i] = leds[Count+i+1];
      
      for (int j = 2; j <= Count+i; j++) {
        leds[j] = leds[Count+i]; 
      }
    }
  }
  
  /*for (Count = 1; Count <= NumLEDS; Count++) { // ONE ATTEMPT
     int Rest = 1; // Needed????
     for (int i = 0; i<=LitGoup+BreakGroup; i++) {
       if (i <= BreakGroup) //Break in between Group
         leds[Count+i] = CRGB(0, 0, 0);
         Rest++;
       if (i > BreakGroup && i <= LitGroup + BreakGroup) //Light them up
         leds[Count+i] = CRGB(Red, Green, Blue); //Lit LED group
    }
  }*/
}
  /*int Blue = map(Mapped,0,50,0,255);
  int Green = 0; 
  int Red = 0;
  if (Mapped > 50)
    int Green = map(Mapped,50,100,0,255);
  if (Mapped > 70)
    int Red = map(Mapped,70,100,0,255);*
    
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
