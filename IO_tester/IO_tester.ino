// Copyright (c) Olivier Dagenais. All rights reserved.
// Licensed under the MIT license. See LICENSE in the project root.

/*
 * A program to test the connections in the media-turtle. Upload to the Arduino UNO (328P).
 */

const int pwm[] = {
  3,
  5,
  6,
  9,
  11
};
const int pwmCount = 5;

const int digitalIn[] = {
  4,
  7,
  8,
  12
};
const int inCount = 4;

int brightness = 0;
int fadeAmount = 5;

const int analogCount = 2;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < inCount; i++) {
    int digitalPin = digitalIn[i];
    pinMode(digitalPin, INPUT_PULLUP);
  }
  for (int o = 0; o < pwmCount; o++) {
    int digitalPin = pwm[o];
    pinMode(digitalPin, OUTPUT);
  }
}

void loop() {

  for (int a = 0; a < analogCount; a++) {
    int v = analogRead(a);
    Serial.print(v < 15 ? 1 : 0);
    Serial.print(v);
    Serial.print(", ");
  }
  for (int i = 0; i < inCount; i++) {
    int digitalPin = digitalIn[i];
    int v = digitalRead(digitalPin);
    Serial.print(v == 0 ? 1 : 0);
  }
  Serial.println();

  for (int c = 0; c < pwmCount; c++) {
    int digitalPin = pwm[c];
    analogWrite(digitalPin, brightness);
  }

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(30);
}
