#include "MKRWiFiLed.h"

void setup() {
    MKRWiFiLed_begin();

    // Set RGB color with values from 0 to 100
    MKRWiFiLed_set(100, 0, 0);
    delay(1000);
    MKRWiFiLed_set(0, 100, 0);
    delay(1000);
    MKRWiFiLed_set(0, 0, 100);
    delay(1000);
    MKRWiFiLed_clear();
    delay(1000);

    // Time duration in seconds
    MKRWiFiLed_turnOnFor(100, 0, 0, 5);
    delay(5000);

    MKRWiFiLed_set(50, 100, 50);
    MKRWiFiLed_turnOffFor(0, 100, 0, 5);
    delay(5000);
}

void loop() {
    
}