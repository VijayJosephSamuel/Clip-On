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


 
#include <Scheduler.h>
#include "BLE_Handler.h"
#include "Led_Handler.h"
#include "Lidar_Handler.h"
#include "Sprint.h"



void setup() {
  // put your setup code here, to run once:

  BLE_Initialize();
  LED_Initialize();
  LIDAR_Initialize();
  
  Serial.begin(115200);
  Scheduler.startLoop(BLE_Routine);
  Scheduler.startLoop(LED_Routine);
  Scheduler.startLoop(LIDAR_Routine);
}

void loop() {
  // put your main code here, to run repeatedly:
  yield();
}
