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
// Determine distance in centimeters
// Input: None
// Output: cm as a floating point number
// Speed of sound is calculated using a default temperature
//
float
Sonar::ping_cm()
{
    return (this->ping_cm(this->_default_temp));
}

//
// Determine distance in centimeters
// Input: Temperature in degrees Celsius
// Output: cm as a floating point number
// Speed of sound is calculated for the provided temperature
//
float
Sonar::ping_cm(float temp)
{
    float duration, cm, sos;

    duration = this->_ping_duration();
    sos = (20.05 * sqrt(273.16 + temp)) / 10000;
    cm = duration * sos / 2.0;
    
    return (cm);
}

//
// Determine distance in inches
// Input: None
// Output: in as a floating point number
// Speed of sound is calculated using a default temperature
//
float
Sonar::ping_in()
{
    return(this->cm_to_in(this->ping_cm()));
}

//
// Determine distance in inches
// Input: Temperature in degrees Fahrenheit
// Output: in as a floating point number
// Speed of sound is calculated for the provided temperature
//
float
Sonar::ping_in(float temp)
{
    float distance;

    return(this->cm_to_in(this->ping_cm(this->f_to_c(temp))));
}

//
// Convert centimeters to inches
// Input: (float) centimeters
// Output: (float) inches
//
float
Sonar::cm_to_in(float cm)
{
    return(cm / 2.54);
}

//
// Convert inches to centimeters
// Input: (float) inches
// Output: (float) centimeters
//
float
Sonar::in_to_cm(float in)
{
    return(in * 2.54);
}

//
// Convert degrees celsius to degrees fahrenheit
// Input: (float) degrees C
// Output: (float) degrees F
//
float
Sonar::c_to_f(float c)
{
    return((c * 1.8) + 32.0);
}

//
// Convert degrees fahrenheit to degrees celsius
// Input: (float) degrees F
// Output: (float) degrees C
//
float
Sonar::f_to_c(float f)
{
    return((f - 32.0) / 1.8);
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
