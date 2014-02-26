This simple program will make LED plug on pins 11 and 12 for one second each.

## Blink.cpp ##

```C

#include <Arduino.h>
#include "IOService.h"

using namespace aio;

void ledRed(void*);
void ledGreen(void*);

#define GREEN_LED 11
#define RED_LED 12
#define TIME 1000

void ledGreen(void*) {
    digitalWrite(RED_LED, LOW); //Switch off red led.
    digitalWrite(GREEN_LED, HIGH); //Switch on green led.
    aio::IOService::instance().addTimer(TIME, ledRed, NULL); //Add a timer that will call ledRed in 1 second.
}

void ledRed(void*) {
    digitalWrite(GREEN_LED, LOW); //Switch off green led.
    digitalWrite(RED_LED, HIGH); //Switch on red led.
    aio::IOService::instance().addTimer(TIME, ledGreen, NULL); //Add a timer that will call ledGreen in 1 second.
}

void setup () {
    pinMode(GREEN_LED, OUTPUT); //Set both GREEN_LED and RED_LED
    pinMode(RED_LED, OUTPUT);   // pins to OUTPUT mode.
}

void loop() {
    aio::IOService service; //Create the IOService object.
    ledGreen(NULL); //Init the Green led first.
    service.exec(); //Run the event loop.
}


```