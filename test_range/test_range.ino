// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  Serial.begin(38400);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  
/*  myservo.write(0);                  // sets the servo position according to the scaled value 
  Serial.println("1");
  delay(1000); 
  myservo.write(45);
  Serial.println("2");
delay(5000);   // sets the servo position according to the scaled value */
  int t = 1000;
  while (1) {
    char c = serial.read();
    if (c == 'a') {
      t += 100;  
    }
    else if (c == 's') {
      t -= 100 
    }
    else {
      myservo.writeMicroseconds(0);
      break;     
    }
    Serial.println(t);
    myservo.writeMicroseconds(t);                  // sets the servo position according to the scaled value 
    delay(15);
  }
  Serial.println("3");
  delay(10000);                  // sets the servo position according to the scaled value 
                       // waits for the servo to get there 
} 
