#include <WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>

// --- CONFIGURACIÓN DE RED Y MQTT ---
const char* WIFI_SSID = "TU_SSID";
const char* WIFI_PASS = "TU_PASSWORD";

const char* MQTT_SERVER = "mqtt3.thingspeak.com";
const int MQTT_PORT = 1883;

// --- CREDENCIALES DE THINGSPEAK ---
const char* CLIENT_ID = "TU_CLIENT_ID";
const char* MQTT_USER = "TU_MQTT_USER";
const char* MQTT_PASS = "TU_MQTT_PASSWORD";
const char* CHANNEL_ID = "3543582";

// --- PINES DE HARDWARE ---
#define DHTPIN 15
#define DHTTYPE DHT22
#define POT_PIN 34
#define LED_PIN 2

// --- TIEMPOS DE MUESTREO (RESTRICCIÓN THINGSPEAK) ---
const unsigned long INTERVALO_PUBLICACION = 2000; // 2 segundos
unsigned long ultimaPublicacion = 0;

// --- OBJETOS ---
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// --- CONTROL DE RED Y WIFI ---
void verificarConexionWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    return;
  }

  digitalWrite(LED_PIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long inicioIntento = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicioIntento < 5000) {
    delay(250);
  }
}

// --- MANEJO DE EXCEPCIONES Y RECONEXIÓN AL BROKER ---
bool asegurarConexionBroker() {
  verificarConexionWiFi();

  if (WiFi.status() != WL_CONNECTED) {
    return false; // Error de red física
  }

  if (mqttClient.connected()) {
    return true;
  }

  // Intento de reconexión al broker
  if (mqttClient.connect(CLIENT_ID, MQTT_USER, MQTT_PASS)) {
    Serial.println("Conectado exitosamente al Broker MQTT!");
    return true;
  } else {
    Serial.print("Fallo conexion MQTT, rc=");
    Serial.println(mqttClient.state());
    return false;
  }
}

// --- LECTURA DE SENSORES ---
void leerSensores(float &temp, float &hum, float &potPorcentaje) {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  int valorADC = analogRead(POT_PIN);
  potPorcentaje = (valorADC / 4095.0) * 100.0;
}

// --- PUBLICACIÓN DE TELEMETRÍA ---
void publicarTelemetria(float temp, float hum, float pot) {
  String topico = "channels/" + String(CHANNEL_ID) + "/publish";
  String payload = "field1=" + String(temp, 1) +
                  "&field2=" + String(hum, 1) +
                  "&field3=" + String(pot, 1);

  if (mqttClient.publish(topico.c_str(), payload.c_str())) {
    Serial.print("Datos enviados correctamente: ");
    Serial.println(payload);
  } else {
    Serial.println("Error al publicar datos en ThingSpeak");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setKeepAlive(15);

  verificarConexionWiFi();
}

void loop() {
  // Manejo no bloqueante de reconexión y ciclo de eventos MQTT
  if (asegurarConexionBroker()) {
    mqttClient.loop();
  }

  // Control de tiempo sin usar delay()
  unsigned long tiempoActual = millis();
  if (tiempoActual - ultimaPublicacion >= INTERVALO_PUBLICACION) {
    ultimaPublicacion = tiempoActual;

    if (mqttClient.connected()) {
      float temperatura = 0.0;
      float humedad = 0.0;
      float potenciometro = 0.0;

      leerSensores(temperatura, humedad, potenciometro);

      // Verificación de integridad de datos antes de enviar
      if (!isnan(temperatura) && !isnan(humedad)) {
        publicarTelemetria(temperatura, humedad, potenciometro);
      } else {
        Serial.println("Error al leer el sensor DHT22");
      }
    }
  }
}
