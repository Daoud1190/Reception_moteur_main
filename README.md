# Reception_main_robotique

# Source du project
https://www.gotronic.fr/blog/articles/controle-dune-main-robotique/
#Introduction 
                                                                     1.L’introduction 
 
A l'occasion de mon TFE de fin de 6eme année secondaire. J’ai décidé de mener un projet qui va me permettre d’appliquer mes connaissance acquis grâce à mon apprentissage à l’INRACI. 
Le but de mon projet est de crée une main que l’on pourra contrôle grâce à un gant à distance. 
Mes motivations pour ce projet viennent de ma passion pour la domotique et le contrôle à distance. 
Depuis tout petit je suis fascinée par les entités contrôler à distance et se projet est l’occasion de rallier ce que j’aime et l’électronique. 
Rapide explication
Les servos moteurs qui seront relier au doigts de la main robotique vont être brancher à une première carte ESP32 qui communiquera avec la même carte. La deuxième carte sera elle brancher au 5 capteurs de flexion qui seront coller aux gants. Les 2 carte pourront communiquer grâce à leur options BT intégré.  
  
  
                                                          2.Les caractéristiques 

Caractéristiques : 
 

 
General : 	                    Main 	                      Gants 
-2 boutons poussoir 
 	Sur la carte ESP32 	Sur la carte ESP32 
 
-1 Led 
 	 Led sur la Esp32 	 Led sur la Esp32 
-Main robotique avec 5 servo moteur 
 	  
    Servo moteur SG90                 	 
                        X          
-Gants avec 5 capteurs de flexions (x résolutions) 	                          X 	  A déterminer 
 
 
Electronique : 	                    Main 	                     Gants 
-BT 2,4 GHz 	    Sur la carte ESP32 	Sur la carte ESP32 
-Consommation 	170 et 250 mA pour les 5 servo moteur 	 ESP32 (80-180 mA) 
-Batteries 5 volt  	A déterminer  	A déterminer  
 
 
 
Mécanique : 	                       Main 	                     Gants 
Poids 	               289g 	A déterminer 
Matière 
 	Acrylique noir 5.0 	Tissu 
 
Liste des composants : 
Electronique 
-2X Adafruit Carte Feather HUZZAH32 ESP32        
- 5x Capteur de Force, ZD10-100 500g 
-1X Batterie
-1X M5PAPER
-5X résistances smd
- 1X interrupteur
-5X fusibles 
Mécanique 
-1X Bras mécanique  
-5X servo moteur (SG90) 
-1X Gants en tissus  


