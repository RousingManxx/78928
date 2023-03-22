#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <ArduinoJson.h>
#include <DHTesp.h>

#define DHTpin 15

// SSID y contraseña de el internet
const char* ssid= "iPhone de Alex";
const char* password = "12345678";

AsyncWebServer server(80);
DHTesp dht;
String aux;

void setup() {
  // Inicializar sensor y banda de comunicación
  Serial.begin(115200);
  dht.setup(DHTpin, DHTesp::DHT11);

  // Llamada al metodo conectarse a internet
  conectarse();
  
  //  Recurso al que se accede
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["status"] = dht.getStatusString();
    json["humedad"] = dht.getHumidity();
    json["temperatura"] = dht.getTemperature();
    json["farenheit"] = dht.toFahrenheit(dht.getTemperature());
    json["sensacion"] = dht.computeHeatIndex(dht.getTemperature(), dht.getHumidity(), false);
    json["sensacion2"] = (dht.computeHeatIndex(dht.toFahrenheit(dht.getTemperature()), dht.getHumidity(), true));
    serializeJson(json, *response);
    request->send(response);
  });

  // CORS
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();

}

void loop(){
}

// Metodo de conectarse a internet
void conectarse(){
  Serial.print("Conectando");Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}