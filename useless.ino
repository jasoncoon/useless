/*
   Useless Machine: https://github.com/jasoncoon/useless
   Copyright (C) 2016 Jason Coon

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
 
// Sequences from "Moody Useless Machine" by Lamja Electronics
// http://www.lamja.com/?p=451
// http://www.lamja.com/blogfiles/UselessMachine.pde
//
// More possible sequence ideas:
// http://www.instructables.com/id/How-to-build-another-useless-machine-easy-to-make-/step8/The-code/
// https://github.com/vagelis-chantzis/UselessBox/blob/master/UselessBox.ino

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define switchPin 11
#define ledPin 13

// the default address is 0x40
Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!

// SG5010 (large) - 130 - 550 // these are the 'minimum' and 'maximum' pulse length count (out of 4096)
int armServoMin = 280; // arm fully retracted/resting
int armServoMax = 400; // switch is off
int armServoMid = 340; // a bit from the switch
int armServoMid2 = 360; // almost on the switch
int armServoNumber = 6;

// SG92R (small) - 130 - 480 // these are the 'minimum' and 'maximum' pulse length count (out of 4096)
int doorServoMin = 380; // all the way down/closed
int doorServoMax = 440; // all the way up/open
int doorServoMid = 400; // just touching the door
int doorServoMid2 = 410; // door half way open
int doorServoMid3 = 420; // door 3/4 way open
int doorServoNumber = 7;

bool isSwitchOn = false;

void setup() {
  Serial.println("Starting up");
  Serial.begin(9600);

  servoDriver.begin();
  servoDriver.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  yield();
}

void sweep(int servoNumber, int from, int to, int delayus)
{
  if (from < to)
  {
    for (int pos = from; pos < to; pos += 1)
    {
      servoDriver.setPWM(servoNumber, 0, pos);
      delayMicroseconds(delayus);
    }
  }
  else if (from > to)
  {
    for (int pos = from; pos >= to; pos -= 1)
    {
      servoDriver.setPWM(servoNumber, 0, pos);
      delayMicroseconds(delayus);
    }
  }
}

void loop() {
  static int sequence = 1; // int(random(1, 10)); // If you want random...

  int switchValue = digitalRead(switchPin);

  if (switchValue == LOW) {
    isSwitchOn = true;
    digitalWrite(ledPin, HIGH);
    Serial.println("Switched on");
  }
  else {
    isSwitchOn = false;
    digitalWrite(ledPin, LOW);
  }

  if (Serial.available()) {
    char serialData = Serial.read();

    Serial.print(serialData);

    static int v = 0;

    switch (serialData) {
      case '0'...'9':
        v = v * 10 + serialData - '0';
        break;
      case 's':
        sequence = v;
        isSwitchOn = true;
        v = 0;
        Serial.println();
        break;
      case 'd':
        if (v < doorServoMin)
          v = doorServoMin;
        else if (v > doorServoMax)
          v = doorServoMax;
        servoDriver.setPWM(doorServoNumber, 0, v);
        v = 0;
        Serial.println();
        break;
      case 'a':
        if (v < armServoMin)
          v = armServoMin;
        else if (v > armServoMax)
          v = armServoMax;
        servoDriver.setPWM(armServoNumber, 0, v);
        v = 0;
        Serial.println();
        break;
    }
  }

  if (!isSwitchOn) {
    return;
  }

  isSwitchOn = false;

  if (sequence < 1 || sequence > 10)
    return;

  Serial.print("Executing sequence ");
  Serial.println(sequence);

  if (sequence == 1) sequence1();
  if (sequence == 2) sequence2();
  if (sequence == 3) sequence3();
  if (sequence == 4) sequence4();
  if (sequence == 5) sequence5();
  if (sequence == 6) sequence6();
  if (sequence == 7) sequence7();
  if (sequence == 8) sequence8();
  if (sequence == 9) sequence9();
  if (sequence == 10) sequence10();

  sequence++;

  if (sequence > 10) sequence = 1;
}

// Sequences from "Moody Useless Machine" by Lamja Electronics
// http://www.lamja.com/?p=451
// http://www.lamja.com/blogfiles/UselessMachine.pde

void sequence1()
{
  delay(700);
  sweep(doorServoNumber, doorServoMin, doorServoMid, 3000);
  delay(1000);
  sweep(doorServoNumber, doorServoMid, doorServoMin, 500);
  delay(1000);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1000);
  sweep(armServoNumber, armServoMin, armServoMid, 1800);
  sweep(armServoNumber, armServoMid, armServoMax, 500);
  delay(100);
  sweep(armServoNumber, armServoMax, armServoMin, 500);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 500);
}

void sequence2()
{
  delay(800);
  sweep(doorServoNumber, doorServoMin, doorServoMid2, 3000);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(120);
  sweep(doorServoNumber, doorServoMid2, doorServoMin, 3000);
  sweep(doorServoNumber, doorServoMin, doorServoMid, 3000);
  delay(1000);
  sweep(doorServoNumber, doorServoMid, doorServoMax, 1000);
  sweep(armServoNumber, armServoMin, armServoMid, 1800);
  sweep(armServoNumber, armServoMid, armServoMax, 500);
  delay(100);
  sweep(armServoNumber, armServoMax, armServoMin, 500);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 500);
}

void sequence3()
{
  delay(50);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence4()
{
  delay(500);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMid2, 1);
  delay(450);
  sweep(armServoNumber, armServoMid2, armServoMax, 30000);
  delay(1);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence5()
{
  delay(1000);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(armServoNumber, armServoMax, armServoMid2, 1);
  delay(110);
  sweep(armServoNumber, armServoMid2, armServoMax, 1);
  delay(110);
  sweep(armServoNumber, armServoMax, armServoMid2, 1);
  delay(110);
  sweep(armServoNumber, armServoMid2, armServoMax, 1);
  delay(110);
  sweep(armServoNumber, armServoMax, armServoMid2, 1);
  delay(110);
  sweep(armServoNumber, armServoMid2, armServoMax, 1);
  delay(110);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence6()
{
  delay(1500);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1000);
  delay(2000);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1000);
  delay(2000);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence7()
{
  delay(500);
  sweep(doorServoNumber, doorServoMin, doorServoMid, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMid, doorServoMid2, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid2, doorServoMid, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid, doorServoMid2, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid2, doorServoMid, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid, doorServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence8()
{
  delay(200);
  sweep(doorServoNumber, doorServoMin, doorServoMid, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMid, doorServoMid2, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid2, doorServoMid, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid, doorServoMid2, 1);
  delay(100);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 1);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence9()
{
  delay(1000);
  sweep(doorServoNumber, doorServoMin, doorServoMid, 2000);
  delay(500);
  sweep(doorServoNumber, doorServoMid, doorServoMid2, 1000);
  delay(1);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid2, doorServoMid3, 1);
  delay(50);
  sweep(doorServoNumber, doorServoMid3, doorServoMid2, 1);
  delay(500);
  sweep(doorServoNumber, doorServoMid2, doorServoMid, 5000);
  delay(1);
  sweep(doorServoNumber, doorServoMid, doorServoMax, 1000);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 1);
  delay(450);
  sweep(armServoNumber, armServoMax, armServoMin, 1);
  delay(200);
  sweep(doorServoNumber, doorServoMax, doorServoMin, 1);
  delay(400);
}

void sequence10()
{
  delay(800);
  sweep(doorServoNumber, doorServoMin, doorServoMax, 30000);
  delay(1);
  sweep(armServoNumber, armServoMin, armServoMax, 3000);
  delay(1);
  sweep(armServoNumber, armServoMax, armServoMin, 3000);
  delay(1);
  sweep(doorServoNumber, doorServoMax, doorServoMid, 30000);
  delay(1);
  sweep(doorServoNumber, doorServoMid, doorServoMin, 1);
  delay(300);
}
