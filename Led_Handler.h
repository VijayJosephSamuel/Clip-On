/*
 * Clip-ON Move-ON
 * Copyright (C) 2020 Vijay J Samuel.  All Rights Reserved.
 *
 * Author: Vijay J Samuel
 * Email: vijayjoseph.official@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#ifndef _LED_HANDLER_H_
#define _LED_HANDLER_H_

#include <Arduino.h>
#include <Scheduler.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "Sprint.h"

#define MATRIX_PIN 7

//#define BRIGHTNESS 1

#define mw 8
#define mh 8


#define LED_BLACK    0

#define LED_RED_VERYLOW   (3 <<  11)
#define LED_RED_LOW     (7 <<  11)
#define LED_RED_MEDIUM    (15 << 11)
#define LED_RED_HIGH    (31 << 11)

#define LED_GREEN_VERYLOW (1 <<  5)   
#define LED_GREEN_LOW     (15 << 5)  
#define LED_GREEN_MEDIUM  (31 << 5)  
#define LED_GREEN_HIGH    (63 << 5)  

#define LED_BLUE_VERYLOW  3
#define LED_BLUE_LOW    7
#define LED_BLUE_MEDIUM   15
#define LED_BLUE_HIGH     31

#define LED_ORANGE_VERYLOW  (LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW    (LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM (LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH   (LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW  (LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW    (LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM (LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH   (LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW  (LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW    (LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM   (LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH   (LED_GREEN_HIGH    + LED_BLUE_HIGH)


#define LED_WHITE_VERYLOW (LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW   (LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM  (LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH    (LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)






static const uint8_t PROGMEM
    mono_bmp[][8] =
    {

      {
      B00011000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,           
      B00000000,  
      B00000000,
      
                      },

      {
      
      B00111100,
      B00011000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,           
      B00000000,  
      B00000000,

                      },

      {
      B01111110,  
      B00111100,
      B00011000,  
      B00000000,
      B00000000,
      B00000000,           
      B00000000,  
      B00000000,     
                  },

      {
      B11111111,
      B01111110,
      B00111100,
      B00011000,  
      B00000000,
      B00000000,           
      B00000000,  
      B00000000,
                      },

      {
      B00011000,
      B11111111,
      B01111110,
      B00111100,
      B00011000,
      B00000000,           
      B00000000,  
      B00000000,
            },
 {   
      B00011000,
      B00011000,
      B11111111,
      B01111110,
      B00111100,
      B00011000,
      B00000000,  
      B00000000,
            },


        {   
      B00011000,
      B00011000,
      B00011000,
      B11111111,
      B01111110,
      B00111100,
      B00011000,
      B00000000,
      
            },
            
  {   
      B00011000,
      B00011000,
      B00011000,
      B00011000,
      B11111111,
      B01111110,
      B00111100,
      B00011000,
       },


{
      B11000001,
      B11100111,
      B01111110,
      B00111100,
      B00111100,           
      B01111110,  
      B11100111,
      B11000011,
                      },

                      {
      B00000000,
      B01100110,
      B11111111,
      B11111111,
      B01111110,           
      B00111100,  
      B00011000,
      B00000000,
                      },
                      
  {   // 1: checkered 2
      B00000000,
      B00111000,
      B00100010,
      B10000010,
      B01000001,
      B10000010,
      B00100010,
      B00111000,
      },

      {   // 1: checkered 2
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00010000,
      B00000000,
      B00000000,
      B00000000,
      },

  {   // 2: smiley
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10100101,
      B10011001,
      B01000010,
      B00111100 },

  {   // 3: neutral
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10111101,
      B10000001,
      B01000010,
      B00111100 },

  {   // 4; frowny
      B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10011001,
      B10100101,
      B01000010,
      B00111100 },
    };



void display_bitmap (uint8_t bmp_num, uint16_t color);
void display_rgbBitmap (uint8_t bmp_num);
void fixdrawRGBBitmap (int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) ;
void LED_Initialize ();
void LED_Routine ();
void display_scrollText(char* text1);

#endif
