#include <WiFi.h>
#include <WebServer.h>

// Credenciales WiFi
const char* ssid = "";
const char* password = "";

//  Servidor
WebServer server(80);

// 🔌 Pines relé
int relay1 = 13;
int relay2 = 12;
int relay3 = 27;
int relay4 = 26;

// Estado relés
bool state1 = false;
bool state2 = false;
bool state3 = false;
bool state4 = false;

// actualizar pines
void updateRelays() {
  digitalWrite(relay1, state1 ? LOW : HIGH);
  digitalWrite(relay2, state2 ? LOW : HIGH);
  digitalWrite(relay3, state3 ? LOW : HIGH);
  digitalWrite(relay4, state4 ? LOW : HIGH);
}

//  Panel web
String htmlPage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Control Domótico</title>

<style>
  body {
    font-family: Arial;
    background: #0f172a;
    color: white;
    text-align: center;
    margin: 0;
  }

  h2 {
    padding: 20px;
  }

  .container {
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  .card {
    background: #1e293b;
    width: 90%;
    max-width: 400px;
    padding: 20px;
    margin: 10px;
    border-radius: 15px;
    box-shadow: 0 0 10px rgba(0,0,0,0.5);
  }

  .btn {
    width: 100%;
    padding: 15px;
    font-size: 18px;
    border: none;
    border-radius: 10px;
    cursor: pointer;
    color: white;
  }

  .on {
    background-color: #22c55e;
  }

  .off {
    background-color: #ef4444;
  }

</style>
</head>

<body>

<h2>Panel Web Equipo-9</h2>

<div class="container">

  <div class="card">
    <h3>Foco 1</h3>
    <button class="btn" id="btn1" onclick="toggle(1)">Cargando...</button>
  </div>

  <div class="card">
    <h3>Foco 2</h3>
    <button class="btn" id="btn2" onclick="toggle(2)">Cargando...</button>
  </div>

  <div class="card">
    <h3>Foco 3</h3>
    <button class="btn" id="btn3" onclick="toggle(3)">Cargando...</button>
  </div>

  <div class="card">
    <h3>Foco 4</h3>
    <button class="btn" id="btn4" onclick="toggle(4)">Cargando...</button>
  </div>

</div>

<script>
function toggle(relay) {
  fetch("/r" + relay)
    .then(() => updateButtons());
}

function updateButtons() {
  fetch("/status")
    .then(res => res.json())
    .then(data => {
      updateButton("btn1", data.r1);
      updateButton("btn2", data.r2);
      updateButton("btn3", data.r3);
      updateButton("btn4", data.r4);
    });
}

function updateButton(id, state) {
  let btn = document.getElementById(id);
  if (state) {
    btn.innerHTML = "Encendido";
    btn.classList.add("on");
    btn.classList.remove("off");
  } else {
    btn.innerHTML = "Apagado";
    btn.classList.add("off");
    btn.classList.remove("on");
  }
}

// actualizar al cargar
updateButtons();
</script>

</body>
</html>
)rawliteral";

  return page;
}

// Controladores
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void toggleRelay1() {
  state1 = !state1;
  updateRelays();
  server.sendHeader("Location", "/");
  server.send(303);
}

void toggleRelay2() {
  state2 = !state2;
  updateRelays();
  server.sendHeader("Location", "/");
  server.send(303);
}

void toggleRelay3() {
  state3 = !state3;
  updateRelays();
  server.sendHeader("Location", "/");
  server.send(303);
}

void toggleRelay4() {
  state4 = !state4;
  updateRelays();
  server.sendHeader("Location", "/");
  server.send(303);
}


// Estatus de cada foco
void handleStatus() {
  String json = "{";
  json += "\"r1\":" + String(state1 ? "true" : "false") + ",";
  json += "\"r2\":" + String(state2 ? "true" : "false") + ",";
  json += "\"r3\":" + String(state3 ? "true" : "false") + ",";
  json += "\"r4\":" + String(state4 ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}


void setup() {
  Serial.begin(115200);

  // Configurar pines
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  updateRelays(); // apagados al inicio

  //  Conectar WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Endpoints
  server.on("/", handleRoot);
  server.on("/r1", toggleRelay1);
  server.on("/r2", toggleRelay2);
  server.on("/r3", toggleRelay3);
  server.on("/r4", toggleRelay4);
  server.on("/status", handleStatus);

  server.begin();
}

void loop() {
  server.handleClient();
}
