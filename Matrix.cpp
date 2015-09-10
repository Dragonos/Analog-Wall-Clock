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

#include "Matrix.h"

Matrix::Matrix(IC_74164_x2 *dualIC, uint8_t rowsPins[7]) :
    m_dualIC(dualIC)
{
    for(uint8_t i = 0; i < 7; ++i)
    {
        m_rowsPins[i] = rowsPins[i];
        m_matrice[i] = 0;
    }
}

void Matrix::begin()
{
    m_dualIC->begin();
    m_dualIC->writeNBits(0xFFF, 12);

    for(uint8_t i = 0; i < 7; ++i)
    {
        pinMode(m_rowsPins[i], OUTPUT);
        digitalWrite(m_rowsPins[i], LOW);
    }
}

void Matrix::reset()
{
    m_dualIC->writeNBits(0xFFF, 12);
    for(uint8_t i = 0; i < 7; ++i)
    {
        digitalWrite(m_rowsPins[i], LOW);
        m_matrice[i] = 0;
    }

}

void Matrix::setRow(uint8_t row, uint16_t data)
{
    m_matrice[row] = data;
}

void Matrix::andRow(uint8_t row, uint16_t data)
{
    m_matrice[row] &= data;
}

void Matrix::orRow(uint8_t row, uint16_t data)
{
    m_matrice[row] |= data;
}

void Matrix::setColomn(uint8_t colomn, uint8_t data)
{
    uint16_t clearMask = ~(1 << colomn);

    for(uint8_t i = 0; i < 7; ++i)
    {
        m_matrice[i] &= clearMask;
        m_matrice[i] |= ((data & (1 << i)) >> i) << colomn;
    }
}

void Matrix::andColomn(uint8_t colomn, uint8_t data)
{
    uint16_t mask = ~(1 << colomn);

    for(uint8_t i = 0; i < 7; ++i)
    {
        m_matrice[i] &= mask | (((data & (1 << i)) >> i) << colomn);
    }
}

void Matrix::orColomn(uint8_t colomn, uint8_t data)
{
    for(uint8_t i = 0; i < 7; ++i)
    {
        m_matrice[i] |= ((data & (1 << i)) >> i) << colomn;
    }
}

void Matrix::render(uint32_t millis)
{
    if(millis < 14) millis = 14;
    for(int d = 0; d < millis/14; ++d)
    {
        for(int i = 0, j = 6; i < 7; ++i, ++j)
        {
            digitalWrite(m_rowsPins[j%7], LOW);
            m_dualIC->writeNBits(~m_matrice[i] & 0xFFF, 12);
            digitalWrite(m_rowsPins[i], HIGH);
            delay(2);
        }
    }
}

