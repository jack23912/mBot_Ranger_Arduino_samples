/**
 * Fuente: https://bricolabs.cc/wiki/guias/mbot_con_ide_arduino
 */

int buzzer = 45;
 
void setup()
{
  tone (buzzer, 392); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 392); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 392); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 311); delay (450); noTone (buzzer); delay (10);
  tone (buzzer, 466); delay (150); noTone (buzzer); delay (10);
  tone (buzzer, 392); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 311); delay (450); noTone (buzzer); delay (10);
  tone (buzzer, 466); delay (150); noTone (buzzer); delay (10);
  tone (buzzer, 392); delay (600); noTone (buzzer); delay (10);
 
  delay (600);
 
  tone (buzzer, 588); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 588); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 588); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 622); delay (450); noTone (buzzer); delay (10);
  tone (buzzer, 466); delay (150); noTone (buzzer); delay (10);
  tone (buzzer, 370); delay (600); noTone (buzzer); delay (10);
  tone (buzzer, 294); delay (450); noTone (buzzer); delay (10);
  tone (buzzer, 466); delay (150); noTone (buzzer); delay (10);
  tone (buzzer, 392); delay (1200); noTone (buzzer); delay (10);
 
  noTone (buzzer);
}
 
void loop() {}
