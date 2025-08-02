/*
    Library for working with an analog keyboard
    GitHub: https://github.com/GyverLibs/AnalogKey
    - Built-in simple debounce
    - Optimal pin polling by timer
    - Check a specific button or output the number of the pressed button

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    v1.1 - optimization, changed the logic of window size
    v1.2 - adding a window as a percentage
*/

#ifndef _AnalogKey_h
#define _AnalogKey_h
#include <Arduino.h>

#define _AKEY_PERIOD 40   // polling period in ms
template <uint8_t PIN, uint8_t AMOUNT, int16_t* S_PTR = nullptr>
class AnalogKey {
public:
    // connects the button to the specified value
    void attach(uint8_t num, int value) {
        if (num >= AMOUNT) return;
        if (S_PTR == nullptr) signals[num] = value;
        else signals_p[num] = value;
    }

    // sets the signal window (default is 20)
    void setWindow(int window) {
        _autoWindow = !window ? true : false;
        _window = window / 2;
    }

    // returns the status of the specified button
    bool status(uint8_t num) {
        if (millis() - tmr > _AKEY_PERIOD) {
            tmr = millis();
            int16_t thisRead = analogRead(PIN);
            if (_autoWindow && thisRead != _lastRead) {
                _window = 0;
                for (uint8_t i = 0; i < AMOUNT; i++) {
                    int16_t currentSignal = (S_PTR == nullptr) ? signals[i] : signals_p[i];
                    bool currentKey = true;
                    int16_t currentWindow = 0;
                    if (i > 0) {
                        int16_t previousSignal = (S_PTR == nullptr) ? signals[i - 1] : signals_p[i - 1];
                        if (thisRead < (previousSignal + currentSignal) / 2) {
                            currentKey = false;
                        }
                        else {
                            currentWindow = (currentSignal - previousSignal) / 3;
                        }
                    }
                    if (i < AMOUNT - 1) {
                        int16_t nextSignal = (S_PTR == nullptr) ? signals[i + 1] : signals_p[i + 1];
                        if (thisRead > (currentSignal + nextSignal) / 2) {
                            currentKey = false;
                        }
                        else {
                            int16_t secondWindow = (nextSignal - currentSignal) / 3;
                            if (!currentWindow || secondWindow < currentWindow) {
                                currentWindow = secondWindow;
                            }
                        }
                    }
                    if (currentKey) {
                        _window = currentWindow;
                        break;
                    }
                }
            }
            _ready = (abs(thisRead - _lastRead) < _window);
            _lastRead = thisRead;
        }
        return check(num);
    }

    // outputs the number of the pressed button or -1 if there are no pressed buttons
    int pressed() {
        status(0);	// call polling
        for (uint8_t i = 0; i < AMOUNT; i++) {
            if (check(i)) return i;
        }
        return -1;
    }

private:
    bool check(int i) {
        int16_t sig = (S_PTR == nullptr) ? signals[i] : signals_p[i];
        return (_ready && (_lastRead > sig - _window) && (_lastRead < sig + _window));
    }

    int16_t signals[(S_PTR == nullptr) ? AMOUNT : 0];
    int16_t* signals_p = S_PTR;
    int16_t _lastRead = 0;
    bool _autoWindow = false;
    int16_t _window = 20;
    bool _ready = false;
    uint32_t tmr;
};
#endif
