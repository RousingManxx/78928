//creación del mapa
var map = L.map('map').setView([19.542354467006163, -96.91752793827085], 13);
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
  maxZoom: 19,
  attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);
//creación del marker
var marker = L.marker([19.5414448641433, -96.92720300407593]).addTo(map);
//agregar popup al marker
marker.bindPopup("<b>Hello World!<b/><br>I'm a popup.").openPopup();
//referencia al botón para agregar listener
document.getElementById("btn").addEventListener("click", marcar)


//definir nombre del cliente
myName = "Changuito"
// Create instancia del cliente
client = new Paho.MQTT.Client("172.20.10.2", 9001, myName);

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});

//función para marcar en el mapa un nuevo marcador
function marcar(humedad){
  lat = document.getElementById("lat").value
  long = document.getElementById("long").value
  mensaje = document.getElementById("mensaje").value
  map.removeLayer(marker);
  marker = L.marker([lat, long]).addTo(map);
  marker.bindPopup(humedad).openPopup();
  console.log(lat + long + mensaje)
}

var markero;

function recargaForm(humedad){

if (markero) { // check

map.removeLayer(markero); // remove
map.removeControl(markero); // remove
}
map.removeLayer(marker);
markero = L.marker([19.541441433, -96.9270407593]);//.addTo(map);
map.addLayer(markero);
markero.bindPopup("<b>" + humedad + "</b><br>" + "Este es un ejercicio.").openPopup();
// $( "#map" ).load(window.location.href + " #map" );
}
//función para conectarse al publicador mosquito
function onConnect() {
  console.log("onConnect");
  client.subscribe("Hola");
  //message = new Paho.MQTT.Message("Hello");
  //message.destinationName = "World";
  //client.send(message);
}

function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

function sendMessage() {
  let mensaje = document.getElementById("mensajeMosquitto").value
  console.log(mensaje)
  client.subscribe("Hola");
  message = new Paho.MQTT.Message(mensaje+" enviado por: "+myName);
  message.destinationName = "Hola";
  client.send(message);
}

function onMessageArrived(message) {
  // console.log("onMessageArrived:"+message.payloadString);
  var json = JSON.parse(message.payloadString + "}");
  // console.log(json[""])
  var humedad = json["humedad"];
  // marcar(humedad);
  recargaForm(humedad);
  
}