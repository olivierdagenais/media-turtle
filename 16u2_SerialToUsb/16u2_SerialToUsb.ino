// Copyright (c) Olivier Dagenais. All rights reserved.
// Licensed under the MIT license. See LICENSE in the project root.

/*
 *  Relays the serial output from the 328P to the host as USB keyboard key
 * presses.
 *
 *  This sketch is to be uploaded to the "HoodLoader16u2" board.
 *
 *  Based on
 * https://github.com/NicoHood/HoodLoader2/blob/8aef3e1cee07f68e51e9b1e3678a3b5bf72c99b4/avr/examples/HID-Bridge/HID-Bridge_USB/HID-Bridge_USB.ino
 */

#include "HID.h"
#include "Keyboard.h"

void setup() {
    // Start the Serial1 which is connected with the I/O MCU.
    Serial1.begin(115200);

    Keyboard.begin();

    // Start the USB Serial for debugging
    Serial.begin(115200);
}

void loop() {
    // Check if any Serial data from the I/O MCU was received
    int i = Serial1.read();
    if (i >= 0) {
        char c = (char)i;
        Keyboard.print(c);
    }
}
