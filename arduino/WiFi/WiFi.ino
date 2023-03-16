#include <WiFi.h>

const char* ssid = "dr-rojano";
const char* password = "78928-tw";

void setup() {

  pinMode(2, OUTPUT);

  Serial.begin(115200);
  delay(10);

  //Se inicia la conexion

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  //Se realiza la conexion

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    digitalWrite(2, LOW);
  }
  while(WiFi.status() == WL_CONNECTED){
    delay(2000);
    digitalWrite(2, HIGH);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

//lograda la conexion se muestra informacion

// Serial.println("");
// Serial.println("WiFi connected");
// Serial.println("IP address: ");
// Serial.println(WiFi.localIP());
}

void loop() {
}
