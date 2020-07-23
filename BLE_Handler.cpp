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


#include "BLE_Handler.h"

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic brightnessCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEByteCharacteristic scrollingCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEStringCharacteristic textCharacteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite,20);

extern int brightness ;
extern bool power;
extern bool turnOnText;
extern bool turnOffText;
extern bool scrolling;
extern String scrollingText;
void BLE_Initialize(){
  
  pinMode(ledPin, OUTPUT);
  
  if (!BLE.begin()) 
    Sprintln("starting BLE failed!");
  
  BLE.setLocalName("CLIP-ON MOVE-ON");
  BLE.setAdvertisedService(ledService);
  
  ledService.addCharacteristic(switchCharacteristic);
  ledService.addCharacteristic(brightnessCharacteristic);
  ledService.addCharacteristic(scrollingCharacteristic);
  ledService.addCharacteristic(textCharacteristic);
  BLE.addService(ledService);

  switchCharacteristic.writeValue(0);
  brightnessCharacteristic.writeValue(0);
  scrollingCharacteristic.writeValue(0);
  BLE.advertise();

  Sprintln("Clip-ON Move-ON Availabe to Connect");
  }

void BLE_Routine(){
  
  BLEDevice central = BLE.central();
   yield();
  if (central) {
  Sprint("Connected to Device: ");
//  Serial.println("Test");
  Sprintln(central.address());

  while (central.connected()) {
    if (switchCharacteristic.written()) {
      if (switchCharacteristic.value()) {   // any value other than 0
        Sprintln("POWER ON");
        power = true;
        turnOnText =  true;
        digitalWrite(ledPin, HIGH);         // will turn the LED on
      } else {                              // a 0 value
        Sprintln(F("POWER OFF"));
        power = false;
        turnOffText =  true;
        digitalWrite(ledPin, LOW);          // will turn the LED off
      }
    }

    if (brightnessCharacteristic.written()) {
      brightness = brightnessCharacteristic.value();
      Sprintln(brightness);
    }

    if (scrollingCharacteristic.written()) {
      scrolling = scrollingCharacteristic.value();
      Sprintln(scrolling);
    }

    if (textCharacteristic.written()) {
      scrollingText = textCharacteristic.value();
      Sprintln(scrollingText);
    }
    yield();
  }


  Sprint(F("Disconnected from central: "));
  Sprintln(central.address());
  yield();
}
  }  
