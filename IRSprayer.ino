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
 
#include <Time.h>
 
int motorPin = 3;                // choose the pin for the Motor
int inputPirPin = 2;              // choose the input pin (for PIR sensor)
int boardLED = 13;               //Debug
int pirState;                    // we start, assuming no motion detected
int statusVal = 0;               // variable for reading the pin status
time_t time = 0;
int endTime = 10;


int delayTime = 10;

boolean isSpraying = false;
boolean hasDelayed = false;
 
void setup() {
  pinMode(motorPin, OUTPUT);      // Declare Motor as Output
  pinMode(inputPirPin, INPUT);     // Declare PIR Input
  Serial.begin(9600);
  
}
 
void loop(){
  statusVal = digitalRead(inputPirPin);  // read input value
  if (statusVal == HIGH && isSpraying == false) {            // check if the input is HIGH
      startSpray(time);
    }
  else {
    stopSpray();
  }
}

void stopSpray(){
  isSpraying = false;
  digitalWrite(motorPin, LOW); // turn LED OFF
    /*if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }*/
}

void startSpray(int time_t){
  time = now();
  isSpraying = true;
  digitalWrite(motorPin, HIGH);
  
    // Turn Motor On
    /*if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;*/
}
