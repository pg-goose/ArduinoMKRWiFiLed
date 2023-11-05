#ifndef Morse_h
#define Morse_h

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include <RTCZero.h>

struct MKRWiFiLed {
  uint8_t red : 8;
  uint8_t green : 8;
  uint8_t blue : 8;
  uint8_t blinks : 8;
  bool reset : 1;
  bool blinking : 1;
  RTCZero timer;
  RTCZero blink;
};

MKRWiFiLed mkr1010Led;

void MKRWiFiLed_begin() {
    pinMode(25, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
}

/**
 * Set the color of the RGB LED. Accepts values from 0 to 100.
*/
void MKRWiFiLed_set(int red, int green, int blue) {
    auto clamp = [](int value) {
        return min(max(value, 0), 100)/100.0*255;
    };

    analogWrite(25, clamp(red));
    analogWrite(26, clamp(green));
    analogWrite(27, clamp(blue));
}

void MKRWiFiLed_clear() {
    analogWrite(25, 0);
    analogWrite(26, 0);
    analogWrite(27, 0);
}

void MKRWiFiLed_turnOnFor(int red, int green, int blue, int duration) {
    int h, m, s = 0;
    h = duration / 3600;
    m = (duration % 3600) / 60;
    s = (duration % 3600) % 60;

    MKRWiFiLed_set(red, green, blue);

    interrupts();
    mkr1010Led.timer.begin(true);
    mkr1010Led.timer.setAlarmTime(h, m, s);
    mkr1010Led.timer.attachInterrupt(MKRWiFiLed_alarmCleanUp);
    mkr1010Led.timer.enableAlarm(mkr1010Led.timer.MATCH_HHMMSS);
}

void MKRWiFiLed_turnOffFor(int duration) {
    int h, m, s = 0;
    h = duration / 3600;
    m = (duration % 3600) / 60;
    s = (duration % 3600) % 60;

    mkr1010Led.red = analogRead(25);
    mkr1010Led.green = analogRead(26);
    mkr1010Led.blue = analogRead(27);
    mkr1010Led.reset = true;

    interrupts();
    mkr1010Led.timer.begin(true);
    mkr1010Led.timer.setAlarmTime(h, m, s);
    mkr1010Led.timer.attachInterrupt(MKRWiFiLed_alarmCleanUp);
    mkr1010Led.timer.enableAlarm(mkr1010Led.timer.MATCH_HHMMSS);
}

void MKRWiFiLed_alarmCleanUp() {
    if (mkr1010Led.reset) {
        MKRWiFiLed_set(mkr1010Led.red, mkr1010Led.green, mkr1010Led.blue);
        mkr1010Led.reset = false;
    } else {
        MKRWiFiLed_clear();
    }
    mkr1010Led.timer.disableAlarm();
    mkr1010Led.timer.detachInterrupt();
}

#endif