// Arduino Mega
// Colunas -> PORTF (pinos 54–58) = PF0–PF4
// Linhas  -> PORTK (pinos 62–68) = PK0–PK6

// Dígito "0" (5 colunas x 7 linhas)
byte dig0[5] = {
  B1000001, 
  B0111110, 
  B0111110, 
  B0111110, 
  B1000001
};

int colunaAtual = 0;

void setup() {
  // Colunas PF0–PF4 como saída
  DDRF = B00011111;   // PF0–PF4 = saída
  // Linhas PK0–PK6 como saída
  DDRK = B01111111;   // PK0–PK6 = saída
}

void loop() {
  // Apaga tudo
  PORTF = B00000000;  // Colunas desligadas (nível alto para ânodo comum)
  PORTK = B00000000;  // Linhas desligadas

  // Seleciona coluna atual (ativa com nível baixo para ânodo comum)
  PORTF |= (1 << colunaAtual);

  // Envia linhas para essa coluna
  PORTK = (dig0[colunaAtual]) & B01111111;

  // Passa para a próxima coluna
  colunaAtual++;
  if (colunaAtual >= 5) colunaAtual = 0;

  delayMicroseconds(200); // tempo de persistência
}
