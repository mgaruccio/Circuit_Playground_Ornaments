# Circuit Playground Ornaments
This sketch allows for a slideshow to play on a circuit playground device with attached TFT Gizmo
Allow plays a version of Jingle Bells when either button is pushed
Tested using Circuit Playground Bluefruit but should also work with the express

## Setup
In order to store pictures on the device the filesystem must be formatted.  The easiest way to accomplish this is to [install CircuitPython](https://learn.adafruit.com/adafruit-circuit-playground-bluefruit/circuitpython) on the device and then immediate re-flash with the code in this sketch

Once the filesystem is set up and the sketch is on the device it should show up as a USB flash drive when plugged into a computer, at this point you just need to place your picture on the device.  the TFT gizmo requires 240x240 bitmaps with 16 bit color, and will generate an error if there are incorrect file types.

## 3D printing
adafruit supplies STL files for a very attractive ornament case, but it seems to have a compatibility issue between the bluefruit and TFT gizmo, which require all 10 screws inserted rather than the 8 supported by the cases.  To work around this an alternate file should be printed for the bottom part of the case

ornament - https://www.thingiverse.com/thing:4019946
alt bottom - https://www.thingiverse.com/thing:4192124

## Purchase Links
TFT Gizmo - https://www.adafruit.com/product/4367
Circuit Playground Bluefruit - https://www.adafruit.com/product/4333