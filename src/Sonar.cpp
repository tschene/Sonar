#include "Sonar.h"

//
// Constructor
// - Record trigger and echo pins
// - Set trigger pin low (disabled)
// - Set trigger pin to output mode
// - Set echo pin to input mode
//
Sonar::Sonar(uint8_t pin_trigger, uint8_t pin_echo)
{
    this->_pin_trigger = pin_trigger;
    this->_pin_echo = pin_echo;
    this->_single_pin = (pin_trigger == pin_echo);
    digitalWrite(this->_pin_trigger, LOW);
    pinMode(this->_pin_trigger, OUTPUT);
    if (!this->_single_pin) {
	pinMode(this->_pin_echo, INPUT);
    }
}

//
// Determine distance in inches
// Input: None
// Output: in as a floating point number
//
float
Sonar::ping_in()
{
    float duration, in;

    duration = this->_ping_duration();
    in = duration * this->_sos_in / 2.0;
    
    return (in);
}

//
// Determine distance in centimeters
// Input: None
// Output: cm as a floating point number
//
float
Sonar::ping_cm()
{
    float duration, cm;

    duration = this->_ping_duration();
    cm = duration * this->_sos_cm / 2.0;
    
    return (cm);
}

//
// Send a signal and measure the time taken to return
// Input: None
// Output: duration in microseconds as a floating point number
// Procedure:
// - Set trigger pin to HIGH to enable the transmitter. Per the
//   HC-SR04 spec, it must be held high for 10us.
// - Set trigger pin back to LOW
// If a single pin is being used for both trigger and echo, we
// must manipulate the pin mode before reading or writing the pin.
//
//
float
Sonar::_ping_duration()
{
    float duration;

    // Trigger the ping
    digitalWrite(this->_pin_trigger, HIGH);
    delayMicroseconds(this->_delay_trigger);
    digitalWrite(this->_pin_trigger, LOW);

    //
    // Read the results. Need to set the pin mode to INPUT if we're
    // using only one pin.
    //
    if (this->_single_pin) {
	pinMode(this->_pin_echo, INPUT);
    }
    duration = pulseIn(this->_pin_echo, HIGH, 30000);

    //
    // If single pin, set it back to OUTPUT so we're
    // ready for the next cycle
    //
    if (this->_single_pin) {
	pinMode(this->_pin_trigger, OUTPUT);
    }
    
    return (duration);
}
