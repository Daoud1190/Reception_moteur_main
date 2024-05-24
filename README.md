# Reception_main_robotique
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/d2b7fc87-36e1-4f90-8f4a-3bf8a841f538)

# Source du projet
https://www.gotronic.fr/blog/articles/controle-dune-main-robotique/
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/caa6b8c0-9e91-4374-8693-e4056b2956e0)

# Introduction 
 
A l'occasion de mon TFE de fin de 6ème année secondaire, j’ai décidé de mener un projet qui va me permettre d’appliquer mes connaissances acquises grâce à mon apprentissage à l’INRACI. 
Le but de mon projet est de créer une main que l’on pourra contrôler grâce à un gant à distance. 
Mes motivations pour ce projet viennent de ma passion pour la domotique et le contrôle à distance. 
Depuis tout petit, je suis fasciné par les entités contrôlées à distance et ce projet est l’occasion de rallier ce que j’aime et l’électronique. 
Rapide explication :
Les servos moteurs qui seront reliés aux doigts de la main robotique vont être branchés à une première carte ESP32 qui communiquera avec une deuxième carte ESP32. Cette dernière sera branchée aux 5 capteurs de flexion qui seront collés aux gants. Les deux cartes pourront communiquer grâce à leurs options BT intégrées.  
  
# Les caractéristiques 

## Général
|                                    | Main                       | Gants                    |
|------------------------------------|----------------------------|--------------------------|
| 2 boutons poussoir                 | Sur la carte ESP32         | Sur la carte ESP32       |
| 1 LED                              | LED sur la carte ESP32     | LED sur la carte ESP32   |
| Main robotique avec 5 servos moteurs| Servo moteur SG90          | X                        |
| Gants avec 5 capteurs de flexion (x résolutions)| X                        | A déterminer             |

## Electronique
|                    | Main                       | Gants                    |
|--------------------|----------------------------|--------------------------|
| BT 2,4 GHz         | Sur la carte ESP32         | Sur la carte ESP32       |
| Consommation       | 170 et 250 mA pour les 5 servos moteurs | ESP32 (80-180 mA) |
| Batteries 5 volt   | A déterminer               | A déterminer             |

## Mécanique
|                    | Main                       | Gants                    |
|--------------------|----------------------------|--------------------------|
| Poids              | 289g                       | 5g                       |
| Matière            | Acrylique noir 5.0         | Tissu                    |

# Liste des composants 
## Electronique 

- [2X Adafruit Carte Feather HUZZAH32 ESP32](https://www.adafruit.com/product/3405)
- [5x Capteur de Force, ZD10-100 500g](https://www.gotronic.fr/art-capteur-de-force-flexiforce-100-lb-31526.htm)
- 1X Batterie
- [1X M5PAPER](https://shop.m5stack.com/products/m5paper-esp32-development-kit)
- 5X résistances smd
- 1X interrupteur
- 5X fusibles réarmable PTC
  
## Mécanique 

- 1X Bras mécanique
- [5X servo moteur (SG90)](https://www.towerpro.com.tw/product/sg90-7/)
- 1X Gants en tissus

# Schéma bloc
## Gant
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/56ece4cd-7237-44d4-9772-9759d0045244)
## Main
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/6e3d5bc1-0683-43b9-865e-6b1bd5fd6e86)

# Schéma de principe sans connecteur

![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/b35885bd-8d20-4a4b-b1e1-3c8ca8ec3a1a)

# PCB
![image](https://github.com/Daoud1190/reception_moteur_2024/assets/146357859/3c00c4ff-1e1e-43a6-be44-43c27cff6cb6)
