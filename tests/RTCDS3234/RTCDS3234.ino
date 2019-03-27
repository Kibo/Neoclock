#include <SPI.h>
#include <SparkFunDS3234RTC.h>

#define DS13074_CS_PIN 10 // DeadOn RTC Chip-select pin
#define INTERRUPT_PIN 2 // DeadOn RTC SQW/interrupt pin (optional)

void setup() {  
  Serial.begin(9600);

  rtc.begin(DS13074_CS_PIN);

  #ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  #endif
   
  rtc.autoTime();  
}

void loop() {
  
  static int8_t lastSecond = -1;    
    
  rtc.update();

  if (rtc.second() != lastSecond){ // If the second has changed  
    Serial.println( getTime() );    
    lastSecond = rtc.second(); 
  } 
}

String getTime(){
  return String(rtc.hour()) + ":" + String(rtc.minute()) + ":" + String(rtc.second());
}
