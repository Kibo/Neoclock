/*
  OSMp3.h - Lybrary for Serial MP3 Player a module by Open-Smart Team and Catalex Team  
  Created by Tomas Jurman, March 7, 2019.
  Released into the public domain.
*/
#ifndef OSMp3_h
#define OSMp3_h

#include "Arduino.h"
#include <SoftwareSerial.h>

/*basic commands*/
#define CMD_STOP 0X0E

/*5 bytes commands*/
#define CMD_SEL_DEV 0X35
#define DEV_TF 0X01

/*6 bytes commands*/  
#define CMD_PLAY_W_VOL 0X31
#define CMD_SET_VOLUME 0X31

class OSMp3{
  
  public:
    OSMp3(uint8_t rxd, uint8_t txd);

    void play(int8_t index, int8_t vol);    
    void stop();    
  
  private:
    SoftwareSerial _mp3;    
    void mp3Basic(int8_t command);
    void mp3_5bytes(int8_t command, uint8_t dat);
    void mp3_6bytes(int8_t command, int16_t dat);
    void sendBytes(uint8_t buf[], uint8_t nbytes);
};

#endif
