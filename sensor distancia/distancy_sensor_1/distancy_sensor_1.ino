#include <Ultrasonic.h>
#include <Stepper.h>
#include <Thread.h>
#define pin_trigger 3
#define pin_echo 2
#define pin_biper 9
#define debug 1

Ultrasonic ultrasonic(pin_trigger, pin_echo);
long distance;
long last_distance;
int rotation;

const int stepsPerRevolution = 1024;
Stepper stepper1(stepsPerRevolution, 5, 7, 6, 8);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("[SYSTEM]");
  Serial.println("Starting...");

  Serial.print("[System]");
  Serial.println("Testing motor");

  stepper1.setSpeed(18);  // limitado a 18
}

void loop() {


  // put your main code here, to run repeatedly:
  distance = ultrasonic.read(CM);
  
  

  if (debug) {
    Serial.print("[Ultrasonic] ");
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" - ");
    Serial.print(last_distance);
    Serial.println("cm");
  }

  if (distance >= 100 || distance <= 0) {
    delay(1000);
    return;
  }
  if (distance > last_distance) {
    Serial.print("[Stepper] ");
    rotation = 550;
    Serial.println(rotation);

    digitalWrite(9,HIGH);
    stepper1.step(rotation);
    digitalWrite(9,LOW);
  }
  if (distance < last_distance) {
    Serial.print("[Stepper] ");
    rotation = -550;
    Serial.println(rotation);
    digitalWrite(9,HIGH);
    stepper1.step(rotation);
    digitalWrite(9,LOW);
  }
  // if (distance == last_distance) {

  //   Serial.print("[Stepper] ");
  //   Serial.println(0);
  //   stepper1.step(0);
  // }
  last_distance = distance;

  delay(1000);
}
