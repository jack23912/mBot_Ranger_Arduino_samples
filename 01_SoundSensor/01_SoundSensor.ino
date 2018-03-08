/**
 * Fuente: https://bricolabs.cc/wiki/guias/mbot_con_ide_arduino
 */
int PIN_sonido = A1;
int intensidad_sonido;
 
void setup() 
{
// Abre a comunicación serie (para o monitor serie)
  Serial.begin(9600);
}
 
void loop() 
{
  intensidad_sonido = 0;
 
  for (int i=0; i<100; i++)
  {
    // Le o valor da tensión no pin A1 e queda co máximo das medidas tomadas
    intensidad_sonido = max (intensidad_sonido, analogRead (PIN_sonido));
  }
  Serial.print ("Intensidad de sonido: "); Serial.println (intensidad_sonido);
 
  delay (500);
}

