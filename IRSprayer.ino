/*

    This code is meant for FIT Student Zhenwei Xie's final thesis.
    It controls an arduino with a PIR sensor and activates a motor 

    Copyright (C) 2013  Nick Steele (@GrandSt)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//This uses the Timer Library from http://www.doctormonk.com/2012/01/arduino-timer-library.html 
 

#include <Time.h>  
#include <Event.h>
#include <Timer.h>


int motorPin = 3;                // choose the pin for the Motor //Default 3
int inputPirPin = 2; // choose the input pin (for PIR sensor)
int boardLED = 13;            //Debug
int pirState;                    // we start, assuming no motion detected
int statusVal = 0;               // variable for reading the pin status
time_t time = 0;

int delayTime = 10;

boolean isSpraying = false;
boolean sprayDowntime = false;

Timer t;

int initialEvent;
int duringEvent;
int afterEvent;

void setup() {
  Serial.begin(9600);
  
  pinMode(motorPin, OUTPUT);      // Declare Motor as Output
  
  pinMode(inputPirPin, INPUT);     // Declare PIR Input
  
  //Serial.println("PIR Sensor Online");
  
  int initialEvent = t.every(700, checkSensor);
}

void loop(){
  t.update();
}

void checkSensor(){
  statusVal = digitalRead(inputPirPin);
  if(statusVal == HIGH && isSpraying == false && sprayDowntime == false){
    //Serial.println("Should now work!");
    startSpray();
  }
  else{
    //Serial.println("Should not work");
  }
}
  
void stopSpray(){
  isSpraying = false;
  sprayDowntime = true; //Begin sprayer downtime
  digitalWrite(motorPin, LOW); // turn Sprayer OFF
  //Serial.println("Motor should rest now");
  t.after(10000, resetDowntime);
}

void startSpray(){
  isSpraying = true;
  digitalWrite(motorPin, HIGH);
  t.after(7000, stopSpray);
}

void resetDowntime(){
  sprayDowntime = false; //No longer sprayer downtime
  //Serial.println("I should work again now");
}
