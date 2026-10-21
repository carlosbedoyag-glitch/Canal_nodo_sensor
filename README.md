# Canal nodo sensor

Proyecto de simulación de un nodo sensor basado en ESP32 para capturar temperatura, humedad y un valor analógico de un potenciómetro, y enviar esos datos a ThingSpeak mediante MQTT.

Este proyecto se desarrolló exclusivamente como simulación en Wokwi. No se realizó un despliegue físico real con PlatformIO ni una programación en hardware real durante esta etapa.

## Descripción del proyecto

El sistema simulado utiliza:

- ESP32 virtual en Wokwi
- Sensor DHT22 para temperatura y humedad
- Potenciómetro conectado al GPIO34
- LED indicador para mostrar el estado de la conexión
- MQTT para publicar datos a ThingSpeak

## Simulación realizada

La lógica del sistema se probó en Wokwi, una plataforma de simulación para microcontroladores. Esto permitió validar el comportamiento de:

- lectura del sensor DHT22
- lectura del potenciómetro
- conexión Wi‑Fi
- conexión MQTT
- publicación de datos en ThingSpeak

## Uso de ThingSpeak

La adquisición de datos se realizó usando ThingSpeak como plataforma IoT para recibir y registrar la telemetría enviada por el nodo simulado.

El dispositivo publica en el tópico:

`channels/<CHANNEL_ID>/publish`

Ejemplo de payload:

`field1=24.2&field2=58.1&field3=65.3`

Donde:

- `field1`: temperatura
- `field2`: humedad
- `field3`: valor del potenciómetro

## Estructura del repositorio

```text
Canal_nodo_sensor/
├── README.md
├── platformio.ini
├── .gitignore
└── src/
    └── main.cpp
```

## Archivos principales

### `src/main.cpp`

Contiene la lógica principal del nodo sensor:

- configuración de Wi‑Fi y MQTT
- conexión al broker de ThingSpeak
- lectura del sensor DHT22
- lectura del potenciómetro
- publicación periódica de datos

### `platformio.ini`

Este archivo existe como referencia de configuración para un entorno ESP32 con PlatformIO, pero en este caso la validación principal se realizó en Wokwi.

## Requisitos para la simulación

- Wokwi
- ESP32 virtual
- Acceso a internet para enviar datos a ThingSpeak
- Credenciales de Wi‑Fi y MQTT

## Variables importantes

En `src/main.cpp` se deben configurar:

- `WIFI_SSID`
- `WIFI_PASS`
- `MQTT_SERVER`
- `CLIENT_ID`
- `MQTT_USER`
- `MQTT_PASS`
- `CHANNEL_ID`

## Funcionamiento del firmware

El código ejecuta estas tareas:

1. Conecta el ESP32 a la red Wi‑Fi.
2. Verifica la conexión con el broker MQTT.
3. Lee la temperatura y humedad del DHT22.
4. Lee el valor analógico del potenciómetro.
5. Publica los datos en ThingSpeak.
6. Reintenta la conexión si ocurre algún fallo.

## Consideraciones

- La publicación en ThingSpeak está limitada por la frecuencia permitida por la plataforma.
- El intervalo de envío se controla con `INTERVALO_PUBLICACION`.
- La simulación en Wokwi permite probar la lógica del proyecto antes de una implementación real en hardware.
- La configuración actual del repositorio está orientada a un entorno una vez se quiera llevar a un ESP32 real, pero la verificación efectiva fue en Wokwi.

## Objetivo

Demostrar la adquisición y envío de datos ambientales y analógicos desde un nodo sensor IoT hacia una plataforma de monitoreo en la nube, validado en una simulación de Wokwi con ThingSpeak como backend de recepción.

## Nota importante

La versión actual del proyecto corresponde a una simulación funcional en Wokwi, no a un despliegue físico realizado con PlatformIO.
