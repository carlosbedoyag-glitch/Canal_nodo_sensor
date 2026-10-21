# Canal nodo sensor

Proyecto de simulación de un nodo sensor basado en ESP32 para medir temperatura, humedad y un valor analógico desde un potenciómetro, y enviar la información a ThingSpeak mediante MQTT.

Este proyecto fue desarrollado y validado en una simulación realizada en Wokwi. No se realizó una implementación física ni un despliegue real en hardware durante esta etapa.

## Descripción del proyecto

El sistema simulado utiliza:

- ESP32 virtual en Wokwi
- Sensor DHT22 para medir temperatura y humedad
- Potenciómetro conectado al GPIO34
- LED indicador para mostrar el estado de conexión
- Protocolo MQTT para publicar los datos en ThingSpeak

## Simulación realizada

La lógica del proyecto fue probada en Wokwi, una plataforma de simulación para microcontroladores, con el objetivo de verificar:

- lectura del sensor DHT22
- lectura del valor analógico del potenciómetro
- conexión Wi‑Fi
- conexión MQTT
- publicación de datos hacia ThingSpeak

## Adquisición de datos con ThingSpeak

La adquisición de datos se realizó mediante ThingSpeak, que actuó como plataforma IoT para recibir y registrar la telemetría enviada por el nodo simulado.

El dispositivo publica datos en el topic:

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
- lectura del DHT22
- lectura del potenciómetro
- publicación periódica de datos

### `platformio.ini`

Archivo de configuración para un entorno ESP32 con PlatformIO, aunque la validación principal se realizó en Wokwi.

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

El código realiza las siguientes tareas:

1. Conecta el ESP32 a la red Wi‑Fi.
2. Verifica la conexión con el broker MQTT.
3. Lee la temperatura y humedad del DHT22.
4. Lee el valor analógico del potenciómetro.
5. Publica los datos en ThingSpeak.
6. Reintenta la conexión si ocurre un error.

## Consideraciones

- La publicación de datos está limitada por la frecuencia permitida por ThingSpeak.
- El intervalo de envío se controla con `INTERVALO_PUBLICACION`.
- La simulación en Wokwi permite validar la lógica del proyecto antes de una implementación real.
- La configuración actual del repositorio está orientada a un entorno ESP32 real, pero la verificación efectuada fue en simulación.

## Objetivo

Demostrar la adquisición y envío de datos ambientales y analógicos desde un nodo sensor IoT hacia una plataforma de monitoreo en la nube, validado en una simulación de Wokwi con ThingSpeak como backend de recepción.

## Nota importante

Este proyecto corresponde a una simulación funcional en Wokwi y no a un montaje físico real en hardware.
