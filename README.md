# RGBright
Full RGB-enabled wifi-controlled desk lamp

This project was designed and built to use as a desk/side table lamp as well as a practical light when filming or taking photos.

All of the parts were designed in Fusion 360 and then 3D printed on the Prusa MK3S. The bottom cover and the main housing were printed in black PLA while the transparent top cover was printed in PETG so it had a higher tolerance to heat, in case the LEDs got warm at all.
  base_cover.stl - PLA
  base.stl - PLA
  cover.stl - PETG

For the electronics, an ESP32 was used as the controller for the LED lights, which were Neopixels from Adafruit. Using the Blynk API, the ESP32 was able to communicate with an iPhone in order to control the lamp's on/off status, the color of the LEDs, and the brightness of the LEDs.

There were a couple of issues when using the Adafruit library with the ESP32, the LEDs would flicker and not hold a single color. So, the Neopixelbus library was used instead, and this fixed all of the issues with the flickering.

Once the code was tested and working using the Blynk connection to the lamp, a Raspberry Pi was setup as a Homebridge server with the Homenridge-Blynk plugin installed. This allowed for the ESP32 to communicate with the Raspberry Pi, which owuld communicate with the Apple HomeKit API. Through this connection, the lamp could be controlled using the Home app on iOS as well as Siri.
