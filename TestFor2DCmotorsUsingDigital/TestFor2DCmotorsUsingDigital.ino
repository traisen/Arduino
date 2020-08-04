/* 
 *  TestFor2DCmotorsUsingAnalog 
 *
 *  Tests 2 DC motors on L9110S H Bridge using digitalWrite
 *  uses wheel direction for motor direction
 *     forwards = fwd; backwards = bck; and stopping = off
 *  Test 1: Motor A fwd, bck, off   wait 5 sec.s
 *  Test 2: Motor B fwd, bck, off   wait 5 sec.s
 *  Test 3: Both Motors fwd, bck, off   wait 5 sec.s
 *    wait 5 sec.s
 *  repeat
 *  
 *  Although only digitalWrite is used (full speed or off)
 *  the PWM pins are chosen so can switch to analogWrite without rewiring.
 *  
 *  Motor A is on pins 3,9
 *  Motor B is on pins 10,11 
 *  
 *  Best if test with both x1A and x1B motor pins attached,
 *  even in only plan to go forward, because direction differences
 *  will so wiring problems.
 *  
 *  Created: 8/1/2020 Carolyn Oates  
 *  github traisen/Ardiuno
 */

const int delayT = 5000; // 5 sec

const int fwd = 1;
const int bck = -1;
const int off = 0;

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
  // Is Motor A - working in both directions and stopping?
  move_motorA(fwd); 
  delay(delayT);
  move_motorA(bck); 
  delay(delayT);
  move_motorA(off); 
  delay(delayT);

  // Is Motor B - working in both directions and stopping?
  move_motorB(fwd); 
  delay(delayT);
  move_motorB(bck); 
  delay(delayT);
  move_motorB(off); 
  delay(delayT);

  // Do both motors work at same time?
  // Are both motors turning in the same direction?
  //   If not how can wiring be changed to fix this?
  //   What is simplest way of the 2 ways and why?
  // Is fwd labeled correctly? 
  //    Again you how can change wiring to correct?
  //    OR reverse code for fwd and bck.
  move_motorA(fwd); 
  move_motorB(fwd); 
  delay(delayT);
  move_motorA(bck); 
  move_motorB(bck); 
  delay(delayT);
  move_motorA(off); 
  move_motorB(off); 
  delay(delayT*2);
}

// Moves motor A forwards, backwards or stops as requested
// (Note: used switch because easier to read   than if else if else)
void move_motorA(int d) 
{
    switch (d) {
    case fwd:         // move forward
      digitalWrite(A1A,LOW);
      digitalWrite(A1B,HIGH);
      break;
    case bck:         // move backwards
      digitalWrite(A1A,HIGH);
      digitalWrite(A1B,LOW);
      break;
    default:          // off
      digitalWrite(A1A,LOW);
      digitalWrite(A1B,LOW);
  }
}

// Moves motor A forwards, backwards or stops as requested
// (Note: used switch because easier to read   than if else if else)
void move_motorB(int d)  
{
    switch (d) {
    case fwd:         // move forward
      digitalWrite(B1A,LOW);
      digitalWrite(B1B,HIGH);
      break;
    case bck:         // move backwards
      digitalWrite(B1A,HIGH);
      digitalWrite(B1B,LOW);
      break;
    default:          // off
      digitalWrite(B1A,LOW);
      digitalWrite(B1B,LOW);
  }
}
