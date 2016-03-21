#include <string.h> 
 char *setNameCode = "AT+NAME=Jukia\x0d\x0a";
 char *setPasswordCode = "AT+PSWD=6666\x0d\x0a";
 int blueControlPin = 7;
 int ledPin = 13;
 void setName() {
   for (int i = 0; i < strlen(setNameCode); i++) {
    Serial3.write(setNameCode[i]);
   }
 }
 void setPassword() {
   for (int j = 0 ; j < strlen(setPasswordCode) ; j++) {
    Serial3.write(setPasswordCode[j]);
  }
 }
void setup() {
  Serial.begin(9600);
  Serial3.begin(38400);
  pinMode(ledPin,OUTPUT);
  pinMode(blueControlPin, OUTPUT);
  delay(3000);
  /*digitalWrite(7, HIGH);
  setName();
  delay(2000);
  setPassword();
  digitalWrite(7,LOW);*/
  digitalWrite(blueControlPin, LOW);
  delay(1000);
}
void loop() {
 if (Serial3.available()) {
  while(Serial3.available()) {
   char c = Serial3.read();
   Serial.write(c);
  }
  Serial.write("\n");
 }
   digitalWrite(13,HIGH);
   delay(500);
   digitalWrite(13,LOW);
}
