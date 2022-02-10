#define LDR A0
#define Bg 2
#define Bd 3
#include <Servo.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Servo srv;
int P;
int Lumi;
int mode=2;
// Tableau contenant les ordonnées en y des 240 points à afficher
uint16_t Trace[240]={0};
// Variable contenant la coordonnées en x du point sur lequel on travaille
// Cette variable est initialisée à 0
uint8_t x=0;

int afficher(float P);

void setup() {
 Serial.begin(9600);
  Serial.println("Panneau solaire automatique"); 
 
  tft.begin();
  
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(3);
  tft.setCursor(0,0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(2);
  tft.println("Panneau solaire automatique");
  delay(1500);
pinMode(LDR, INPUT);

srv.attach(6); //definition de la broche du servo
srv.write(0); //definition de sont angle de depart ici 0°
delay(500);
P=Scan(); //appel de la fonction de scan et on rentre la position avec le plus de luminositer dans une variable P
srv.write(P); //definition de l'angle du servo avec P pour orienté le panneau la ou le rendement sera optimal
delay(1000);
Lumi=Luminosite(); //appel de la fonction de luminosité pour la rentré dans une variable Lumi qui nous permetra de comparé le changement de luminosité plus tard
}

void loop() {
  if (digitalRead(Bg)==true){
    while(digitalRead(Bg)==true){ //permet de pouvoir rester appuiyer sur le bouton sans que cela ne fassent plusieur foit ce que l'on demande (la boucle s'active au relachement du bouton)
    }
    if (mode==1){ //si c'est le mode 1 il passe au mode 2
      mode=2;
    }
    else { //si c'est le mode 2 il passe au mode 1
      mode=1;
    }
  }
  if (mode==1){ 
     while (digitalRead(Bd)==true){ //si le mode et le mode 1 et que le bouton de droite et appuyer alors la boucle s'active
      delay(50);
      if (P<180 and P>=0){ //permet de changer manuelement la position 
        P=P+5;
        srv.write(P);
        afficher(P);
        Lumi=Luminosite(); //permet de changer la luminositer a comparé
      }
      else {
        P=0;
        srv.write(P);
        afficher(P);
        Lumi=Luminosite(); //permet de changer la luminositer a comparé
      }
    }
  }
  if (mode==2){
    if (digitalRead(Bd)==true){ //si le mode et le mode 2 et que le bouton de droite et appuyer alors la boucle s'active
      P=Scan(); //alors on est dans le mode "auto" et si l'on appuie sur le bouton de droite on relance un scan
      srv.write(P);
      afficher(P);
      delay(1000);
      Lumi=Luminosite();  
    }
    if (Lumi-Luminosite()>100 or Luminosite()-Lumi>100){ //si la luminosité change depuis le moment du scan on relance le scan pour retrouvé l'endroit optimal
      delay(100);
      P=Scan();
      srv.write(P);
      afficher(P);
      delay(1000);
      Lumi=Luminosite();
      }
  }
}

int Luminosite() {
  float Ul=5.000-((analogRead(LDR)*5.000)/1024);          //on recupère le potentiel après la LDR et on le soustrait au pententiel avent la LDR pour trouver la tension aux bornes de la LDR
  float RL=((-Ul)*1000)/((Ul)-5.000);                    //on injecte la formule de la tension aux bornes de la LDR dans la formule de la résistance LDR trouvée à l'aide du pont diviseur de tension (voir shema)
  int Lux=10.76*exp(log(45706/RL)/0.8311);               //on injecte la formule de la résistance LDR trouvée dans celle du niveau d'éclairement 
  return Lux;
}

int Scan() { //on lance un scan avec la ldr pour trouver l'endroit ou il y a le plus de luminosité
  int i=0;
  int Lum=0;
  int Pos=0;
  while(i!=180) { //180 puisque le servo ne peut avoir des angle qu'entre 0° et 180°
    delay(100);
    srv.write(i);
    Serial.println(Lum);
    if (Luminosite()>Lum){ //ici on compare la luminosite ancienement plus haute avec celle qu'on trouve
      Lum=Luminosite(); //si la lum trouver et plus importante que l'ancienne alors on la defini comme nouvellement la plus grande
      Pos=i; //de plus on enregistre la position de l'endroit avec le plus de luminosité
    }
    i=i+2; //ici on trouve le pas du servo moteur ici on va a 2° par incrementation
  }
  afficher(Pos);
  return Pos;
}

int afficher(float P, float L) //cette fonction permet d'afficher sur l'ecrant tft la posititon du panneaux solaire plus la luminosité a cette endroit
{
  
  if (0 <= P and P <= 22.5) 
  {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);  
    tft.fillCircle(95, 110, 10, ILI9341_RED) ;
    tft.fillCircle(225, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(160, 175, 10, ILI9341_WHITE) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_WHITE) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_WHITE) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position 1 :");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_WHITE);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    
  }
  else  if (22.5<P and P<=67.5) {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);
    tft.fillCircle(95, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(225, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(160, 175, 10, ILI9341_WHITE) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_RED) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_WHITE) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position 2 :");
    tft.setCursor(0, 320);
    tft.setTextColor(ILI9341_WHITE);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
  
  }
  else  if (67.5<P and P<=112.5) {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);
    tft.fillCircle(95, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(225, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(160, 175, 10, ILI9341_RED) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_WHITE) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_WHITE) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position 3 :");
    tft.setCursor(0, 320);
    tft.setTextColor(ILI9341_WHITE);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    
  }
  else  if (112.5<P and P<=157.5) {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);
    tft.fillCircle(95, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(225, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(160, 175, 10, ILI9341_WHITE) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_WHITE) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_RED) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position 4 :");
    tft.setCursor(0, 320);
    tft.setTextColor(ILI9341_WHITE);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
 
  }
  else  if (157.5<P and P<=180) {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);
    tft.fillCircle(95, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(225, 110, 10, ILI9341_RED) ;
    tft.fillCircle(160, 175, 10, ILI9341_WHITE) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_WHITE) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_WHITE) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position 5 :");
    tft.setCursor(0,320);
    tft.setTextColor(ILI9341_WHITE);  
    tft.setTextSize(1);
    tft.println("Luminosité : ");
    tft.println(L);
  
  }
  else if (P>180 or P<0) {
  tft.fillScreen(ILI9341_BLACK);
  tft.println("Erreur de position du panneau solaire");
  delay(100);
  }
}
