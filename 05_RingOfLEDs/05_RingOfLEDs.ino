#include <Adafruit_NeoPixel.h>  // Libreria para manexar o anel de Neopixels
 
int PIN       = 44;  // Pin no que están conectados os Neopixels 
int NUMPIXELS = 12;  // Número de Neopixels
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  pixels.begin ();   // Esta instrucción inicializa a librería
}
 
void loop (){
  // Con este código encendemos o pixel 8
  pixels.setPixelColor(8, pixels.Color(175,0,0));
  pixels.show();
  delay (500);
 
  pixels.setPixelColor(8, pixels.Color(0,0,0));
  pixels.show();
  delay (500);
}
