/*
  NeoPixelClock.h - Show time in two NeoPixels.
  Created by Tomas Jurman, March 18, 2019.
  Released into the public domain.
*/
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class NeoPixelClock{	 
  public:		
        NeoPixelClock(Adafruit_NeoPixel& innerStrip, Adafruit_NeoPixel& outerStrip, uint8_t brightness);

	void update(uint8_t hour, uint8_t minute, uint8_t second);    
	
	void setBrightness(uint8_t b);

	static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
	
	void setHourColor( uint32_t color);
	void setMinuteColor( uint32_t color);
	void setSecondColor( uint32_t color);

	uint32_t getHourColor();
	uint32_t getMinuteColor();
	uint32_t getSecondColor();
	
  private:		
	uint8_t _brightness;
	uint32_t _hourColor;
	uint32_t _minuteColor;
	uint32_t _secondColor;	
	
	Adafruit_NeoPixel& _innerStrip;
	Adafruit_NeoPixel& _outerStrip;
	
	void animateInTime( uint8_t hour, uint8_t minute, uint8_t second );
	void changeColors(uint8_t hour, uint8_t minute, uint8_t second);
	void colorWipe(uint32_t color, uint8_t wait, uint8_t startPosition);
	uint32_t wheel(byte wheelPos);
};

#endif
