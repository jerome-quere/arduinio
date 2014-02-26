/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jerome Quere <contact@jeromequere.com>
 *
 * Permission is hereby granted, free  of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction,  including without limitation the rights
 * to use,  copy,  modify,  merge, publish,  distribute, sublicense, and/or sell
 * copies  of  the  Software,  and  to  permit  persons  to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above  copyright  notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY  OF ANY KIND, EXPRESS OR
 * IMPLIED,  INCLUDING BUT NOT LIMITED  TO THE  WARRANTIES  OF  MERCHANTABILITY,
 * FITNESS  FOR A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT  OF  OR  IN  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
