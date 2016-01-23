#include <Servo.h>

Servo rotationServo;
Servo heelServo;

int rotationPin=9;
int rotationCenter = 110;
int rotationLeft = -1;

int heelPin=10;
int heelCenter = 100;
int heelLeft = -1;

int fanPowerPin=1;
int servoPowerPin=2;


bool ran=0;

void setup() {
  pinMode(rotationPin,OUTPUT);
  pinMode(heelPin,OUTPUT);
  pinMode(fanPowerPin,OUTPUT);
  pinMode(servoPowerPin,OUTPUT);
  
  rotationServo.attach(10);  
  heelServo.attach(9);
}

void loop() {
  if(ran==0)
  {
    //reset the relays if necassary
    digitalWrite(servoPowerPin,HIGH);
    digitalWrite(fanPowerPin,HIGH);
  
    //start the servos
    digitalWrite(servoPowerPin,LOW);
    delay(1000);

    //center the servos
    rotationServo.write(rotationCenter);
    heelServo.write(heelCenter);
    delay(1000);
    
    //start the fan
    digitalWrite(fanPowerPin,LOW);
    delay(5000);
    
    //tack left
    rotationServo.write(rotationCenter + (rotationLeft * -45));
    heelServo.write(heelCenter + (heelLeft * -45));
    delay(10000);
  
    //tack right
    rotationServo.write(rotationCenter + (rotationLeft * 45));
    heelServo.write(heelCenter + (heelLeft * 45));
    delay(10000);
  
    //center
    rotationServo.write(rotationCenter);
    heelServo.write(heelCenter);
    delay(1000);
    
    //turn off servos
    digitalWrite(servoPowerPin,HIGH);
    delay(1000);
    //turn off fan
    digitalWrite(fanPowerPin,HIGH);
    
    ran=1;
  }

  //wait until next run to give op a chance to shut down
  delay(1000);
}



