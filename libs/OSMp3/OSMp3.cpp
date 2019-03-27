#include "Arduino.h"
#include <SoftwareSerial.h>
#include "OSMp3.h"

OSMp3::OSMp3(uint8_t rxd, uint8_t txd):_mp3(rxd, txd){  
	_mp3.begin(9600);	
}

/**
 * @param index - the index of song
 * @param vol - volume (0 -15 )
 */
void OSMp3::play(int8_t index, int8_t vol){  
	stop();
		
	if(vol < 0){
		vol = 0;
	}else if(vol > 0x1e){
		vol = 0x1e;//max volume
	}

	int16_t dat;
	dat = ((int16_t)vol) << 8;
	dat |= index;
	mp3_6bytes(CMD_PLAY_W_VOL, dat);
        delay(200);//wait for 200ms
}

void OSMp3::stop(){  
  mp3Basic(CMD_STOP);  
  delay(200);//wait for 200ms
}

void OSMp3::mp3Basic(int8_t command){
  uint8_t Send_buf[4];
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x02; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = 0xef; //
  sendBytes(Send_buf,4);
}

void OSMp3::mp3_5bytes(int8_t command, uint8_t dat){
  uint8_t Send_buf[5];
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x03; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = dat; //
  Send_buf[4] = 0xef; //
  sendBytes(Send_buf,5);
}

void OSMp3::mp3_6bytes(int8_t command, int16_t dat){
  uint8_t Send_buf[6];
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x04; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = (int8_t)(dat >> 8);//datah
  Send_buf[4] = (int8_t)(dat); //datal
  Send_buf[5] = 0xef; 
  sendBytes(Send_buf,6);
}

void OSMp3::sendBytes(uint8_t buf[], uint8_t nbytes){
  for(uint8_t i=0; i < nbytes; i++){
    _mp3.write(buf[i]) ;
  }
}