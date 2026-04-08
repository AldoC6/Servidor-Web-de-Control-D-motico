# Servidor Web de Control Domótico con ESP32

Proyecto de control domótico basado en un ESP32 que aloja un servidor web local.  
Permite encender y apagar 4 focos (o cualquier dispositivo eléctrico) mediante una interfaz web accesible desde cualquier navegador dentro de la misma red WiFi.

---

##  Descripción

Este sistema utiliza un ESP32 conectado a un módulo de 4 relés para controlar dispositivos eléctricos.  
El ESP32 actúa como servidor web y proporciona una interfaz gráfica donde el usuario puede:

- Encender/apagar focos
- Visualizar el estado actual de cada relé
- Controlar todo desde su celular o computadora

---

##  Requisitos e instalación

### Hardware necesario
- ESP32
- Módulo de 4 relés
- Fuente de alimentación (5V recomendada)
- Cables de conexión
- Focos o dispositivos eléctricos

###  Software necesario
- Arduino IDE (versión 2.x recomendada)
- Librerías:
  - `WiFi.h`
  - `WebServer.h`

---

###  Conexión básica

| Relé | GPIO ESP32 |
|------|-----------|
| Relay 1 | 13 |
| Relay 2 | 12 |
| Relay 3 | 27 |
| Relay 4 | 26 |

---

### Instalación

1. Clonar o descargar el repositorio
2. Abrir el código en Arduino IDE
3. Configurar credenciales WiFi:

```cpp
const char* ssid = "TU_WIFI";
const char* password = "TU_PASSWORD";

```

4. Seleccionar la placa ESP32 en:

   - Herramientas → Placa → ESP32 Dev Module

5. Seleccionar el puerto COM correcto

6. Subir el código al ESP32

---

## Cómo usarlo

1. Abrir el Monitor Serial (115200 baudios)

2. Esperar a que el ESP32 se conecte al WiFi

3. Copiar la dirección IP que aparece:
```
IP: 192.168.X.X
```

4. Abrir esa IP en el navegador (celular o PC en la misma red)

---

###  Interfaz web

- Botones para cada foco
- Indicador de estado:
  - 🟢 Encendido
  - 🔴 Apagado

---

### Endpoints disponibles

| Endpoint | Descripción |
|---------|------------|
| `/` | Página principal |
| `/r1` | Cambia estado del relay 1 |
| `/r2` | Cambia estado del relay 2 |
| `/r3` | Cambia estado del relay 3 |
| `/r4` | Cambia estado del relay 4 |
| `/status` | Devuelve estados en JSON |

---

### Ejemplo de respuesta `/status`

```json
{
  "r1": true,
  "r2": false,
  "r3": true,
  "r4": false
}
```

### Flujo de funcionamiento

1. Usuario presiona botón en la web  
2. Se hace una petición HTTP (`/r1`, `/r2`, etc.)  
3. El ESP32 cambia el estado del relé  
4. Se consulta `/status`  
5. La interfaz actualiza los botones automáticamente  

---

##  Estructura del proyecto
```
Servidor-Web-de-Control-Domotico/
│
├── main.ino # Código principal del ESP32
├── README.md # Documentación del proyecto

```


