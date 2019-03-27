/************************************************* ************************************************** ******
OSMp3.h - Lybrary for Serial MP3 Player a module by Open-Smart Team and Catalex Team  
Created by Tomas Jurman, March 7, 2019.
Released into the public domain.

mp3.play( index, volume );
mp3.stop();

************************************************** **************************************************/
#include <OSMp3.h>


#define ARDUINO_RX 5 //should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 6 //connect to RX of the module

void setup() {
  OSMp3 mp3( ARDUINO_RX, ARDUINO_TX);
  
  mp3.play(1,12); // play song 1 with volume 12

  delay(5000); 
  mp3.stop();
  
  mp3.play(2,14); // play song 2 with volume 14
  delay(10000); 
  mp3.stop();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
