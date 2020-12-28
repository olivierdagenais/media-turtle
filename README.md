# media-turtle

An old turtle toy repurposed as a media control device.

## The story

My wife was going out shopping with her friend, so I asked her to find me a used toy with buttons on it so I could repurpose it to control my music.  She sends me these two pictures of the candidates she found:

| Candidate 1 | Candidate 2 |
| ----------- | ----------- |
| [![Used musical turtle toy](images/Toy_with_buttons1_small.jpg)](images/Toy_with_buttons1.jpg) | [![Used baby toy](images/Toy_with_buttons2_small.jpg)](images/Toy_with_buttons2.jpg) |

You can probably guess which one I picked.

As you read through the rest, you may start to wonder why an Arduino Leonardo (which natively supports sending USB keyboard key presses to the host, among other things) wasn't used instead of the Arduino Uno (which does not).  That's mostly because I accidentally ordered an Arduino Uno and I figured I could work around the issue with software.  At first, I was going to write a program that runs on the host and listens for messages sent via the serial connection, but eventually I discovered that some awesome people had worked out how to reprogram one of the chips on the Arduino Uno so it could have its firmware flashed like the main chip.  This makes the solution more portable, on top of the geek credentials involved for [connecting two Arduinos together to update one with the other](https://github.com/NicoHood/HoodLoader2/wiki/Burn-the-bootloader-from-another-Arduino).

### What the toy looked like before I started

Here's a couple of "before" photos.

| Top | Bottom | Inside | Buttons |
| --- | ------ | ------ | ------- |
| [![Turtle toy top](images/Turtle_top_small.jpg)](images/Turtle_top.jpg) | [![Turtle toy bottom](images/Turtle_bottom_small.jpg)](images/Turtle_bottom.jpg) | [![Inside of turtle toy](images/Turtle_inside_small.jpg)](images/Turtle_inside.jpg) | [![Underneath the turtle's shell](images/Turtle_buttons_small.jpg)](images/Turtle_buttons.jpg) |

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

### Pin mappings

Here's how the toy's buttons and lights were wired up to the `328P`'s I/O pins.  The `IO_tester` sketch validates that these are wired up correctly.

| Category       | Name     | Color  | Connection    | Note   |
| -------------- | -------- | ------ | ------------- | ------ |
| Digital (PWM~) | 0->RX    |        |               |        |
| Digital (PWM~) | 1->TX    |        |               |        |
| Digital (PWM~) | 2        |        |               |        |
| Digital (PWM~) | 3~       | Blue   | Xylophone     | Light  |
| Digital (PWM~) | 4        | Yellow | Note          | Button |
| Digital (PWM~) | 5~       | Orange | Violon        | Light  |
| Digital (PWM~) | 6~       | Yellow | Piano         | Light  |
| Digital (PWM~) | 7        | Green  | Harp          | Button |
|                |          |        |               |        |
| Digital (PWM~) | 8        | Yellow | Piano         | Button |
| Digital (PWM~) | 9~       | White  | Drum          | Light  |
| Digital (PWM~) | 10~      |        |               |        |
| Digital (PWM~) | 11~      | Green  | Harp          | Light  |
| Digital (PWM~) | 12       | White  | Drum          | Button |
| Digital (PWM~) | 13       |        |               |        |
|                | GND      |        |               |        |
|                | AREF     |        |               |        |
|                | (I2C)SDA |        |               |        |
|                | (I2C)SCL |        |               |        |
|                |          |        |               |        |
|                | IOREF    |        |               |        |
|                | RESET    |        |               |        |
| Power          | 3.3V     |        |               |        |
| Power          | 5V       |        |               |        |
| Power          | GND      |        |               |        |
| Power          | GND      | Blue   | Common ground |        |
| Power          | Vin      |        |               |        |
|                |          |        |               |        |
| Analog In      | A0       | Blue   | Xylophone     | Button |
| Analog In      | A1       | Orange | Violon        | Button |
| Analog In      | A2       |        |               |        |
| Analog In      | A3       |        |               |        |
| Analog In      | A4       |        |               |        |
| Analog In      | A5       |        |               |        |

### What the toy looked liked midway through

After I removed the old circuit board, soldered some extension cables, connected all the grounds together and plugged them into the Arduino's pins, this is what it looked like:

| Digital side | Analog & power side | Ready to be closed up |
| ------------ | ------------------- | --------------------- |
| [![Digital side of the circuit board](images/Digital_side_small.jpg)](images/Digital_side.jpg) | [![Analog & power side](images/Analog_power_side_small.jpg)](images/Analog_power_side.jpg) | [![Ready to close](images/Ready_to_close_small.jpg)](images/Ready_to_close.jpg) |

## The software side

### Design

Unlike the Arduino Leonardo, we can't directly translate a button press into a USB key event: we need to write a sketch for the `328P` that detects button presses, relays them to the `16u2` over the serial connection between the 2 MCUs, then finally write a sketch for the `16u2` to convert instructions received from the `328P` into USB key presses for the host.

### As a diagram

A button press is detected by reading from a pin by the `328P`, it writes a character representing it to the serial port, the `16u2` sees the character and writes it to the USB keyboard:

```mermaid
graph LR;
    button-->|Pin|328P
    328P-->|Serial|16u2
    16u2-->|USB|Host
```
