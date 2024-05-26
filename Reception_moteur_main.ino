// Inclusion des bibliothèques nécessaires
#include <ESP32Servo.h>       // Bibliothèque pour contrôler les servomoteurs avec l'ESP32
#include <Wire.h>             // Bibliothèque pour la communication I2C
#include "BluetoothSerial.h"  // Bibliothèque pour la communication Bluetooth
#include "m5rotate8.h"
#include <Wire.h>

// Vérifie si le Bluetooth est activé
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Le Bluetooth n'est pas activé ! Veuillez exécuter `make menuconfig` pour l'activer
#endif

// Vérifie si le Bluetooth série est disponible
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Bluetooth série non disponible ou non activé. Il n'est disponible que pour la puce ESP32.
#endif

// Déclaration de l'objet Bluetooth Serial
BluetoothSerial SerialBT;

// Déclaration des objets Servo
Servo myservoPouce;
Servo myservoINDEX;
Servo myservoMajeur;
Servo myservoAnnulaire;
Servo myservoAuriculaire;

Servo myservo;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

#define NB_data 7  // Nombre d'éléments dans le tableau receiveData
// Variables pour stocker les positions des servomoteurs

enum mode {
  Choixmenu,
  Manuelle,
  BT,
};

mode ModeActuelle = Choixmenu;

char pos = 0;
char pos1 = 0;
char pos2 = 0;
char pos3 = 0;
char pos4 = 0;
char receiveData[7];  // Tableau pour stocker les données reçues
char DATA;

// Déclaration de l'objet M5ROTATE8
M5ROTATE8 MM;

// Informations sur le périphérique ESP32 Bluetooth (Esclave)
const char *pin = "4321";               // Code PIN pour le couplage Bluetooth
String device_name = "ESP32-BT-Slave";  // Nom du périphérique Bluetooth
int servoPouce = 14;
int servoINDEX = 32;
int servoMAJEUR = 15;
int servoAnnulaire = 33;
int servoAuriculaire = 27;  // Broche pour le servomoteur Auriculaire
bool inOptionsMenu = false;

int mappedValue;
int encoderValue;
int mappedValue1;
int encoderValue1;
int mappedValue2;
int encoderValue2;
int mappedValue3;
int encoderValue3;
int mappedValue4;
int encoderValue4;
byte mode;

uint8_t R = 0, G = 0, B = 0;  //  colors
uint16_t D = 0;
// Fonction de configuration, appelée une fois au démarrage
void setup() {
  // Attacher les servomoteurs à leurs broches respectives
  myservoPouce.attach(servoPouce);
  myservoINDEX.attach(servoINDEX);
  myservoMajeur.attach(servoMAJEUR);
  myservoAnnulaire.attach(servoAnnulaire);
  myservoAuriculaire.attach(servoAuriculaire);

  // Initialisation de la communication I2C
  Wire.begin();
  Serial.begin(115200);
  // Initialisation de la communication série Bluetooth
  SerialBT.begin(device_name);
  // Affichage des informations sur le périphérique
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  // Définition du code PIN pour le couplage Bluetooth
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
  // Initialisation de l'objet M5ROTATE8

  MM.begin();
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  Serial.begin(115200);
  MM.resetAll();

  delay(100);
}

// Fonction de boucle principale
void loop() {
  // Vérifie si des données sont disponibles sur le port série et les envoie via Bluetooth

  if (SerialBT.available()) {
    SerialBT.write(Serial.read());
    DATA = SerialBT.read();  // Lire le caractère envoyé via Bluetooth
  }
  switch (DATA) {
    case '-':
      Serial.println("CHOIX MENU");
      ModeActuelle = Choixmenu;
      break;

    case '&':
      Serial.println("MODE MANUEL");
      ModeActuelle = Manuelle;
      //************************************pouce****************************
      pouce();
      //*******************************index*******************************
      index();
      //****************************majeur*************************
      majeur();
      //*********************************annulaire****************************
      annulaire();
      //**************************************auriculaire*************************
      auriculaire();
      break;

    case '#':

      ModeActuelle = BT;
      // Lit le premier caractère des données reçues
      receiveData[0] = DATA;
      // Vérifie si le premier caractère est '#'
      if (SerialBT.available()) {

        if (receiveData[0] == '#') {
          // Parcourt les données restants
          for (char cptSend = 1; cptSend < NB_data; cptSend++) {
            // Attend que des données soient disponibles
            while (!SerialBT.available())
              ;
            // Lit et stocke les données
            receiveData[cptSend] = SerialBT.read();
          }
        }

        // Affiche les données reçues
        Serial.println(receiveData[0]);
        Serial.printf("a:%d\n", receiveData[1]);
        Serial.printf("b:%d\n", receiveData[2]);
        Serial.printf("c:%d\n", receiveData[3]);
        Serial.printf("d:%d\n", receiveData[4]);
        Serial.printf("e:%d\n", receiveData[5]);
        Serial.printf("f:%d\n", receiveData[6]);

        // Définit les positions des servomoteurs en fonction des données reçues
        myservoPouce.write(receiveData[1]);
        myservoINDEX.write(receiveData[2]);
        myservoMajeur.write(receiveData[3]);
        myservoAnnulaire.write(receiveData[4]);
        myservoAuriculaire.write(receiveData[5]);

        // Vérifie si les données reçues sont valides
        if (receiveData[0] == '#' && receiveData[6] == (receiveData[1] ^ receiveData[2] ^ receiveData[3] ^ receiveData[4] ^ receiveData[5]))
          Serial.print("Données OK\n");
        else
          Serial.print("Données INVALIDES\n");

        // Efface le tampon de réception
        receiveData[0] = 0;
        // Ajoutez d'autres cas pour d'autres modes si nécessaire
      }
      break;
  }
}

