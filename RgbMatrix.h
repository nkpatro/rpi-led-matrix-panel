// Copyright (c) 2013 Matt Hill
// Use of this source code is governed by The MIT License
// that can be found in the LICENSE file.

// This class is for controlling a 32x32 RGB LED Matrix panel using
// the Raspberry Pi GPIO.
//
// Buy a 32x32 RGB LED Matrix from Adafruit!
//   http://www.adafruit.com/products/607
//
// For different sizes of RGB LED Matrix, change the contants in this file.
//
// The 32x32 panels can also be chained together to make larger panels.
// When daisy-chaining multiple boards in a square (like four 32x32 boards
// for a 64x64 matrix), columns 1 to 64 are Left to Right across the top two
// boards, but columns 65 to 127 are backwards Right to Left across the bottom
// two boards. (Referenced by: ColumnCnt)
//
 
#ifndef RPI_RGBMATRIX_H
#define RPI_RGBMATRIX_H

#include <stdint.h>
#include "GpioProxy.h"


class RgbMatrix
{
 public:

  // Width and Height of the RBG Matrix.
  // If chaining multiple boards together, this is the overall Width x Height.
  static const int Width = 32;
  static const int Height = 32;

  // The 32x32 RGB Matrix is broken into two 16x32 sub-panels. 
  static const int RowsPerSubPanel = 16;
  static const int ColsPerSubPanel = 32;

  // Number of Daisy-Chained Boards
  static const int ChainedBoardsCnt = 1;

  // Number of Columns
  static const int ColumnCnt = ChainedBoardsCnt * ColsPerSubPanel;

  // Pulse Width Modulation (PWM) Resolution 
  static const int PwmResolution = 4;

 
  RgbMatrix(GpioProxy *io);

  void clearDisplay();

  // Call this in a loop to keep the matrix updated. 
  void updateDisplay();


  //Drawing functions
  void drawPixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);

  void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
                uint8_t red, uint8_t green, uint8_t blue);

  void drawVLine(uint8_t x, uint8_t y, uint8_t h,
                 uint8_t red, uint8_t green, uint8_t blue);

  void drawHLine(uint8_t x, uint8_t y, uint8_t w,
                 uint8_t red, uint8_t green, uint8_t blue);

  void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                uint8_t red, uint8_t green, uint8_t blue);

  void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                uint8_t red, uint8_t green, uint8_t blue);

  void fillScreen(uint8_t red, uint8_t green, uint8_t blue);

  void drawRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r,
                     uint8_t red, uint8_t green, uint8_t blue);

  void fillRoundRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t r,
                     uint8_t red, uint8_t green, uint8_t blue);
  
  void drawCircle(uint8_t x, uint8_t y, uint8_t r,
                  uint8_t red, uint8_t green, uint8_t blue);

  // Draw one of the four quadrants of a cirle.
  //   quadrant = 1 : Upper Left
  //            = 2 : Upper Right
  //            = 4 : Lower Right
  //            = 8 : Lower Left
  void drawCircleQuadrant(uint8_t x, uint8_t y, uint8_t r, uint8_t quadrant,
                          uint8_t red, uint8_t green, uint8_t blue);

  void fillCircle(uint8_t x, uint8_t y, uint8_t r,
                  uint8_t red, uint8_t green, uint8_t blue);

  // Fill one half of a cirle.
  //   half = 1 : Left
  //        = 2 : Right
  //        = 3 : Both
  //   stretch = number of pixels to stretch the circle vertically.
  void fillCircleHalf(uint8_t x, uint8_t y, uint8_t r,
                      uint8_t half, uint8_t stretch,
                      uint8_t red, uint8_t green, uint8_t blue);
 
private:
  GpioProxy *const _gpio;


  // The following data structure represents the pins on the Raspberry Pi GPIO.
  // Each RGB LED Panel requires writing to 2 LED's at a time, so the data
  // structure represents 2 pixels on an RGB LED matrix. The data structure maps
  // the GPIO pins to the LED matrix contols.
  //
  // The GPIO pins are mapped to the LED Matrix as follows:
  //
  //   GPIO 2 (SDA)       -->  OE (Output Enabled)
  //   GPIO 3 (SCL)       -->  CLK (Serial Clock)
  //   GPIO 4 (GPCLK0)    -->  LAT (Data Latch)
  //   GPIO 7 (CE1)       -->  A  --|
  //   GPIO 8 (CE0)       -->  B    |   Row
  //   GPIO 9 (MISO)      -->  C    | Address
  //   GPIO 10 (MOSI)     -->  D  --|
  //   GPIO 17            -->  R1 (LED 1: Red)
  //   GPIO 18 (PCM_CLK)  -->  G1 (LED 1: Green)
  //   GPIO 22            -->  B1 (LED 1: Blue)
  //   GPIO 23            -->  R2 (LED 2: Red)
  //   GPIO 24            -->  G2 (LED 2: Green)
  //   GPIO 25            -->  B2 (LED 2: Blue)
  //
  union GpioPins {
    struct {
      unsigned int ignoredPins1:2;   // 0,1
      unsigned int outputEnabled:1;  // 2
      unsigned int clock:1;          // 3
      unsigned int latch:1;          // 4
      unsigned int ingoredPins2:2;   // 5,6
      unsigned int rowAddress:4;     // 7-10
      unsigned int ignoredPins3:6;   // 11-16
      unsigned int r1:1;             // 17
      unsigned int g1:1;             // 18
      unsigned int ignoredPins4:3;   // 19-21
      unsigned int b1:1;             // 22
      unsigned int r2:1;             // 23
      unsigned int g2:1;             // 24
      unsigned int b2:1;             // 25
    } bits;
    uint32_t raw;
    GpioPins() : raw(0) {}
  };


  // Because a 32x32 Panel is composed of two 16x32 sub-panels, and each
  // 32x32 Panel requires writing an LED from each sub-panel at a time, the
  // following data structure represents two rows: n and n+16.
  struct TwoRows {
    GpioPins column[ColumnCnt];  //TODO: Does this only use color bits???
  };

  struct Display {
    TwoRows row[RowsPerSubPanel];
  };

  Display _plane[PwmResolution];

};

#endif  // RPI_RGBMATRIX_H
