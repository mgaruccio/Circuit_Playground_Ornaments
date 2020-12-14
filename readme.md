# Circuit Playground Ornaments
This sketch allows for a slideshow to play on a circuit playground device with attached TFT Gizmo
Allow plays a version of Jingle Bells when either button is pushed
Tested using Circuit Playground Bluefruit but should also work with the express

## Setup
In order to store pictures on the device the filesystem must be formatted.  The easiest way to accomplish this is to [install CircuitPython](https://learn.adafruit.com/adafruit-circuit-playground-bluefruit/circuitpython) on the device and then immediate re-flash with the code in this sketch

Once the filesystem is set up and the sketch is on the device it should show up as a USB flash drive when plugged into a computer, at this point you just need to place your picture on the device.  the TFT gizmo requires 240x240 bitmaps with 16 bit color, and will generate an error if there are incorrect file types.

TFT Gizmo - https://www.adafruit.com/product/4367
Circuit Playground Bluefruit - https://www.adafruit.com/product/4333