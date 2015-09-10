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

#ifndef ANALOGCLOCKMATRIX_H
#define ANALOGCLOCKMATRIX_H

#include "Matrix.h"

#define ANALOGCLOCKMATRIX_COL_0 8

class AnalogClockMatrix : public Matrix
{
public:
    inline AnalogClockMatrix(IC_74164_x2 *dualIC, uint8_t rowsPins[7]) :
        Matrix(dualIC, rowsPins)
    {
    }

    // Dislay

    inline void setHourHand(uint8_t h)
    {
        orColomn((h+12-ANALOGCLOCKMATRIX_COL_0)%12, 0x0F);
    }

    inline void setMinuteHand(uint8_t m)
    {
        orColomn((m/5+12-ANALOGCLOCKMATRIX_COL_0)%12, 0x1F);
    }

    inline void setSecondMark(uint8_t s)
    {
        setRow(6, 1 << ( (s+12-ANALOGCLOCKMATRIX_COL_0-1) % 12) );
    }

    inline void setHourMarks(uint16_t mask = 0x0FFF)
    {
        setRow(5, mask);
    }

    inline void setCenter(uint16_t mask = 0xFFFF)
    {
        setRow(0, mask);
    }

};

#endif // ANALOGCLOCKMATRIX_H
