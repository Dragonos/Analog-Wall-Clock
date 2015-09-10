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

#ifndef MATRIX_H
#define MATRIX_H

#include <Electro_IC_74164_x2.h>

using namespace Electro;

class Matrix
{
public:
    Matrix(IC_74164_x2 *dualIC, uint8_t rowsPins[7]);
    void begin();

    void reset();

    void setRow(uint8_t row, uint16_t data); // 0x0FFF
    void andRow(uint8_t row, uint16_t data);
    void orRow(uint8_t row, uint16_t data);

    void setColomn(uint8_t colomn, uint8_t data); // 0x7F
    void andColomn(uint8_t colomn, uint8_t data);
    void orColomn(uint8_t colomn, uint8_t data);

    void render(uint32_t millis = 0);

private:
    IC_74164_x2 *m_dualIC;
    uint8_t m_rowsPins[7];

    // Data
    uint16_t m_matrice[7]; // i = row // m_matrice[i] = Colomns
};

#endif // MATRIX_H
