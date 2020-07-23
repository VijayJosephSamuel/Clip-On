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


#include "Lidar_Handler.h"

SFEVL53L1X distanceSensor;

extern int distance = 0;
extern int prev_distance = 0;
extern int power;
extern int led_sequence;

void LIDAR_Initialize(){
  
  Wire.begin();

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Sprintln("TOF Sensor failed to begin. Please check wiring. Freezing...");

  }
  ("TOF Sensor online!");
  }

void LIDAR_Routine(){
  yield();
  if(power){
  prev_distance = distance;
  distanceSensor.startRanging(); //Write configuration block of 135 bytes to setup a measurement
  while (!distanceSensor.checkForDataReady())
  {
    delay(1);
  }
  distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
  distanceSensor.clearInterrupt();
  distanceSensor.stopRanging();


  if(signalStatus()){

//  Sprint("Distance(mm): ");
//  Sprint (distance);


  int slope = distance - prev_distance;

//  Sprint("\tSlope: ");
//  Sprint(slope);

  
  }

  else{
    Sprint("Signal Fail");
    }
  
//  Sprintln();
  if(distance < 1500) {
    led_sequence = 1;
//    Sprintln("             Loop Entered");
    }

  if(distance > 1500) {
    led_sequence = 0;
//    Sprintln("             Loop2 Entered");
    }  
  yield();
  
  }  

} 


bool signalStatus(void){
  byte rangeStatus = distanceSensor.getRangeStatus();
  if(rangeStatus == 0)
    return 1;
  else
    return 0;  
  }  
