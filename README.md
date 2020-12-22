# media-turtle

An old turtle toy repurposed as a media control device.

Uses [ELEGOO R3 Board ATmega328P ATMEGA16U2](https://www.elegoo.com/product/elegoo-uno-r3-board-atmega328p-atmega16u2-with-usb-cable/), pictured below:

![An annotated picture of the ELEGOO R3 Board](images/ELEGOO_R3_Board.jpg)

## MCU capabilities

This project leverages the basic USB capabilities made possible by Arduino UNO-compatible boards (i.e. based on the ATmega328P, henceforth known as `328P`) that have an ATmega16U2 Microcontroller unit (MCU), henceforth known as `16u2`.

| Capability | `16u2` | `328P` |
| ---------- | ------ | ------ |
| USB        | Y      | N      |
| I/O pins   | ?      | 20     |
| RAM        | 500b   | 2kb    |
| Flash      | 16kb   | 32kb   |
