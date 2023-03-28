#include "actionneurs.h"

//Libraries
#include <Wire.h>
#include <VL53L1X.h>
#include <Servo.h>

//Objects Declaration
Servo servo;
VL53L1X sensor;
bool sensorEnabled = false;
bool etatLed = false;

EtatSignal etatSignal = TETEBAISSEE;

//Global Variables
long unsigned Temps_LED = 0;

long unsigned Temps_Moteur = 0;
long unsigned TempsReel;
long unsigned TempsTeteBaissee = 0;
long unsigned TempsTeteLevee = 0;
long unsigned startTime;
long unsigned elapsedTime;

//Setup > par là, juste faire defiler l'écran
void initActionneurs()
{
  Serial.begin(115200);
  Wire.begin();
  sensor.setTimeout(500);
  Wire.setClock(400000);
  pinMode (MOTOR_PIN_A1, OUTPUT);
  pinMode (MOTOR_PIN_B1, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  } else {
    Serial.println("cool ! ");
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  servo.attach(D8); //Numéro pin moteur
  servo.write(10);
  delay(50);
}

void algoActionneurs()
{
  sensor.startContinuous(50);
  uint16_t distance = sensor.read();
  Serial.print ("Position moteur : ");
  Serial.print (servo.read());
  long unsigned TempsSensor = 0;
  TempsReel = millis();

  Serial.print(" Distance (mm): ");
  Serial.println(distance);
  TempsSensor = TempsReel;
    {
      switch (etatSignal) {
     
        case TETEBAISSEE:
        TempsReel = millis();
          digitalWrite(MOTOR_PIN_A1, LOW);
          digitalWrite(MOTOR_PIN_B1, LOW);
          servo.write(10);
          if (TempsReel - TempsTeteBaissee >= TETEBAISSEEDURATION ){
            etatSignal=DETECTIONBAS;
            TempsTeteBaissee=TempsReel;
            Serial.print( "changement en mode detection bas ");
          }
          break;
     
        case DETECTIONBAS:
          if (distance >= 300) {
            etatSignal=TETEBAISSEE;
            Serial.print("pas de detection ");
          }
          if (distance < 300) {
            etatSignal=REVEIL;
            Serial.print( "Passage en mode reveil ");
            startTime = millis();
          }
          break;
     
        case REVEIL:
          elapsedTime = millis();
          Serial.print("Reveil en cours... ");
          digitalWrite(MOTOR_PIN_A1, LOW);
          digitalWrite(MOTOR_PIN_B1, HIGH);
          Serial.println (elapsedTime - startTime);
          if (elapsedTime - startTime >= 5000){
            digitalWrite(MOTOR_PIN_A1, LOW);
            digitalWrite(MOTOR_PIN_B1, LOW); 
            servo.write(100);
            startTime = elapsedTime;
            Serial.println("Reveil terminé! ");
            etatSignal=TETELEVEE;
            TempsTeteLevee = millis();
          }   
          break;
     
        case TETELEVEE:
        TempsReel = millis();
          if (TempsReel - TempsTeteLevee >= TETELEVEEDURATION ){
            etatSignal=DETECTIONHAUT;
            TempsTeteLevee=TempsReel;
          }
          Serial.print("Tete levée");
          break;
     
        case DETECTIONHAUT:
          if (distance >= 300) {
            etatSignal=REPOS;
            startTime = millis();
          }
          if (distance < 300) {
            etatSignal=TETELEVEE;
          }
          break; 

        case REPOS:
          elapsedTime = millis();         
          digitalWrite(MOTOR_PIN_A1, HIGH);
          digitalWrite(MOTOR_PIN_B1, LOW);
          Serial.print("passage en mode repos ");
          if (elapsedTime - startTime >= 5000){
            digitalWrite(MOTOR_PIN_A1, LOW);
            digitalWrite(MOTOR_PIN_B1, LOW); 
            servo.write(10);
            startTime=elapsedTime;
            etatSignal=TETEBAISSEE;
            TempsTeteBaissee = millis(); 
          }
          break;     
      }
    }
  if ( TempsReel - Temps_LED >= 10) {
    etatLed=!etatLed;
    digitalWrite(LED_PIN, etatLed);
    Temps_LED = TempsReel;
   } 
}
