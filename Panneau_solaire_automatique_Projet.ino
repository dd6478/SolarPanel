#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);



/*
 *  L'afficheur présente une matrice de points de 240 pixels en x 
 *  sur 320 pixels en y
 *  
 *  Pour chaque point en x allant de 0 à 239, 
 *  il s'agit de calculer l'ordonnée en y allant de 0 à 319
 */

// Tableau contenant les ordonnées en y des 240 points à afficher
uint16_t Trace[240]={0};
// Variable contenant la coordonnées en x du point sur lequel on travaille
// Cette variable est initialisée à 0
uint8_t x=0;

int afficher(float P, float L);

void setup() 
{
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

  /*************************************************************************
  * Tracé du repère en x et y avec quadrillage
  * Axe vertical de 0 à 5V avec une graduation (sous-axe) tous les 1V .... pour des pixels allant de 0 à 319  
  * Axe horizontal de 0 à 2390ms avec une graduation (sous-axe) toutes les 400ms .... pour des pixels allant de 0 à 239 
  *    
  * Fonctions à utiliser :
  * Tracé d'une ligne verticale
  * tft.drawFastVLine(coordonnée en x du point de départ de la ligne, coordonnée en y du point de départ de la ligne, longueur de la ligne verticale, couleur de la ligne);
  * Tracé d'une ligne horizontale
  * tft.drawFastHLine(coordonnée en x du point de départ de la ligne, coordonnée en y du point de départ de la ligne, longueur de la ligne horizontale, couleur de la ligne);
  **************************************************************************/

 
}

/*
 * !! IMPORTANT !!
 * 
 * A chaque nouveau passage dans la boucle loop(), on travaille sur un nouveau point en x
 * 
 * On démarre en travaillant sur le point dont la coordonnée en x=0
 * Au deuxième passage, on travaille sur le point dont la coordonnée en x=1
 * ... etc.
 * On termine en travaillant sur le point dont la coordonnée en x=239
 * Puis on recommence ...
 * 
*/

void loop() {
  
  afficher(20, 100);








  
  


  
  /*************************************************************************
  * Mesure de la tension d'entrée présente sur l'entrée A0 de la carte ARDUINO
  * Stockage dans la variable "Tension_Ve"
  * On choisira de faire une mesure toutes les 10ms .... fonction à utiliser "delay(10);"
  * Se référer au document "fiche-outil-mesurer-une-tension-1.pdf" disponible dans le dossier Ressources_Eleve.
  * ATTENTION : On exprimera la tension mesurée en mV !!!!
  *************************************************************************/

  /*************************************************************************
  * Affichage de la tension d'entrée mesurée sur l'écran TFT
  * On indiquera l'unité
  * 
  * Fonctions à utiliser :
  * tft.fillScreen(couleur choisie); 
  * tft.setCursor(coordonnée en x,coordonnée en y);
  * tft.setTextColor(couleur choisie pour le caractère, couleur choisie pour le fond);  
  * tft.setTextSize(taille des caractères);
  * tft.println("Chaîne de caractères à afficher");
  * tft.println(variable à afficher);
  * 
  * Tailles de caractère disponibles :
  * 1 = 10 pixels de haut, 
  * 2 = 20 pixels de haut, 
  * ... etc 
  * 5 = 50 pixels de haut
  * 
  * Couleurs disponibles :
  * ILI9341_BLACK
  * ILI9341_NAVY
  * ILI9341_DARKGREEN
  * ILI9341_DARKCYAN
  * ILI9341_MAROON
  * ILI9341_PURPLE
  * ILI9341_OLIVE
  * ILI9341_LIGHTGREY
  * ILI9341_DARKGREY
  * ILI9341_BLUE
  * ILI9341_GREEN
  * ILI9341_CYAN
  * ILI9341_RED
  * ILI9341_MAGENTA
  * ILI9341_YELLOW
  * ILI9341_WHITE
  * ILI9341_ORANGE
  * ILI9341_GREENYELLOW
  * ILI9341_PINK
  *************************************************************************/

  
}


int afficher(float P, float L) 
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
    tft.println("Position1 :");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    delay(10000);
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
    tft.println("Position2 :");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    delay(10000);
    delay(10000);

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
    tft.println("Position3");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    delay(10000);
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
    tft.println("Position4");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Luminosité :");
    tft.println(L);
    delay(10000);
  }
  else  if (157.5<P and P<=180) {
    tft.fillCircle(160, 110, 50, ILI9341_WHITE);
    tft.fillCircle(95, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(225, 110, 10, ILI9341_WHITE) ;
    tft.fillCircle(160, 175, 10, ILI9341_WHITE) ;
    tft.fillCircle(107.5, 150, 10, ILI9341_RED) ;
    tft.fillCircle(212.5, 150, 10, ILI9341_WHITE) ;
    tft.setCursor(130,110);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Position5");
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_BLACK);  
    tft.setTextSize(1);
    tft.println("Luminosité : ");
    tft.println(L);
    delay(10000);
  }
  else if (P>180 or P<0) {
  tft.fillScreen(ILI9341_BLACK);
  tft.println("Erreur de position du panneau solaire");
  delay(10000);
  }
}
