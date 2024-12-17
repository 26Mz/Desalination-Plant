// Benötigte Libraries werden importiert
#include <DallasTemperature.h>
#include <OneWire.h>
// Hier wird der Eingangs-Pin deklariert, an dem das SensorModul angeschlossen ist
#define LKTemp2 4
#define ECSencor A0
int counter = 0;
// Libraries werden konfiguriert
OneWire oneWire(LKTemp2);
DallasTemperature sensors(&oneWire);

#define TdsSensorPin A1
#define VREF 5.0           // analog reference voltage(Volt) of the ADC
#define SCOUNT 30          // sum of sample point
int analogBuffer[SCOUNT];  // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

void setup() {
  // Initialisierung Serielle Ausgabe
  Serial.begin(9600);
  pinMode(TdsSensorPin, INPUT);
  // Sensor wird initialisiert
  sensors.begin();
}
/*
void loop() {
  // Temperaturmessung wird gestartet...
  sensors.requestTemperatures();
  // ... und gemessene Temperatur ausgeben
  Serial.print(counter);
  Serial.print("\t");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("\t");
  Serial.println(analogRead(ECSencor));
  counter++;
  delay(1000);  // 1s Pause bis zur nächsten Messung
}*/
static unsigned long analogSampleTimepoint = millis();
static unsigned long printTimepoint = millis();
void loop() {
  if (millis() - analogSampleTimepoint > 40) {  //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);  //read the analog value and store into the buffer
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)  analogBufferIndex = 0;
  }
  
  if (analogBufferIndex == SCOUNT -1) {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }

    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);

    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;  // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);               //temperature compensation formula : fFinalResult(25 ^ C) = fFinalResult(current) / (1.0 + 0.02 * (fTP - 25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient;
    // temperature compensation
    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5;  //convert voltage value to tds value
    //Serial.print("voltage:");
    //Serial.print(averageVoltage,2);
    //Serial.print("V ");
    Serial.print(counter);
    Serial.print("\t");
    Serial.print(tdsValue);
    Serial.print("\t");
    Serial.println(temperature);
    counter++;
  }
}

int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
