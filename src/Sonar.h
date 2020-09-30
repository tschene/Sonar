#ifndef __Sonar_h
#define __Sonar_h

#include "Arduino.h"

class Sonar {
    public:
	Sonar(uint8_t pin_trigger, uint8_t pin_echo);
	float ping_cm();
	float ping_in();
    private:
	float _ping_duration();
	uint8_t _pin_trigger;
	uint8_t _pin_echo;
	uint8_t _delay_trigger = 10;
	bool _single_pin;
	const float _sos_cm = 0.0343;	    // Speed of sound (cm/usec)
	const float _sos_in = 0.0135039;    // Speed of sound (in/usec)
};
#endif /* __Sonar_h */