void pouce() {
  encoderValue = MM.getAbsCounter(0);  // Lecture de la position de l'encodeur
  mappedValue = map(encoderValue, 0, 100, 50, 100);

  // Vérification des limites de l'encodeur
  if (encoderValue <= 0) {
    encoderValue = 0;
    MM.setAbsCounter(0, 0);  // Réinitialisez l'encodeur à 0

  } else if (encoderValue >= 350) {
    encoderValue = 350;        // Forcer encoderValue à 350 si c'est le cas
    MM.setAbsCounter(0, 350);  // Réinitialisez l'encodeur à 0
  }
  // Positionnement du servomoteur en fonction de la valeur mappée
  myservoPouce.write(mappedValue);
  Serial.print(encoderValue);
  delay(10);  // Délai entre chaque itération
}

void index() {
  encoderValue1 = MM.getAbsCounter(1);  // Lecture de la position de l'encodeur
  mappedValue1 = map(encoderValue1, 0, 100, 50, 100);
  
  // Vérification des limites de l'encodeur
  if (encoderValue1 <= 0) {
    encoderValue1 = 0;
    MM.setAbsCounter(1, 0);  // Réinitialisez l'encodeur à 0

  } else if (encoderValue1 >= 220) {
    encoderValue1 = 220;       // Forcer encoderValue à 350 si c'est le cas
    MM.setAbsCounter(1, 220);  // Réinitialisez l'encodeur à 0
  }
  // Positionnement du servomoteur en fonction de la valeur mappée
  myservoINDEX.write(mappedValue1);
  Serial.print(encoderValue1);
  delay(10);  // Délai entre chaque itération
}

void majeur() {
  encoderValue2 = MM.getAbsCounter(2);  // Lecture de la position de l'encodeur
  mappedValue2 = map(encoderValue2, 0, 100, 50, 100);

  // Vérification des limites de l'encodeur
  if (encoderValue2 <= 0) {
    encoderValue2 = 0;
    MM.setAbsCounter(2, 0);  // Réinitialisez l'encodeur à 0


  } else if (encoderValue2 >= 220) {
    encoderValue2 = 220;       // Forcer encoderValue à 350 si c'est le cas
    MM.setAbsCounter(2, 220);  // Réinitialisez l'encodeur à 0
  }
  // Positionnement du servomoteur en fonction de la valeur mappée
  myservoMajeur.write(mappedValue2);
  // Affichage de la valeur de l'encodeur
  Serial.print(encoderValue2);
  delay(10);  // Délai entre chaque itération
}
void annulaire() {
  encoderValue3 = MM.getAbsCounter(3);  // Lecture de la position de l'encodeur
  mappedValue3 = map(encoderValue3, 0, 100, 50, 100);

  // Vérification des limites de l'encodeur
  if (encoderValue3 <= 0) {
    encoderValue3 = 0;
    MM.setAbsCounter(3, 0);  // Réinitialisez l'encodeur à 0

  } else if (encoderValue3 >= 220) {
    encoderValue3 = 220;       // Forcer encoderValue à 350 si c'est le cas
    MM.setAbsCounter(3, 220);  // Réinitialisez l'encodeur à 0
  }
  // Positionnement du servomoteur en fonction de la valeur mappée
  myservoAnnulaire.write(mappedValue3);
  // Affichage de la valeur de l'encodeur
  Serial.print(encoderValue3);
  delay(10);  // Délai entre chaque itération
}

void auriculaire() {
  encoderValue4 = MM.getAbsCounter(4);  // Lecture de la position de l'encodeur
  mappedValue4 = map(encoderValue4, 0, 100, 50, 100);

  // Vérification des limites de l'encodeur
  if (encoderValue4 <= 0) {
    encoderValue4 = 0;
    MM.setAbsCounter(4, 0);  // Réinitialisez l'encodeur à 0

  } else if (encoderValue4 >= 220) {
    encoderValue4 = 220;       // Forcer encoderValue à 350 si c'est le cas
    MM.setAbsCounter(4, 220);  // Réinitialisez l'encodeur à 0
  }
  // Positionnement du servomoteur en fonction de la valeur mappée
  myservoAuriculaire.write(mappedValue4);
  // Affichage de la valeur de l'encodeur
  Serial.println(encoderValue4);
  delay(10);  // Délai entre chaque itération
}