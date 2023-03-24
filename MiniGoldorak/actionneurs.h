#ifndef actionneurs_h
#define actionneurs_h

enum EtatSignal { TETEBAISSEE, DETECTIONBAS, REVEIL, TETELEVEE, DETECTIONHAUT, REPOS };

//Constants
#define MOTOR_DURATION 5000 //Durée actionnement du moteur
#define LED_DURATION 100 //Interval de clignotement de la LED
#define MOTOR_PIN_A1 D5 //Numéro de la broche pour le moteur
#define MOTOR_PIN_B1 D6 //Numéro de la broche pour le moteur
#define MOTOR_SPEED 150 //Vitesse du moteur, entre 0 et 255
#define LED_PIN 13 //Numéro de la broche pour la LED
#define SENSOR_DURATION 1000 //Interval actualisation du capteur
#define TETEBAISSEEDURATION 2000
#define TETELEVEEDURATION 5000

void initActionneurs();
void algoActionneurs();

#endif
