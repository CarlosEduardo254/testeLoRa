#include <SPI.h>
#include <LoRa.h>

// Pinos pro ESP32
#define ss 5
#define rst 14
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Iniciando LoRa Sender");
  LoRa.setPins(ss, rst, dio0);

  // Ajuste a frequência para o seu módulo (ex: 915E6)
  if (!LoRa.begin(915E6)) { 
    Serial.println("Falha ao iniciar o LoRa!");
    while (1);
  }
  
  // IMPORTANTE: Ativa o CRC para compatibilidade com o Raspberry Pi
  LoRa.enableCrc(); 
}

void loop() {
  Serial.print("Enviando pacote de teste... ");

  LoRa.beginPacket();
  
  // --- CABEÇALHO RADIOHEAD (4 bytes) ---
  LoRa.write(255); // Byte 1: Destino (255 = Broadcast)
  LoRa.write(255); // Byte 2: Remetente (255 = Broadcast)
  LoRa.write(0);   // Byte 3: ID da Mensagem
  LoRa.write(0);   // Byte 4: Flags
  // -------------------------------------
  
  LoRa.print("Ping do ESP32!");
  LoRa.endPacket();

  Serial.println("Enviado.");
  delay(3000);
}