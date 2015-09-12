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

#include "AnalogClock.h"

#define DISABLED    0
#define ENABLED     1

#define NO_SKIP     0
#define SKIP_H      1
#define SKIP_M      2


AnalogClock::AnalogClock(IC_74164_x2 *dualIC, uint8_t rowsPins[7], uint8_t btnH, uint8_t btnM) :
    m_matrix(dualIC, rowsPins),

    m_configMode(DISABLED),
    m_skipNextUp(NO_SKIP),

    m_btnH(btnH, E_BUTTON_PULL_DOWN),
    m_btnM(btnM, E_BUTTON_PULL_DOWN)
{
}

void AnalogClock::begin()
{
    Wire.begin();
    m_rtc.begin();
    if(!m_rtc.isrunning())
    {
        // following line sets the RTC to the date & time this sketch was compiled
        m_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2015 at 3am you would call:
        // m_rtc.adjust(DateTime(2015, 1, 21, 3, 0, 0));
    }

    m_matrix.begin();
    m_btnH.begin();
    m_btnM.begin();
}

void AnalogClock::render()
{
    m_now = m_rtc.now();

    m_matrix.reset();
    m_matrix.setHourHand(m_now.hour());
    m_matrix.setMinuteHand(m_now.minute());

    // Hour Marks bink mask
    uint8_t col = (m_now.minute()/5+12-ANALOGCLOCKMATRIX_COL_0)%12;
    uint16_t mask = 0xFFFF;

    if(m_now.minute() % 5 > 0 && m_now.minute() % 5 < 4) // minute = X*5+1 or X*5+2 or X*5+3
        mask &= ~(1 << col);
    if(m_now.minute() % 5 > 1 ) // minute = X*5+2 or X*5+3 or X*5+4
    {
        if(col < 11)
            mask &= ~(1 << col+1);
        else
            mask &= 0xFFFE;
    }

    while(m_rtc.now().minute() == m_now.minute())
    {
        // Move the mark of second
        m_matrix.setSecondMark(m_rtc.now().second());

        for(int j=0; j<2; j++)
        {
            // Hour Marks
            m_matrix.setHourMarks(mask);
            // Config Mode
            m_matrix.setCenter((m_configMode)? 0 : 0xFFFF);

            // Render and Check Configuration
            if(renderAndCheckConfig(210)) return;

            // Hour Marks
            m_matrix.setHourMarks();
            // Config Mode
            m_matrix.setCenter();

            // Render and Check Configuration
            if(renderAndCheckConfig(224)) return;
        }
    }
}

uint8_t AnalogClock::renderAndCheckConfig(uint32_t millis)
{
    for(uint8_t i = 0; i< (millis/14); i++)
    {
        m_matrix.render(14);
        if(config()) return 1;
    }
    return 0;
}

uint8_t AnalogClock::config()
{
    m_btnH.check();
    m_btnM.check();

    // Check if the hour and the minute buttons are simultaneously up
    if((m_btnH.state() == E_BUTTON_UP && m_btnM.state() == E_BUTTON_UP)
       || (m_btnH.state() == E_BUTTON_UP && m_btnM.state() == E_BUTTON_IN)
       || (m_btnH.state() == E_BUTTON_IN && m_btnM.state() == E_BUTTON_UP))
    {
        // Switch configuration mode
        m_configMode = !m_configMode;

        // Skip next Button Up
        if(m_configMode)
        {
            if(m_btnH.state() == E_BUTTON_IN)
                m_skipNextUp = SKIP_H;
            else if(m_btnM.state() == E_BUTTON_IN)
                m_skipNextUp = SKIP_M;
        }
        else
           m_skipNextUp =  NO_SKIP;

    }
    // In Configuration Mode
    else if(m_configMode)
    {
        // Hour button up
        if(m_btnH.state() == E_BUTTON_UP && m_skipNextUp != SKIP_H)
        {
            m_skipNextUp = NO_SKIP;

            m_rtc.adjust(DateTime(m_now.unixtime()+3600));
            return 1;
        }
        // Minute button up
        else if(m_btnM.state() == E_BUTTON_UP && m_skipNextUp != SKIP_M)
        {
            m_skipNextUp = NO_SKIP;

            m_rtc.adjust(DateTime(m_now.unixtime()+60));
            return 1;
        }
    }

    return 0;
}

