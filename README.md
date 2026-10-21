# Canal nodo sensor

Proyecto de un nodo sensor basado en ESP32 para medir temperatura, humedad relativa y un valor analógico de un potenciómetro, y enviar la información a ThingSpeak mediante MQTT.

El desarrollo fue validado en una simulación realizada en Wokwi, y la adquisición de datos se gestionó con ThingSpeak para visualizar y registrar la telemetría.

## Descripción del proyecto

Este sistema utiliza:

- ESP32 como nodo de adquisición.
- Sensor DHT22 para medir temperatura y humedad.
- Potenciómetro para simular una variable analógica.
- LED indicador para mostrar el estado de conexión.
- MQTT para publicar datos en ThingSpeak.

## Simulación realizada

La implementación se probó en Wokwi, una plataforma de simulación para microcontroladores basada en entorno visual. Esto permitió validar el funcionamiento del firmware antes de desplegarlo físicamente.

Además, la integración con ThingSpeak se utilizó como plataforma de adquisición y visualización de datos en tiempo real.

## Hardware utilizado

- ESP32
- Sensor DHT22 conectado al GPIO15
- Potenciómetro conectado al GPIO34
- LED conectado al GPIO2
- Conexión Wi‑Fi para transmitir datos

## Requisitos

- PlatformIO
- Framework Arduino para ESP32
- Librerías:
  - DHT Sensor Library
  - Adafruit Unified Sensor
  - PubSubClient

## Configuración rápida

1. Clona este repositorio.
2. Instala PlatformIO.
3. Abre el proyecto con PlatformIO.
4. Modifica los parámetros de Wi‑Fi, MQTT y ThingSpeak en `src/main.cpp`.
5. Compila y sube el firmware al ESP32.
6. Verifica la conexión serial para diagnosticar errores.

## Variables de configuración importantes

Edita estos valores dentro de `src/main.cpp`:

- `WIFI_SSID`
- `WIFI_PASS`
- `MQTT_SERVER`
- `CLIENT_ID`
- `MQTT_USER`
- `MQTT_PASS`
- `CHANNEL_ID`

## Topología de publicación

El dispositivo publica los datos en el topic:

`channels/<CHANNEL_ID>/publish`

con un payload similar a:

`field1=24.2&field2=58.1&field3=65.3`

Donde:

- `field1`: temperatura
- `field2`: humedad
- `field3`: valor del potenciómetro

## Funcionamiento

El código realiza lo siguiente:

- Conecta el ESP32 a la red Wi‑Fi.
- Verifica y mantiene la conexión con el broker MQTT.
- Lee la temperatura y la humedad del DHT22.
- Obtiene el valor analógico del potenciómetro.
- Publica la información en ThingSpeak cada 10 segundos.
- Evita bloqueos usando lógica no bloqueante para reconexión y temporización.

## Consideraciones importantes

- La frecuencia de publicación está limitada por ThingSpeak y se controla con `INTERVALO_PUBLICACION`.
- El sistema usa reconexión automática a Wi‑Fi y MQTT.
- Si el sensor DHT22 falla, se muestra un mensaje en el puerto serial.
- La simulación en Wokwi ayuda a validar la lógica del sistema antes del despliegue real.

## Objetivo

El proyecto tiene como finalidad demostrar la adquisición de datos ambientales y analógicos desde un nodo sensor, y su envío a una plataforma IoT para almacenamiento y visualización remota mediante ThingSpeak.

## Licencia

Este proyecto se distribuye solo con fines educativos y de demostración.
