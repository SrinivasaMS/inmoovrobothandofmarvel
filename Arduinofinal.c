/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-servo-motor-controlled-by-potentiometer
 */

#include <Servo.h>

Servo thumbServo;
Servo indexServo;  
Servo middleServo;  
Servo ringServo; 
Servo pinkyServo;      // create servo object to control a servo

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  myServo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 1023)
  int analogValue_thumb = analogRead(A0);
  int analogValue_index = analogRead(A1);
  int analogValue_middle = analogRead(A2);
  int analogValue_ring = analogRead(A3);
  int analogValue_pinky = analogRead(A4);

  // scales it to use it with the servo (value between 0 and 180)
  int angle_thumb = map(analogValue_thumb, 0, 1023, 0, 180);
  int angle_index = map(analogValue_index, 0, 1023, 0, 180);
  int angle_middle = map(analogValue_middle, 0, 1023, 0, 180);
  int angle_ring = map(analogValue_ring, 0, 1023, 0, 180);
  int angle_pinky = map(analogValue_pinky, 0, 1023, 0, 180);

  // sets the servo position according to the scaled value
  thumbServo.write(angle_thumb); 
  indexServo.write(angle_index);
  middleServo.write(angle_middle);
  ringServo.write(angle_ring);
  pinkyServo.write(angle_pinky);

  // print out the value
  Serial.print("thumb Analog: ");
  Serial.print(analogValue_thumb);
  Serial.print(",thumb Angle: ");
  Serial.println(angle_thumb);
  Serial.print("index Analog: ");
  Serial.print(analogValue_index);
  Serial.print(",index Angle: ");
  Serial.println(angle_index);
  Serial.print("middle Analog: ");
  Serial.print(analogValue_middle);
  Serial.print(", middle Angle: );
  Serial.println(angle_middle);
  Serial.print("ring Analog: ");
  Serial.print(analogValue_ring);
  Serial.print(", ring Angle: ");
  Serial.println(angle_ring);
  Serial.print("pinky Analog: ");
  Serial.print(analogValue_pinky);
  Serial.print(",pinky Angle: ");
  Serial.println(angle_pinky);
  delay(100);
}
