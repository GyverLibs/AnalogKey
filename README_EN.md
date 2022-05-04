This is an automatic translation, may be incorrect in some places. See sources and examples!

#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0% B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square )](https://alexgyver.ru/support_alex/)

[![Foo](https://img.shields.io/badge/README-ENGLISH-brightgreen.svg?style=for-the-badge)](https://github-com.translate.goog/GyverLibs/ AnalogKey?_x_tr_sl=ru&_x_tr_tl=en)

# AnalogKey
Analog Keyboard Library for Arduino
- Built-in simple debounce
- Optimal pin polling by timer- Checking a specific button or displaying the number pressed

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **AnalogKey** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/AnalogKey/archive/refs/heads/main.zip) .zip archive for manual installation:- Extract and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
AnalogKey<A0, 16> keys; // specify the pin and the number of buttonsAnalogKey<A0, 16, signals> keys; // specify the pin, the number of buttons and the external array of signals
```

<a id="usage"></a>
## Usage
```cpp
void attach(uint8_t num, int value); // connects the button to the specified value
void setWindow(int window); // sets signal window (default 40)
bool status(uint8_tnum); // returns the status of the specified button
int pressed(); // prints the number of the pressed button or -1 if there are no buttons pressed```
### How to work
- Measure and record signals from the keyboard (for example, output values ​​to the port monitor)
- Pass values ​​to the library:
    - Put in an external array and pass it during initialization (see example)
    - Connect each button via attach (see example)
- If necessary, adjust the window size so that the signals from the buttons do not intersect: the distance between adjacent signals must be at least half the window
- This library allows you to simply find the pressed button. For advanced work (clicks, holds) use the [EncButton] library (https://github.com/GyverLibs/EncButton) in virtual mode

<a id="example"></a>## Example
### External array
```cpp
#include "AnalogKey.h"
// create an array of button signal values
int16_t sigs[16] = {
  1023, 927, 856, 783,
  671, 632, 590, 560,
  504, 480, 455, 440,
  399, 319, 255, 230};

// specify the pin, the number of buttons and the array of values
AnalogKey<A0, 16, sigs> keys;

void setup() {
  Serial.begin(9600);

  // the size of the polling window is such that the buttons do not intersect
  // The distance between adjacent signals is not less than half the window!cranberry keys.setWindow(30);
}

void loop() {
  // check each button manually
  if (keys.status(0)) Serial.println("press 0");
  if (keys.status(1)) Serial.println("press 1");
  if (keys.status(2)) Serial.println("press 2");
  if (keys.status(3)) Serial.println("press 3");
  if (keys.status(4)) Serial.println("press 4");if (keys.status(5)) Serial.println("press 5");
  if (keys.status(6)) Serial.println("press 6");

  // or display the number of the currently pressed one (-1 means none is pressed)
  if (keys.pressed() != -1) Serial.println(keys.pressed());
  delay(10);
}
```

### Internal array```cpp
#include "AnalogKey.h"
// specify the pin and the number of buttons
AnalogKey<A0, 16> keys;

void setup() {
  Serial.begin(9600);
  
  // assign buttons their signals
  keys.attach(0, 1023);cranberry keys.attach(1, 927);
  keys.attach(2, 856);
  keys.attach(3, 783);
  keys.attach(4, 671);
  keys.attach(5, 632);
  keys.attach(6, 590);
  keys.attach(7, 560);
  keys.attach(8, 504);
  keys.attach(9, 480);
  keys.attach(10, 455);cranberry keys.attach(11, 440);
  keys.attach(12, 399);
  keys.attach(13, 319);
  keys.attach(14, 255);
  keys.attach(15, 230);
}

void loop() {
  // check each button manually
  if (keys.status(0)) Serial.println("press 0");if (keys.status(1)) Serial.println("press 1");
  if (keys.status(2)) Serial.println("press 2");
  if (keys.status(3)) Serial.println("press 3");
  if (keys.status(4)) Serial.println("press 4");
  if (keys.status(5)) Serial.println("press 5");
  if (keys.status(6)) Serial.println("press 6");

  // or display the number of the currently pressed one (-1 means none is pressed)
  if (keys.pressed() != -1) Serial.println(keys.pressed());
  delay(10);}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - optimization, window size logic changed

<a id="feedback"></a>
## Bugs and feedbackWhen you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!