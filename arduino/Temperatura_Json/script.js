window.onload = update;
setInterval(update,6000);

function update(){
    // fetch('http://172.20.10.4/')
    fetch('http://192.168.0.104/')
    .then(response => response.json())
    .then(data => {
        agregar(data);
        console.log(data);
    })
}

// fetch('http://172.20.10.4/')
//     .then(response => response.json())
//     .then(data => {
//         agregar(data);
//         console.log(data);
//     })

function agregar(data){
    var aux = document.getElementById('tabla');
    let auxRow = aux.insertRow(-1);
    let auxCell = auxRow.insertCell(0);
    let auxCell2 = auxRow.insertCell(1);
    let auxCell3 = auxRow.insertCell(2);
    let auxCell4 = auxRow.insertCell(3);
    let auxCell5 = auxRow.insertCell(4);
    let auxCell6 = auxRow.insertCell(5);
    auxCell.textContent = data.status;
    auxCell2.textContent = data.humedad;
    auxCell3.textContent = data.temperatura;
    auxCell4.textContent = data.farenheit;
    auxCell5.textContent = data.sensacion;
    auxCell6.textContent = data.sensacion2;
    // setInterval("location.reload()",1000);
};
