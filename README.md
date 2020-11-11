# arduino_ci and Unit Tests for a Sketch

## Video

You can watch a [video](https://youtu.be/vaS4AU_PXQo) showing how this project can be used.

## Automated Testing

Any serious software project should have good tests and much work has been done to automate that process. One challenging area for testing is low-level devices, such as an [Arduino](https://www.arduino.cc/), whose primary action is setting lines to high or low voltage. One project that seems to be doing a good job of filling this gap is [arduino_ci](https://github.com/ianfixes/arduino_ci). In this project we provide a sample Arduino program with automated tests.

 &nbsp;            | Linux | macOS | Windows
-------------------|:------|:------|:--------
**AppVeyor**       |       |       | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/2m0y9wsawprq3i3p?svg=true)](https://ci.appveyor.com/project/prestoncarman/blink)
**CircleCI**       | [![Linux Build Status](https://circleci.com/gh/prestoncarman/Blink/tree/2020-11-10_ci.svg?style=svg)](https://app.circleci.com/pipelines/github/prestoncarman/Blink)
 | |
**GitHub Actions** | ![Linux Build Status](https://github.com/prestoncarman/Blink/workflows/Arduino%20CI/badge.svg) | ![Linux Build Status](https://github.com/prestoncarman/Blink/workflows/Arduino%20CI/badge.svg) | ![Linux Build Status](https://github.com/prestoncarman/Blink/workflows/Arduino%20CI/badge.svg) 
**Travis CI**      | [![Linux Build Status](https://ci.appveyor.com/api/projects/status/2m0y9wsawprq3i3p?svg=true)](https://ci.appveyor.com/project/prestoncarman/blink) | |


## Blink

One of the initial Arduino tutorials is [Blink](https://www.arduino.cc/en/Tutorial/Blink), a program that simply turns an LED on and off for one second each. It is a nice demo that doesn't require any external devices and can be written in a few lines of code.

## Sketch

An Arduino Sketch is a program written in the Arduino IDE. It is based on C++, but has a different extension (`.ino`). A sketch has two public methods, `setup()`, which is called once when the board is powered on or reset, and `loop()`, which is called repeatedly after the setup process finishes. 

Some of the confusion (for me, at least) about how to test a sketch is that it isn't technically C/C++ and isn't (typcally) edited in a traditional IDE. But the Arduino IDE does allow C/C++ code to be referenced by a sketch, and such code is called a _library_. 

## Library

Although a [library](https://www.arduino.cc/en/main/libraries) is described in the [glossary](https://www.arduino.cc/glossary/en/) as "a software extension of the Arduino API that expands the functionality of a program," it is basically C/C++ code that can be called from a sketch. In fact, there isn't any reason you can't write essentially your entire program as a library (and even reference other libraries as needed). Consider the [original blink sketch](https://www.arduino.cc/en/Tutorial/Blink):

```
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
```

The basic sketch could be replaced with the [following](examples/Blink/Blink.ino): 

```
#include "Blink.h"
Blink blink;

void setup() {
    blink.setup();
}

void loop() {
  blink.loop();
}
```

Then, given a library with [Blink.h](blink.h) and [Blink.cpp](Blink.cpp), we have the equivalent functionality but now the program itself is essentially all in C/C++ and we can run it somewhere other than on an Arduino.

## [arduino_ci](https://github.com/ianfixes/arduino_ci)

The ArduinoCI Ruby gem "is a cross-platform build/test system, consisting of a Ruby gem and a series of C++ mocks. It enables tests to be run both locally and as part of a CI service like Travis or Appveyor. Any OS that can run the Arduino IDE can run `arduino_ci` ([cite](https://github.com/ianfixes/arduino_ci)). But, it "can only really work on an arduino library, not an arduino sketch. So if you factor your code into classes such that the standard arduino functions like setup() and loop() are just thin wrappers around library functions" then you can run tests on it ([cite](https://github.com/ianfixes/arduino_ci/issues/139#issuecomment-613164740)).

To actually see this work, do the following:
  * copy this project (simply download the zip unless you want to fork it and contribute!) into your Arduino `libraries` directory (`~/Documents/Arduino/libraries/` on macOS)
  * copy `Blink/` from `examples/` to your Arduino projects directory (`~/Documents/Arduino/` on macOS)
  * open the sketch in the Arduino IDE and try it out
  * open a command shell in the library directory and execute the following:

  ```
  bundle install --path vendor/bundle
  bundle exec arduino_ci_remote.rb
  ```

With that you should have an application that works and has automated tests.

### Example CI Configs

In this repo, the Arduino-CI is used to run the test suite through several CI vendors.
The example code for each vendor is found in the following files:

* AppVeyor - `.appveyor.yml`
* Circle CI - `.circleci/config.yml`
* GitHub Actions - `.github/workflows/Arduino-CI.yaml`
* Travis CI - `.travis.yml`

## Credits

This Arduino example was created in September 2020 by James Foster <arduino@jgfoster.net>.
