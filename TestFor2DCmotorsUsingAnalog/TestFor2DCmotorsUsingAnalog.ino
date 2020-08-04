/* 
 *  Tests 2 DC motors on L9110S H Bridge using analogWrite
 *  uses wheel direction for motor direction
 *     forwards = fwd; backwards = bck; and stopping = off
 *     There us a waut betweeb tests,
 *  Test 1: Motor A fwd fast, fwd slow, bck fast, bck slow, off  
 *  Test 2: Motor B fwd fast, fwd slow, bck fast, bck slow, off   
 *  Test 3: Both Motors fwd-fast, bck-fast,   Tests forward, wait (10 secs)
 *          motor A slow motor B fast; wait, motor A fast motor B slow; wait, Tests right and left turns, wait
 *          both motors: fwd-slow, bck-slow,off, wait
 *  wait 15 sec.s
 *  repeat
 *  
 *  Although only digitalWrite is used (full speed or off)
 *  the PWM pins are chosen so can switch to analogWrite without rewiring.
 *  
 *  Motor A is on pins 3,9
 *  Motor B is on pins 10,11 
 *  
 *  
 *  Created: 8/1/2020 Carolyn Oates
 *  github traisen/Ardiuno
 */

const int delayT = 5000; // 5 sec

const int fwd = 1;
const int bck = -1;
const int off = 0;

int slow = 50;
int fast = 255;

// Ardunino PWM pins 3=A1A, 5, 6, 9=A1B, 10=B1A, 11=B1B 
//  pins 3,9,10,11 are 490 Hz; pins 5,6 are 980 Hz
//  Chose pins with same Hz

// L9110S pins 
// (It helps to check your wiring matches your code, if list color of your wires to pin in comments)
const int B1B = 9; // red  to pin 9
const int B1A = 3; // blue to pin 3

// GND             // purple to GND  by 5V on Arduino
// VCC signal      // red    to 5V  by GND on Arduino 

const int A1B = 11; // gray  to pin 11
const int A1A = 10; // white to pin 10

// Motor power pins (starting on B1A side) RED-BLACK RED-BLACK

void setup() {
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  delay(3000);
}

void loop() {
  // Is Motor A - working in both direction, both fast and slow and stopping?
  move_motorA(fwd,fast); 
  delay(delayT);
  move_motorA(fwd,slow); 
  delay(delayT); 
  move_motorA(bck,fast); 
  delay(delayT);
  move_motorA(bck,slow); 
  delay(delayT); 
  move_motorA(off,off); 
  delay(delayT);

  // Is Motor B - working in both directions and stopping?
  move_motorB(fwd,fast); 
  delay(delayT);
  move_motorB(fwd,slow); 
  delay(delayT); 
  move_motorB(bck,fast); 
  delay(delayT);
  move_motorB(bck,slow); 
  delay(delayT); 
  move_motorB(off,off); 
  delay(delayT);

  // Do both motors work at same time?
  // Are both motors turning in the same direction?
  //   If not how can wiring be changed to fix this?
  //   What is simplest way of the 2 ways and why?
  // Is fwd labeled correctly? 
  //    Again you how can change wiring to correct?
  //    OR reverse code for fwd and bck.
  move_motorA(fwd,fast);   // both forward fast
  move_motorB(fwd,fast); 
  delay(delayT);
  move_motorA(bck,fast);   // both backwards fast
  move_motorB(bck,fast); 
  delay(delayT*2);
  move_motorA(fwd,slow);   // A forward slow // slow - fast used for turns
  move_motorB(fwd,fast);   // B forward fast
  delay(delayT);
  move_motorA(bck,fast);   // A forward fast
  move_motorB(bck,slow);   // B forward slow // fast - slow used for turns
  delay(delayT);
  move_motorA(fwd,slow);   // both forwards slow
  move_motorB(fwd,slow); 
  delay(delayT);
  move_motorA(bck,slow);   // both backwards slow
  move_motorB(bck,slow); 
  delay(delayT);
  move_motorA(off,off);    // both off
  move_motorB(off,off); 
  delay(delayT*3);
}

void move_motorA(int d, int speed) 
{
    switch (d) {
    case fwd:         // move forward
      analogWrite(A1A,LOW);
      analogWrite(A1B,speed);
      break;
    case bck:         // move backwards
      analogWrite(A1A,speed);
      analogWrite(A1B,LOW);
      break;
    default:          // off
      analogWrite(A1A,LOW);
      analogWrite(A1B,LOW);
  }
}

void move_motorB(int d, int speed)  
{
    switch (d) {
    case fwd:         // move forward
      analogWrite(B1A,LOW);
      analogWrite(B1B,speed);
      break;
    case bck:         // move backwards
      analogWrite(B1A,speed);
      analogWrite(B1B,LOW);
      break;
    default:          // off
      analogWrite(B1A,LOW);
      analogWrite(B1B,LOW);
  }
}
