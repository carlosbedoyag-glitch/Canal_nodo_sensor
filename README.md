# Canal nodo sensor

Proyecto para ESP32 que lee temperatura, humedad y un valor analógico desde un potenciómetro, y publica la telemetría a ThingSpeak mediante MQTT.

## Hardware

- ESP32
- Sensor DHT22 conectado al pin GPIO15
- Potenciómetro conectado al pin GPIO34
- LED indicador conectado al GPIO2

## Requisitos

- PlatformIO
- Framework Arduino para ESP32
- Librerías:
  - DHT Sensor Library
  - Adafruit Unified Sensor
  - PubSubClient

## Configuración rápida

1. Clona el repositorio.
2. Instala PlatformIO.
3. Abre este proyecto con PlatformIO.
4. Edita los valores de red y MQTT en `src/main.cpp`.
5. Compila y sube el firmware al ESP32.

## Variables importantes

Cambiar en `src/main.cpp`:

- `WIFI_SSID`
- `WIFI_PASS`
- `MQTT_SERVER`
- `CLIENT_ID`
- `MQTT_USER`
- `MQTT_PASS`
- `CHANNEL_ID`

## Topología de publicación

El código publica en el topic:

`channels/<CHANNEL_ID>/publish`

con payload similar a:

`field1=24.2&field2=58.1&field3=65.3`

## Consideraciones

- La tasa de publicación está limitada para ThingSpeak y se regula con `INTERVALO_PUBLICACION`.
- El código usa una lógica no bloqueante para reconectar WiFi y MQTT.
- Si el DHT22 falla, se imprime un mensaje en el puerto serial.
