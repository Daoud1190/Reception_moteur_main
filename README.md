# Reception_main_robotique

# Source du project
https://www.gotronic.fr/blog/articles/controle-dune-main-robotique/
# Introduction 
 
A l'occasion de mon TFE de fin de 6eme année secondaire. J’ai décidé de mener un projet qui va me permettre d’appliquer mes connaissance acquis grâce à mon apprentissage à l’INRACI. 
Le but de mon projet est de crée une main que l’on pourra contrôle grâce à un gant à distance. 
Mes motivations pour ce projet viennent de ma passion pour la domotique et le contrôle à distance. 
Depuis tout petit je suis fascinée par les entités contrôler à distance et se projet est l’occasion de rallier ce que j’aime et l’électronique. 
Rapide explication
Les servos moteurs qui seront relier au doigts de la main robotique vont être brancher à une première carte ESP32 qui communiquera avec la même carte. La deuxième carte sera elle brancher au 5 capteurs de flexion qui seront coller aux gants. Les 2 carte pourront communiquer grâce à leur options BT intégré.  
  
# Les caractéristiques 

 
# Liste des composants 
Electronique 

 - 2X Adafruit Carte Feather HUZZAH32 ESP32        
 - 5x Capteur de Force, ZD10-100 500g 
 - 1X Batterie
 - 1X M5PAPER
 - 5X résistances smd
 - 1X interrupteur
 - 5X fusibles
  
Mécanique 

- 1X Bras mécanique  
- 5X servo moteur (SG90) 
- 1X Gants en tissus  

# Schéma bloc
## Gant
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/56ece4cd-7237-44d4-9772-9759d0045244)
## Main
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/6e3d5bc1-0683-43b9-865e-6b1bd5fd6e86)

