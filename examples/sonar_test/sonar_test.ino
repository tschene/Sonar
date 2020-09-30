#include "Sonar.h"

// Define pins
const int TRIG_PIN	= 2;
const int ECHO_PIN	= 3;

Sonar sonar(TRIG_PIN, ECHO_PIN);

void
setup() 
{ 
    // Initialize I/O pins and set initial state
    digitalWrite(TRIG_PIN, LOW);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.begin(9600);
} 
 
void
loop() 
{ 
    float distance;

    // Send a ping twice a second.

    distance = sonar.ping_in();
    Serial.print("distance = ");
    Serial.print(distance);
    Serial.println(" in");
    delay(2000); 
} 
