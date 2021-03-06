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

#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <Wire.h>
#include <RTClib.h>
#include <Electro_PushButton.h>

#include "AnalogClockMatrix.h"


class AnalogClock
{
public:
    AnalogClock(IC_74164_x2 *dualIC, uint8_t rowsPins[7], uint8_t btnH, uint8_t btnM);
    void begin();

    void render();

private:
    uint8_t renderAndCheckConfig(uint32_t millis);
    uint8_t config();

private:
    RTC_DS1307 m_rtc;

    // Current time
    DateTime m_now;

    AnalogClockMatrix m_matrix;

    // Configuration Mode
    uint8_t m_configMode,

    // Skip next up
    m_skipNextUp;

    // Buttons
    PushButton m_btnH, m_btnM;
};

#endif // ANALOGCLOCK_H
