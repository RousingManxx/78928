#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid = "iPhone de Alex";
const char* password = "12345678";
AsyncWebServer server(80);

void setup() {
  pinMode(2, OUTPUT);
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

  server.begin();
  /*
  delay(10);
  */

}

void loop() {
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

Serial.println("");
Serial.println("Wifi Connected");
Serial.println("Ip Address: ");
Serial.println(WiFi.localIP());
}