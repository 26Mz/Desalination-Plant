import serial
import time
import os

# Pfad zur seriellen Schnittstelle (z. B. COM3 für Windows oder /dev/ttyUSB0 für Linux/Mac)
port = "COM3"  # Passe dies an deinen Port an
baud_rate = 9600  # Baudrate muss mit der im Arduino-Code übereinstimmen
output_file = "data\\arduino_data0.txt"

try:
    # Serielle Verbindung öffnen
    ser = serial.Serial(port, baud_rate, timeout=1)
    print(f"Verbindung zu {port} hergestellt")
    
    with open(output_file, "w") as file:
        while True:
            # Daten von der seriellen Verbindung lesen
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(f"Gelesen: {line}")
                file.write(line + "\n")  # Daten in die Datei schreiben
except KeyboardInterrupt:
    print("\nProgramm beendet")
except Exception as e:
    print(f"Fehler: {e}")
finally:
    ser.close()
    print(f"Daten wurden in {output_file} gespeichert")
