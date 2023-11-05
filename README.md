# ArduinoMKRWiFiLed

## Usage

Just inlcude the library and use it's methods. See the example.

## Details

This library depends on RTCZero and uses it's alarm interrupt functionality to set or clear the led on the functions `turnOnFor` and `turnOffFor`. This functions are non-blocking. They will also **enable interrupts**.

`turnOffFor` will turn off the led and **restore** the color after the given time. (If the color was 0 it will seem as the function didn't do anything.)

## Example

```c++
#include "ArduinoMKRWiFiLed.h"

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
    delay(5500);

    MKRWiFiLed_set(50, 100, 50);
    MKRWiFiLed_turnOffFor(0, 100, 0, 5);
    delay(5500);
}

void loop() {
    
}
```