/*
    The MIT License (MIT)

    Copyright (c) 2015 Amine Ben Hassouna (https://github.com/Dragonos)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

 */

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <Electro_IC_74164_x2.h>
#include <Electro_PushButton.h>

#include "AnalogClock.h"

uint8_t rowPins[7] = {8,7,6,5,4,3,2}; // 6 5 4 3 2 1 0

#define DATA_PIN     A3
#define CLK_PIN0     A2
#define CLK_PIN1     A1
#define CLR_PIN      A0

#define BTN_H   10
#define BTN_M   9

IC_74164_x2 dualIC(DATA_PIN,CLK_PIN0,CLK_PIN1,CLR_PIN, MSBFIRST);
AnalogClock clock(&dualIC, rowPins, BTN_H, BTN_M);


void setup()
{
    clock.begin();
}

void loop()
{
    clock.render();
}
