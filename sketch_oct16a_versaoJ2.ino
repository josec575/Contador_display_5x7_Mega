#include <TimerOne.h>
#define S1  8

volatile byte x = 0;
byte i = 0;
byte c = 0;
byte r = 0;
// ===== Dígitos 0–9 (cada um com 5 colunas) =====
byte dig0[5] =
  {B1000001,
   B0111110,
   B0111110,
   B0111110,
   B1000001};
byte dig1[5] = 
  {B1111111,
   B0111101,
   B0000000,
   B0111111,
   B1111111}; // 1
byte dig2[5] = 
  {B0111101,
   B0011110,
   B0101110,
   B0110110,
   B0111001,}; // 2

byte dig3[5] = {
  B0111101,
  B0110110,
  B0110110,
  B0110110,
  B1001001
};
byte dig4[5] = {
  B1100111,
  B1101011,
  B1101101,
  B0000000,
  B1101111
};

byte dig5[5] = {
  B1011000,
  B0111010,
  B0111010,       
  B0111010, 
  B1000110            
};

byte dig6[5] = {
  B1000001,
  B0110110,
  B0110110,
  B0110110,
  B1001111
};

byte dig7[5] = {
  B1111110,
  B0001110,
  B1110110,
  B1111010,
  B1111100
};

byte dig8[5] = {
  B1001001,
  B0110110,
  B0110110,
  B0110110,
  B1001001
};

byte dig9[5] = {
  B1111001,
  B0110110,
  B0110110,
  B0110110,
  B1000001
};
byte digA[5] = {
  B1111111,
  B0000000,
  B1111111,
  B0000000,
  B1111111,
};

 


// ===== Interrupção do TimerOne: muda o número a cada 1 s =====


void mux_display()
{
 byte dados;
  // === Seleciona qual número exibir ===
  switch (x) {
    case 0: dados = dig0[i]; break;
    case 1: dados = dig1[i]; break;
    case 2: dados = dig2[i]; break;
    case 3: dados = dig3[i]; break;
    case 4: dados = dig4[i]; break;
    case 5: dados = dig5[i]; break;
    case 6: dados = dig6[i]; break;
    case 7: dados = dig7[i]; break;
    case 8: dados = dig8[i]; break;
    case 9: dados = dig9[i]; break;
    //case 10:dados = digA[i]; break;
  }

  // === Multiplexação ===
  PORTF = B00000000;  // desliga todas as colunas (nível alto)
  PORTK = 0;          // apaga linhas

  // Port K recebe o byte indexado do vetor e escreve na linha 
  PORTK = (dados) & B01111111;

  // ativa a coluna correspondente em nivel alto
  PORTF =  PORTF|(1 << i);

  // próxima coluna
  i++;
  if (i >= 5) i = 0;
  
  //delayMicroseconds(200); // tempo de persistência
}
void  clearDisplay()
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
// ===== Setup =====
void setup() 
{
  DDRF = B00011111; // PF0–PF4 como saída (colunas)
  DDRK = B01111111; // PK0–PK6 como saída (linhas)
  DDRH=  B11011111;   //configura o pino 8 bit 5 do PORTH como entrada
  Timer1.initialize(2000);        // 2 ms
  Timer1.attachInterrupt(mux_display);
}

// ===== Loop principal: multiplexação =====
void loop() 
{
  if (digitalRead (S1)==1)
  {
  Timer1.detachInterrupt(); 
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
  Timer1.attachInterrupt(mux_display);
}

  else
  {
 
  for (x=0;x<10;x++)
  delay(1000);
  }
}
