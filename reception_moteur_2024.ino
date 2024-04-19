/*
 * Nom du LAB : Communication Bluetooth ESP32->ESP32 (CODE ESCLAVE)
 *   [ CODE ESCLAVE ]
 * Auteur : Khaled Magdy
 * DeepBlueMbedded 2023
 * Pour plus d'informations, visitez : www.DeepBlueMbedded.com
 */

// Inclusion des bibliothèques nécessaires
#include <ESP32Servo.h>     // Bibliothèque pour contrôler les servomoteurs avec l'ESP32
#include <Wire.h>           // Bibliothèque pour la communication I2C
#include "BluetoothSerial.h"// Bibliothèque pour la communication Bluetooth
#include "m5rotate8.h"

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

// Variables pour stocker les positions des servomoteurs
char pos = 0;
char pos1 = 0;
char pos2 = 0;
char pos3 = 0;
char pos4 = 0;

// Déclaration de l'objet M5ROTATE8
M5ROTATE8 MM;

// Informations sur le périphérique ESP32 Bluetooth (Esclave)
const char *pin = "1234";  // Code PIN pour le couplage Bluetooth
String device_name = "ESP32-BT-Slave"; // Nom du périphérique Bluetooth
int servoPouce = 13;
int servoINDEX = 12;
int servoMAJEUR = 27;
int servoAnnulaire = 33;
int servoAuriculaire = 15; // Broche pour le servomoteur Auriculaire

char receiveData[7];        // Tableau pour stocker les données reçues
#define NB_data 7           // Nombre d'éléments dans le tableau receiveData

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

  // Initialisation de la communication série avec un débit de 115200 bauds
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
  MM.resetAll();
}

// Fonction de boucle principale
void loop() {
  // Vérifie si des données sont disponibles sur le port série et les envoie via Bluetooth
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // Vérifie si des données sont disponibles sur le port série Bluetooth
  if (SerialBT.available()) {
    // Lit le premier caractère des données reçues
    receiveData[0] = SerialBT.read();

    // Vérifie si le premier caractère est '#'
    if (receiveData[0] == '#') {
      // Parcourt les données restants
      for (char cptSend = 1; cptSend < NB_data; cptSend++) {
        // Attend que des données soient disponibles
        while (!SerialBT.available());
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
  }
}
