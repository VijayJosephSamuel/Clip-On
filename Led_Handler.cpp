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


#include "Led_Handler.h"

int cross = 2;
extern int brightness = 1;
extern bool power = false;
extern bool turnOnText = false;
extern bool turnOffText = false;
extern bool scrolling = false;
extern String scrollingText = "Wear Mask";
//char textToScroll;
extern int distance;
extern int prev_distance;
extern int led_sequence = 0;
static uint8_t pixmap_count = ((mw+7)/8) * ((mh+7)/8);
bool ledOn = false;

Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, MATRIX_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(0, 0, 255) };

int x    = matrix->width();
int pass = 0;  
void LED_Initialize(){
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(brightness);
  matrix->setTextColor(colors[0]);
  }

void LED_Routine(){
  yield();
//  display_scrollText("VIJAY");


  
  if(turnOffText){
    
    Sprintln("SHUTDOWN SMILEY");
    display_bitmap(14, LED_GREEN_HIGH);
    delay(2000); 
    matrix->fillScreen(LED_BLACK);
    matrix->show();
    turnOffText = false;
    }  
    
  if(power){

   if(!scrolling){
      if(ledOn){
        ledOn = false;
        matrix->fillScreen(LED_BLACK);
        matrix->show();
        }

    }
   if(scrolling){
//      const char* disp = scrollingText.c_str();
      char *s2 = new char[scrollingText.length()+1];
      strcpy(s2, scrollingText.c_str());
      ledOn = true;
      display_scrollText(s2);
      yield();
   }
  if(turnOnText){
    Sprintln("STARTUP SMILEY");
    display_bitmap(12, LED_BLUE_HIGH);
    delay(2000); 
    matrix->fillScreen(LED_BLACK);
    matrix->show();
    turnOnText = false;
    }  
  
  if(led_sequence == 1){
  matrix->setBrightness(brightness);
  Serial.println(led_sequence);

      
  for(int i=0;i<cross;i++){
    Sprintln("Displaying Red Cross");
    ledOn = true;
    display_bitmap(8,LED_RED_HIGH);
    delay(200);
    matrix->fillScreen(LED_BLACK);
    matrix->show();
    delay(200);
    }
      
  while(distance < 1500){
    Sprintln("Displaying Green Arrow");
    for (uint8_t i=0; i<8; i++){
      display_bitmap(i, LED_GREEN_HIGH);
      delay(100);
      
      }
  ledOn = true;

    }
  Sprintln("Displaying Heart");
  display_bitmap(9, LED_PURPLE_HIGH);
  delay(1000); 
  led_sequence = 0;
  matrix->fillScreen(LED_BLACK);
  matrix->show();
    }

  if(led_sequence == 0 ){
    if(ledOn == true){
    matrix->fillScreen(LED_BLACK);
    matrix->show();
    ledOn = false;
    yield();
    }
    }

    }
  }


void display_bitmap(uint8_t bmp_num, uint16_t color) { 
  static uint16_t bmx,bmy;

  // Clear the space under the bitmap that will be drawn as
  // drawing a single color pixmap does not write over pixels
  // that are nul, and leaves the data that was underneath
  matrix->fillRect(bmx,bmy, bmx+8,bmy+8, LED_BLACK);
  matrix->drawBitmap(bmx, bmy, mono_bmp[bmp_num], 8, 8, color);
  bmx += 8;
  if (bmx >= mw) bmx = 0;
  if (!bmx) bmy += 8;
  if (bmy >= mh) bmy = 0;
  matrix->show();
}

void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    uint16_t RGB_bmp_fixed[w * h];
    for (uint16_t pixel=0; pixel<w*h; pixel++) {
  uint8_t r,g,b;
  uint16_t color = pgm_read_word(bitmap + pixel);

  //Serial.print(color, HEX);
  b = (color & 0xF00) >> 8;
  g = (color & 0x0F0) >> 4;
  r = color & 0x00F;
  //Serial.print(" ");
  //Serial.print(b);
  //Serial.print("/");
  //Serial.print(g);
  //Serial.print("/");
  //Serial.print(r);
  //Serial.print(" -> ");
  // expand from 4/4/4 bits per color to 5/6/5
  b = map(b, 0, 15, 0, 31);
  g = map(g, 0, 15, 0, 63);
  r = map(r, 0, 15, 0, 31);
  //Serial.print(r);
  //Serial.print("/");
  //Serial.print(g);
  //Serial.print("/");
  //Serial.print(b);
  RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
  //Serial.print(" -> ");
  //Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}

void display_scrollText(char* text1){
  matrix->fillScreen(0);
  matrix->setCursor(x, 0);
  matrix->print(F(text1));
  if(--x < -36) {
    x = matrix->width();
    if(++pass >= 3) pass = 0;
//    matrix->setTextColor(colors[pass]);
  }
  matrix->show();
  delay(100);
  }
