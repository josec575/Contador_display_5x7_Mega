//Programa teste display dot matrix 5x7 anodo comum
int colPins[5] = {54, 55, 56, 57, 58};            // Colunas PF0-PF4
int rowPins[7] = {62, 63, 64, 65,66,67,68};       // Linhas PK0-PK6

void clearDisplay() 
{
for (int c = 0; c < 5; c++)    
{
   PORTF &=~(1 << c);         // destiva colunas nivel 0 (anodo comum)
}   
 
for (int r = 0; r < 7; r++) 
{
PORTK |= (1 << r);            // destiva linhas nivel 1 (anodo comum)
}   

delay(200);                   // delay 200 ms
}
void setup()
{
// Configura pinos como saída
  for (int c = 0; c < 5; c++) pinMode(colPins[c], OUTPUT);
  for (int r = 0; r < 7; r++) pinMode(rowPins[r], OUTPUT);
}
void loop() 
{
   
  for (int c = 0; c < 5; c++)       //varredura de colunas 
  {
    for (int r = 0; r < 7; r++)     //varredura de linhas 
  {
    {
     
      clearDisplay();
      PORTF |=(1 << c);             // ativa coluna nivel 1 em c(anodo comum)
      PORTK &= ~ (1 << r);          // ativa linha r nivel 0 em r (anodo comum)
      delay(200);
      
    }
  }
}
}
