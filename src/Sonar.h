#ifndef __Sonar_h
#define __Sonar_h

#include "Arduino.h"

class Sonar {
    public:
	Sonar(uint8_t pin_trigger, uint8_t pin_echo);
	float ping_cm();
	float ping_cm(float temp);
	float ping_in();
	float ping_in(float temp);
	float cm_to_in(float cm);
	float in_to_cm(float in);
	float c_to_f(float c);
	float f_to_c(float f);
    private:
	float _ping_duration();
	uint8_t _pin_trigger;
	uint8_t _pin_echo;
	uint8_t _delay_trigger = 10;
	bool _single_pin;
	const float _default_temp = 20.0;   // Default temperature (C)
};
#endif /* __Sonar_h */
