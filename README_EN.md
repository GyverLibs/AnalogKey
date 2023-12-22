This is an automatic translation, may be incorrect in some places. See sources and examples!

# Analogy
Library for working with an analog keyboard for Arduino
- Built -in, simple debate
- Optimal PIN survey by timer
- checking a specific button or output of a pressed number

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** analogy ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/analogkey/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Analogkey <a0, 16> keys;// Specify the PIN and the number of buttons
Analogkey <a0, 16, Signals> keys;// Specify PIN, number of buttons and external array of signals
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID attach (uint8_t num, int velue);// connects the button to the specified value
VOID Setwindow (Intsdow);// sets the signal window (silence 40)
Bool Status (uint8_t num);// returns the status of the specified button
Intsed ();// displays the number of the pressed button or -1, if there are no buttons pressed
`` `
### How to work
- measure and write signals from the keyboard (for example, display values to the port monitor)
- Pass the values to the library:
    - Put in an external array and transfer it to initialization (see example)
    - connect each button via attach (see example)
- if necessary, configure the window size so that the signals from the buttons do not intersect: the distance between neighboring signals should be at least half of the window
- This library allows you to just find a pressed button.For advanced work (clique, retention), use the library [encbuton] (https://github.com/gyverlibs/encbutton) in virtual mode

<a id="EXAMPLE"> </a>
## Example
### External array
`` `CPP
#include "AnaLogkey.h"
// Create an array of signal values from buttons
int16_t sigs [16] = {{
  1023, 927, 856, 783,
  671, 632, 590, 560,
  504, 480, 455, 440,
  399, 319, 255, 230
};

// Specify PIN, number of buttons and array of values
ANALOGKEY <A0, 16, sigs> keys;

VOID setup () {
  Serial.Begin (9600);

  // The size of the survey window is so that the buttons do not intersect
  // The distance between neighboring signals is at least half the window!
  keys.setwindow (30);
}

VOID loop () {
  // Check each button in manual mode
  if (keys.status (0)) serial.println ("Press 0");
  if (keys.status (1)) serial.println ("Press 1");
  if (keys.status (2)) serial.println ("Press 2");
  if (keys.status (3)) serial.println ("Press 3");
  if (keys.status (4)) serial.println ("Press 4");
  if (keys.status (5)) serial.println ("Press 5");
  if (keys.status (6)) serial.println ("Press 6");

  // or display the number of the current pressed (-1 means not one is pressed)
  if (keys.pressed ()! = -1) serial.println (keys.pressed ());
  Delay (10);
}
`` `

### Inner array
`` `CPP
#include "AnaLogkey.h"
// Specify the PIN and the number of buttons
Analogkey <a0, 16> keys;

VOID setup () {
  Serial.Begin (9600);
  
  // assign the buttons their signals
  keys.attach (0, 1023);
  keys.attach (1, 927);
  Keys.attach (2, 856);
  keys.attach (3, 783);
  Keys.attach (4, 671);
  keys.attach (5, 632);
  Keys.attach (6, 590);
  keys.attach (7, 560);
  keys.attach (8, 504);
  keys.attach (9, 480);
  keys.attach (10, 455);
  keys.attach (11, 440);
  keys.attach (12, 399);
  Keys.attach (13, 319);
  keys.attach (14, 255);
  keys.attach (15, 230);
}

VOID loop () {
  // Check each button in manual mode
  if (keys.status (0)) serial.println ("Press 0");
  if (keys.status (1)) serial.println ("Press 1");
  if (keys.status (2)) serial.println ("Press 2");
  if (keys.status (3)) serial.println ("Press 3");
  if (keys.status (4)) serial.println ("Press 4");
  if (keys.status (5)) serial.println ("Press 5");
  if (keys.status (6)) serial.println ("Press 6");

  // or display the number of the current pressed (-1 means not one is pressed)
  if (keys.pressed ()! = -1) serial.println (keys.pressed ());
  Delay (10);
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- v1.1 - optimization, the logic of the window size has been changed

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code