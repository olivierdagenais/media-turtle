// Copyright (c) Olivier Dagenais. All rights reserved.
// Licensed under the MIT license. See LICENSE in the project root.

/*
 * A program to convert button presses to characters.
 */

class ButtonBase {
  protected:
    const char _character;
    const uint8_t _buttonPin;
    const uint8_t _ledPin;

    volatile bool _currentButtonState;
    virtual bool isPressed() = 0;

  public:
    void scan() {
        bool newState = isPressed();
        if (_currentButtonState) { // button was previously pressed
            if (!newState) {       // now it's released
                _currentButtonState = false;
                if (_ledPin != -1) {
                    analogWrite(_ledPin, 255);
                }
            }
        }
        else {              // button wasn't pressed
            if (newState) { // now it's pressed
                _currentButtonState = true;
                if (_ledPin != -1) {
                    analogWrite(_ledPin, 0);
                }
                Serial.print(_character);
            }
        }
    }

    ButtonBase(char character, uint8_t buttonPin)
        : ButtonBase(character, buttonPin, -1) {
        // defer to other constructor overload
    }

    ButtonBase(char character, uint8_t buttonPin, uint8_t ledPin)
        : _character(character), _buttonPin(buttonPin), _ledPin(ledPin) {
        _currentButtonState = false;
        if (_ledPin != -1) {
            pinMode(ledPin, OUTPUT);
            analogWrite(_ledPin, 255);
        }
    }
};

class DigitalButton : public ButtonBase {

  public:
    DigitalButton(char character, uint8_t buttonPin)
        : DigitalButton(character, buttonPin, -1) {
        // defer to other constructor overload
    }

    DigitalButton(char character, uint8_t buttonPin, uint8_t ledPin)
        : ButtonBase(character, buttonPin, ledPin) {
        pinMode(_buttonPin, INPUT_PULLUP);
    }

    virtual bool isPressed() {
        int v = digitalRead(_buttonPin);
        return (v == 0);
    }
};

class AnalogButton : public ButtonBase {

  public:
    AnalogButton(char character, uint8_t buttonPin)
        : AnalogButton(character, buttonPin, -1) {
        // defer to other constructor overload
    }

    AnalogButton(char character, uint8_t buttonPin, uint8_t ledPin)
        : ButtonBase(character, buttonPin, ledPin) {}

    virtual bool isPressed() {
        int v = analogRead(_buttonPin);
        return (v < 10);
    }
};

const int NUM_BUTTONS = 6;
ButtonBase *_buttons[NUM_BUTTONS];

void setup() {
    Serial.begin(115200);
    _buttons[0] = new DigitalButton('0', 8, 6);  // piano     -> '0'
    _buttons[1] = new DigitalButton('1', 12, 9); // drum      -> '1'
    _buttons[2] = new DigitalButton('3', 15, 5); // violon    -> '3'
    _buttons[3] = new DigitalButton('4', 7, 11); // harp      -> '4'
    _buttons[4] = new DigitalButton('5', 4, -1); // note      -> '5'
    _buttons[5] = new DigitalButton('6', 14, 3); // xylophone -> '6'
}

void loop() {
    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        _buttons[i]->scan();
    }
    delay(30);
}
