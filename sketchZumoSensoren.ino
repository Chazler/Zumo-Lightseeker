#include <Wire.h>
#include <NewPing.h>
#include <ZumoShield.h>

ZumoMotors motors;

//Photocells
int photocellPin1 = 0;
int photocellPin2 = 2;
int photocellReadingLinks;
int photocellReadingRechts;

//EchoSensoren
#define maximum_distance 200
int trigPin1 = 3;
int echoPin1 = 2;
NewPing sonarLinks(trigPin1, echoPin1, maximum_distance); //sensor function

int trigPin2 = 4;
int echoPin2 = 5;
NewPing sonarRechts(trigPin2, echoPin2, maximum_distance); //sensor function
int distance;
int duration;

enum directionEnum {LINKS,RECHTS};
directionEnum checkLight();

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  driveDir(checkLight());
}

void driveDir(directionEnum dir){
  switch (dir){
    case LINKS:
      Serial.println("Drive Links");
      motors.setSpeeds(75,150);
      delay(100);
    break;
    case RECHTS:
      Serial.println("Drive Rechts");
      motors.setSpeeds(150,75);
      delay(100);
    break;
  }
  delay(100);
}

directionEnum checkLight(){
  if (sonarRechts.ping_cm() < 12 && sonarRechts.ping_cm() != 0){
    Serial.println("Obstakel rechts = ");
    Serial.print(sonarRechts.ping_cm());
    motors.setSpeeds(-200,-200);
    delay(400);
    motors.setSpeeds(50,200);
    delay(200);
    return LINKS;
  }
  if (sonarLinks.ping_cm() < 15 && sonarLinks.ping_cm() != 0){
    Serial.println("Obstakel links = ");
    Serial.print(sonarLinks.ping_cm());
    motors.setSpeeds(-200,-200);
    delay(400);
    motors.setSpeeds(200,50);
    delay(200);
    return RECHTS;
  }
  
  int lichtLinks = analogRead(photocellPin2);
  int lichtRechts = analogRead(photocellPin1);

  if ((lichtLinks - lichtRechts) > 0){
    return LINKS;
  }
  else{
    return RECHTS;
  }
}
