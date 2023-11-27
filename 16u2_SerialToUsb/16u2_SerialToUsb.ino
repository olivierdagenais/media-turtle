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

#include "HID-Project.h"

void setup() {
    // Start the Serial1 which is connected with the I/O MCU.
    Serial1.begin(115200);

    Consumer.begin();

    // Start the USB Serial for debugging
    Serial.begin(115200);
}

void loop() {
    // Check if any Serial data from the I/O MCU was received
    int i = Serial1.read();
    if (i >= 0) {
        char c = (char)i;
        switch(c) {
          case '0': // piano
            Consumer.write(MEDIA_PLAY_PAUSE);
            break;
          case '1': // drum
            Consumer.write(MEDIA_REWIND);
            break;
          case '3': // violon
            Consumer.write(MEDIA_FAST_FORWARD);
            break;
          case '4': // harp
            Consumer.write(MEDIA_PREVIOUS);
            break;
          case '5': // note
            Consumer.write(MEDIA_PLAY_PAUSE);
            break;
          case '6': // xylophone
            Consumer.write(MEDIA_PREVIOUS);
            break;
        }
    }
}
