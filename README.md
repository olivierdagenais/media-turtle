# media-turtle

An old turtle toy repurposed as a media control device.

## The story

My wife was going out shopping with her friend, so I asked her to find me a used toy with buttons on it so I could repurpose it to control my music.  She sends me these two pictures of the candidates she found:

| Candidate 1 | Candidate 2 |
| ----------- | ----------- |
| [![Used musical turtle toy](images/Toy_with_buttons1.jpg)](images/Toy_with_buttons1.jpg) | [![Used baby toy](images/Toy_with_buttons2.jpg)](images/Toy_with_buttons2.jpg) |

You can probably guess which one I picked.

### What the toy looked like before I stated

Here's a couple of "before" photos.

| Top | Bottom | Inside | Buttons |
| --- | ------ | ------ | ------- |
| [![Turtle toy top](images/Turtle_top.jpg)](images/Turtle_top.jpg) | [![Turtle toy bottom](images/Turtle_bottom.jpg)](images/Turtle_bottom.jpg) | [![Inside of turtle toy](images/Turtle_inside.jpg)](images/Turtle_inside.jpg) | [![Underneath the turtle's shell](images/Turtle_buttons.jpg)](images/Turtle_buttons.jpg) |

## Technical details

Uses [ELEGOO R3 Board ATmega328P ATMEGA16U2](https://www.elegoo.com/product/elegoo-uno-r3-board-atmega328p-atmega16u2-with-usb-cable/), pictured below:

[![An annotated picture of the ELEGOO R3 Board](images/ELEGOO_R3_Board.jpg)](images/ELEGOO_R3_Board.jpg)

### MCU capabilities

This project leverages the basic USB capabilities made possible by Arduino UNO-compatible boards (i.e. based on the ATmega328P, henceforth known as `328P`) that have an ATmega16U2 Microcontroller unit (MCU), henceforth known as `16u2`.

| Capability | `16u2` | `328P` |
| ---------- | ------ | ------ |
| USB        | Y      | N      |
| I/O pins   | ?      | 20     |
| RAM        | 500b   | 2kb    |
| Flash      | 16kb   | 32kb   |
