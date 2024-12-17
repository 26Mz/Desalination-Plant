import serial

# path to serial interface (e.g. COM3 for Windows or /dev/ttyUSB0 for Linux/Mac)
port = "COM3"  # Agjust to your port, seen in the Arduino IDE, if you click on "Arduino Uno" on the top left.
baud_rate = 9600  # Must be same as serial.begin() in the .ino code
output_file = "data\\arduino_data0.txt"

try:
    # open serial connection
    ser = serial.Serial(port, baud_rate, timeout=1)
    print(f"Verbindung zu {port} hergestellt")
    
    with open(output_file, "w") as file:
        while True:
            # read data from serial connection
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(f"Gelesen: {line}")
                file.write(line + "\n")  # Write data to .txt document
except KeyboardInterrupt:
    print("\nProgramme ended")
except Exception as e:
    print(f"Error: {e}")
finally:
    ser.close()
    print(f"Data saved in: {output_file}")
