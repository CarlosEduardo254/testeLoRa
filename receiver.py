import time

import adafruit_rfm9x
import board
import busio
from digitalio import DigitalInOut

# Pinos CS e RST no Raspberry Pi
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)

# Inicializa SPI padrão do RPi
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)

# Inicializa o LoRa (Ajuste a frequência para bater com a do ESP32, ex: 915.0)
try:
    rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 915.0)
    print("Módulo LoRa inicializado. Aguardando pacotes...")
except RuntimeError as error:
    print("Erro de SPI/Fiação: ", error)
    exit()

while True:
    # Aguarda um pacote por até 5 segundos
    packet = rfm9x.receive(timeout=5.0)

    if packet is None:
        print("Ouvindo...")
    else:
        # Tenta decodificar o payload
        try:
            packet_text = str(packet, "utf-8")
            print(f">>> Recebido: {packet_text}")
        except UnicodeDecodeError:
            print("Pacote recebido, mas não pôde ser decodificado como texto.")
