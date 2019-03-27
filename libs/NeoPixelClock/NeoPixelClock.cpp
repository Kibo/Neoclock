#include "Arduino.h"
#include "NeoPixelClock.h"

NeoPixelClock::NeoPixelClock(Adafruit_NeoPixel& innerStrip, Adafruit_NeoPixel& outerStrip, uint8_t brightness):
_innerStrip (innerStrip), _outerStrip (outerStrip), _brightness (brightness){
	
	_hourColor = NeoPixelClock::Color( 0, 0, 0 );
	_minuteColor = NeoPixelClock::Color( 0, 0, 0 );
	_secondColor = NeoPixelClock::Color( 0, 0, 0 );

	_outerStrip = outerStrip;
	_outerStrip.begin();
	_outerStrip.setBrightness( _brightness);
	
	_innerStrip = innerStrip;
	_innerStrip.begin();
	_innerStrip.setBrightness( _brightness );
}

// Convert separate R,G,B into packed 32-bit RGB color.
uint32_t NeoPixelClock::Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

void NeoPixelClock::update(uint8_t hour, uint8_t minute, uint8_t second){
	 hour = map(hour%12 , 0, 11, 0, 23);

	_outerStrip.clear();
	_outerStrip.setPixelColor( second, getSecondColor());
	_outerStrip.setPixelColor( minute, getMinuteColor());    
	_outerStrip.show();
	
	_innerStrip.clear();	 
	_innerStrip.setPixelColor( hour, getHourColor());    
	_innerStrip.show();
		
	changeColors(hour, minute, second);	

	animateInTime(hour, minute, second);
}

//-- ***************** Getter/ Setter *******************************

void NeoPixelClock::setBrightness(uint8_t b){
	_innerStrip.setBrightness(b);
	_outerStrip.setBrightness(b);
}

void NeoPixelClock::setHourColor(uint32_t color ){
	_hourColor = color;
}

void NeoPixelClock::setMinuteColor(uint32_t color ){
	_minuteColor = color;
}

void NeoPixelClock::setSecondColor(uint32_t color ){
	_secondColor = color;
}

uint32_t NeoPixelClock::getHourColor(){
	return _hourColor;
}

uint32_t NeoPixelClock::getMinuteColor(){
	return _minuteColor;
}

uint32_t NeoPixelClock::getSecondColor(){
	return _secondColor;
}

//-- ***************** Private *******************************

void NeoPixelClock::animateInTime( uint8_t hour, uint8_t minute, uint8_t second ){

	if(minute == 0 && second == 0){
		colorWipe(getMinuteColor(), 50, 0);
		colorWipe(NeoPixelClock::Color(0, 0, 0), 50, 0); //black
	}else 

	if(minute == 15 && second == 0){
		colorWipe(getMinuteColor(), 50, 15);
		colorWipe(NeoPixelClock::Color(0, 0, 0), 50, 15); //black
	}else

	if(minute == 30 && second == 0){
		colorWipe(getMinuteColor(), 50, 30);
		colorWipe(NeoPixelClock::Color(0, 0, 0), 50, 30); //black
	}else

	if(minute == 45 && second == 0){
		colorWipe(getMinuteColor(), 50, 45);
		colorWipe(NeoPixelClock::Color(0, 0, 0), 50, 45); //black
	}	
}

void NeoPixelClock::changeColors(uint8_t hour, uint8_t minute, uint8_t second){
	setSecondColor( wheel(map(second,0,59,0,255) ));
	setMinuteColor( wheel(map(minute,0,59,0,255) ));
	setHourColor( wheel(map(hour,0,23,0,255) ));
}

// Fill the dots one after the other with a color
void NeoPixelClock::colorWipe(uint32_t color, uint8_t wait, uint8_t startPosition) {
  for(uint16_t i=0; i<_outerStrip.numPixels(); i++) {
    _outerStrip.setPixelColor((i+startPosition)%_outerStrip.numPixels(), color);
    _outerStrip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoPixelClock::wheel(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return NeoPixelClock::Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return NeoPixelClock::Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return NeoPixelClock::Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}
