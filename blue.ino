/*
  Arc Reactor

  This sketch provides the basis for an AdaFruit Circuit Playground based Iron Man Arc Reactor.
  It uses a stock AdaFuits Circuit Playground Classic board.
  It starts all of the LED lights in the ring on solid blue, low brightness
  Tapping the board will cause the brightness to increase until max, then reset to lowest setting
  Flipping the switch on the board to the right will turn off the LEDs and reset the brightness to the lowest setting
  Flipping the switch on the board to the left will turn on the LEDs at lowest brightness setting

  Created 15 October 2017
  By Bandwidthninja
  Modified 15 October 2017
  By Bandwidthninja
  https://github.com/bandwidthninja/AdaFruitCircuitPlayground

*/

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>
#include <Wire.h>
#include <SPI.h>

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 60
// variable used to adjust the LED brightness
uint16_t BRIGHTNESS = 5;

void setup() {
  //while (!Serial);
  Serial.begin(9600);
  CircuitPlayground.begin();

  // set the accelerometer's sensitivity, mode single click
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD);

  // have a procedure called when a tap is detected
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), tapTime, FALLING);
}

void tapTime(void) {
  // increase brightness by 50 unless at max, then reset to minimum
  if (BRIGHTNESS == 255) {
    Serial.println("Set brightness 5");
    CircuitPlayground.setBrightness(5);
    BRIGHTNESS = 5;
    Serial.print(BRIGHTNESS);
  } else {
    Serial.println("Set brightness 255");
    CircuitPlayground.setBrightness(BRIGHTNESS + 50);
    BRIGHTNESS = BRIGHTNESS + 50;
    Serial.print(BRIGHTNESS);
  }
}

void loop() {
  // disable Red #13 LED
  CircuitPlayground.redLED(LOW);
  // add delay time to loop
  delay(1000);
  // if Slide Switch set Left - set all NeoPixel LEDs to Blue
  // else it is set right, turn off all NeoPixel LEDs
  if (CircuitPlayground.slideSwitch()) {
    Serial.println("Slide to the left");
    // set all NeoPixel LEDs to blue
    CircuitPlayground.setPixelColor(0, 0, 0, 255);
    CircuitPlayground.setPixelColor(1, 0, 0, 255);
    CircuitPlayground.setPixelColor(2, 0, 0, 255);
    CircuitPlayground.setPixelColor(3, 0, 0, 255);
    CircuitPlayground.setPixelColor(4, 0, 0, 255);
    CircuitPlayground.setPixelColor(5, 0, 0, 255);
    CircuitPlayground.setPixelColor(6, 0, 0, 255);
    CircuitPlayground.setPixelColor(7, 0, 0, 255);
    CircuitPlayground.setPixelColor(8, 0, 0, 255);
    CircuitPlayground.setPixelColor(9, 0, 0, 255);
  } else {
    Serial.println("Slide to the right");
    CircuitPlayground.clearPixels();
    CircuitPlayground.setBrightness(5);
    BRIGHTNESS = 5;
  }

}
