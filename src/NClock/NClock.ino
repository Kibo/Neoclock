#include <SPI.h>
#include <SparkFunDS3234RTC.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <NeoPixelClock.h>
#include <OSMp3.h>

// RTC
#define DS13074_CS_PIN 10 // DeadOn RTC Chip-select pin

// Bluetooth
#define HC06_RX 3
#define HC06_TX 2
SoftwareSerial hc06( HC06_TX, HC06_RX );
String cmd="";

// Serial MP3 Player
#define MP3_RX 5 //should connect to TX of the Serial MP3 Player module
#define MP3_TX 6 //connect to RX of the module
OSMp3 mp3( MP3_RX, MP3_TX);
uint8_t currentSongNumber = 1;
uint8_t currentVolume = 14;

// NeoPixels
#define OUTER_STRIP_NUMBER_OF_LED 60
#define OUTER_STRIP_DATA_PIN 8
#define INNER_STRIP_NUMBER_OF_LED 24
#define INNER_STRIP_DATA_PIN 9  
Adafruit_NeoPixel inner( INNER_STRIP_NUMBER_OF_LED, INNER_STRIP_DATA_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel outer( OUTER_STRIP_NUMBER_OF_LED, OUTER_STRIP_DATA_PIN, NEO_GRB + NEO_KHZ800);
uint8_t defaultBrightness = 18;
NeoPixelClock clock( inner, outer, defaultBrightness);

void setup() {     
  rtc.begin(DS13074_CS_PIN);   
  rtc.autoTime(); 

  hc06.begin(9600);  
}

void loop() {
  static int8_t lastSecond = -1;    
  
  rtc.update();
    
  if (rtc.second() != lastSecond){ // If the second has changed    
    clock.update(  rtc.hour(), rtc.minute(), rtc.second());               
    lastSecond = rtc.second();     
  } 

  if (rtc.alarm1()){
    clock.setBrightness( defaultBrightness );           
    mp3.play(currentSongNumber, currentVolume);
  }
    
  readBlueToothCommand();  
    
  delay(100); 
}


void readBlueToothCommand(){
  
  //Read data from HC06
  while(hc06.available()>0){
    cmd+=(char)hc06.read();
  }
  
  if(cmd!=""){ 
  hc06.println("Command recieved : ");
  hc06.println(cmd);
  
  if(cmd == "gt"){                                   
    hc06.println( "Now : " + getTime());             
    
  }else if(cmd.startsWith("st")){                                   
     hc06.println( "Set time: " + cmd );         
     rtc.setTime(0, parseMinutes(cmd), parseHours(cmd), 1, 18, 12, 18);
     rtc.update();
     hc06.println( "Now : " + getTime()); 
       
  }else if(cmd.startsWith("sa")){
     hc06.println( "Set alarm: " + cmd );
     rtc.setAlarm1(0, parseMinutes(cmd), parseHours(cmd));        
     hc06.println( "Alarm : " + String(parseHours(cmd)) + ":" + String(parseMinutes(cmd))); 
  
  }else if(cmd.startsWith("ss")){                                   
     hc06.println( "Set song: " + cmd );
     currentSongNumber = parseCmd(cmd);                     
     hc06.println( "Alarm song: " + String(parseCmd(cmd))); 
           
  }else if(cmd.startsWith("ps")){                                   
     hc06.println( "Play song: " + cmd );          
     mp3.play(parseCmd(cmd), currentVolume);
     hc06.println( "Playing: " + String(parseCmd(cmd))); 
  
  }else if(cmd.startsWith("sb")){                                   
     hc06.println( "Set brihtness: " + cmd );                     
     clock.setBrightness( parseCmd(cmd) );
     hc06.println( "Brightness: " + String(parseCmd(cmd)));

  }else if(cmd.startsWith("sv")){                                   
     hc06.println( "Set volume: " + cmd );                     
     currentVolume = parseCmd(cmd);
     hc06.println( "Volume: " + String(parseCmd(cmd)));
                        
  }else{     
     hc06.println("Commands:");
     hc06.println("gt - get time, show current time");
     hc06.println("st1206 - set time, 4 digit");
     hc06.println("sa0502 - set alarm, 4 digit");    
     hc06.println("ss2 - set alarm song, 0 - songs number");
     hc06.println("ps1 - play song, play alarm song 1");         
     hc06.println("sb100 - set brightness, 0 - 200");
     hc06.println("sv14 - set volume, 0 - 15");
  }
  
  cmd=""; //reset cmd
  }
}

// -- Helper method ------------------------
String getTime(){
  return String(rtc.hour()) + ":" + String(rtc.minute()) + ":" + String(rtc.second());
}

int parseHours(String cmd){
  return cmd.substring(2).substring(0,2).toInt();
}

int parseMinutes(String cmd){
  return cmd.substring(2).substring(2).toInt();
}

int parseCmd(String cmd){
  return cmd.substring(2).toInt();
}
