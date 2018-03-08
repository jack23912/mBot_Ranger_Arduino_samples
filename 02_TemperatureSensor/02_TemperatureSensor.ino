/**
 * Fuente: https://bricolabs.cc/wiki/guias/mbot_con_ide_arduino
 */
int PIN_temperatura = A0;
float temperatura;
 
void setup() 
{
// Abre a comunicación serie (para o monitor serie)
  Serial.begin (9600);
}
 
void loop() 
{
  // Le o valor da tensión no pin A0
  float v_temperatura = analogRead (PIN_temperatura); 
 
  // Calcula o valor da temperatura
  temperatura = 1.0 / (log(v_temperatura/(1023-v_temperatura)) / 3375.0 + 1/298.15) - 273.15;
 
  Serial.print ("Temperatura: "); Serial.println (temperatura);
 
  delay (500);
}
