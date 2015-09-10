
# Analog Wall Clock : Circular LED Matrix

Released under Club Systèmes Embarqués - Esprit (Embedded Systems Club of Esprit), the Analog Wall Clock project consists of a circular LED matrix showing the time. The electronic circuit is based on the Atmega328P microcontroller, the DS1307 real time clock and the 74164 8-bits parallel-out shift registers.

The use of the Atmega328P microcontroller, witch is the same microcontroller used in the Arduino Uno Board, lets us benefit from the easy-to-use library offered by Arduino and lets us use the Arduino Uno Board as an In-Circuit Serial Programmer.

We used the [Adafruit fork of Jeelab's fantastic RTC library](https://github.com/adafruit/RTClib) to communicate with the DS1307 Real time clock and the [Electro](https://github.com/Dragonos/Electro) library to check push buttons status and control the 74164 integrated circuit.


## Prototype 1.0

The Analog Wall Clock Prototype version 1.0 was released by :

* [Amine Ben Hassouna (Dragonos)](https://github.com/Dragonos)
* Mohsen Sammary
* Slaheddinne Ahmed
* Yosra Fourati
* Souleymane Diallo


## License

All source code in this project is licensed under the terms of the MIT license.
The electronic schema of this project is licensed under the terms of the [Creative Commons Attribution 4.0 International Public License (CC-BY 4.0)](http://creativecommons.org/licenses/by/4.0).
