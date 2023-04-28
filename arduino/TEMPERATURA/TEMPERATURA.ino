#include <DHTesp.h>
#include "DHT.h"
#define DHTPin 15
#define DHTTipo DHT11

DHT dht(DHTPin, DHTTipo);

void setup() {
  Serial.begin(115200);
  Serial.println("SENSOR DHT FUNCIONANDO!");
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if(isnan (t) || isnan (h)){
    Serial.println("Lectura erronea");
    return;
  }

  Serial.println("Humedad: ");
  Serial.print(h);
  Serial.println();
  Serial.println(" Temperatura: ");
  Serial.print(t);
  Serial.println(" ºC ");
  delay(2000);
}
