
var map = L.map('map').setView([19.546440, -96.904626], 13);
var marker = L.marker();

        L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
            maxZoom: 19,
            attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
        }).addTo(map);

        // marcador
        var marker = L.marker([19.546440, -96.904626]).addTo(map);

        // popup
        marker.bindPopup("<b>Hello world!</b><br>I am a popup.").openPopup();

document.getElementById("btn").addEventListener("click", marcar);

function marcar(){
    map.removeLayer(marker);
    var mapa = document.getElementById("map");
    latitud = document.getElementById("latitud").value;
    longitud = document.getElementById("longitud").value;
    mensaje = document.getElementById("mensaje").value;
    marker = L.marker([latitud, longitud]).addTo(map);

    // popup
    marker.bindPopup("<b>Mensaje</b><br>" + mensaje + ".").openPopup();
}