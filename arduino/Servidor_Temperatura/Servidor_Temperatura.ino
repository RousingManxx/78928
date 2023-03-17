#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <DHTesp.h>
#define DHTpin 15
DHTesp dht;

const char* ssid = "iPhone de Alex";
const char* password = "12345678";
AsyncWebServer server(80);

void setup() {
// SENSOR LED
  pinMode(2, OUTPUT);
  // FIN

  // SERVICIO WEB
  Serial.begin(115200);
  conectarse();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    int numParametros = request -> params();
    Serial.println(numParametros);
    if(numParametros == 0){
      request ->send(200, "text/html","<h1>Hola Mundo</h1>");
      digitalWrite(2, HIGH); 
    }else{
      AsyncWebParameter* p=request->getParam(0);
      String html = "<h1> hola" + p->value() + " desde ESP32</h1>";
      request->send(200,"text/html",html);
    }
  });
  server.on("/adios",HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(200,"text/html","<h1>adios</h1>");
    digitalWrite(2, LOW);
  });
// temperatura
  server.on("/temp",HTTP_GET, [](AsyncWebServerRequest* request){
    // SENSOR DTH
  Serial.println();
  Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");
  dht.setup(DHTpin, DHTesp::DHT11);
  delay(dht.getMinimumSamplingPeriod());
  float humedad =  dht.getHumidity();
  float temperatura = dht.getTemperature();
  float farenheit =  dht.toFahrenheit(temperatura);
  float calor = dht.computeHeatIndex(temperatura, humedad, false);  
  float calor2 = dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true);


  if (isnan(humedad) || isnan(temperatura)){
    Serial.println("No se pudo leer sensor DHT!");
    return;
  }else{
    request->send(200,"text/html","<h1>TEMPERATURAS</h1><h2>"+String(humedad)+" "+String(temperatura)+" "+String(farenheit)+" "+String(calor)+" "+String(calor2)+"</h2>");
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
  }
  // FIN
  });

  server.begin();
  /*
  delay(10);
  */
// FIN
}

void loop(){
  delay(dht.getMinimumSamplingPeriod());
  float humedad =  dht.getHumidity();
  float temperatura = dht.getTemperature();                            
  if (isnan(humedad) || isnan(temperatura)){
    Serial.println("No se pudo leer sensor DHT!");
    return;
  }
  Serial.print( dht.getStatusString() );
  Serial.print("\t");
  Serial.print(humedad, 1);
  Serial.print("\t\t");
  Serial.print(temperatura, 1);
  Serial.print("\t\t");
  Serial.print( dht.toFahrenheit(temperatura), 1);
  Serial.print("\t\t");
  Serial.print( dht.computeHeatIndex(temperatura, humedad, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true), 1);
  delay(2000);
}

void conectarse(){
  Serial.println();
  Serial.println();
  Serial.print("Conenecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}

Serial.println("#####################");
Serial.println("Wifi Connected");
Serial.println("Ip Address: ");
Serial.println(WiFi.localIP());
Serial.println("#####################");
}