#include <WiFi.h>
#include <HTTPClient.h>
#include <Servo.h>

const char* ssid = "tu_SSID";
const char* password = "tu_CONTRASEÑA";
const char* serverName = "http://tuservidor.com/insertar_datos.php"; // URL del script PHP

const int trigPin = 32;  // Ajusta los pines según tu placa ESP32
const int echoPin = 33;
const int foodDispenserPin = 25;

long duracion;
float distancia;
Servo servoComida;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoComida.attach(foodDispenserPin);
  servoComida.write(0);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  // Medir la distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia > 10) { // Umbral para determinar si el plato está vacío
    Serial.println("El plato está vacío.");
    rellenarComida();
  } else {
    Serial.println("El plato contiene comida.");
  }

  delay(5000); // Espera 5 segundos antes de la próxima lectura
}

void rellenarComida() {
  // Activa el servo para dispensar comida
  servoComida.write(90); // Ajusta el ángulo según tu dispensador
  delay(2000); // 2 segundos (ajusta según la cantidad de comida necesaria)
  servoComida.write(0);

  Serial.println("Plato rellenado con comida.");

  // Enviar datos al servidor
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String datosHTTP = "distancia=" + String(distancia);
    int codigoRespuestaHTTP = http.POST(datosHTTP);

    if (codigoRespuestaHTTP > 0) {
      String respuesta = http.getString();
      Serial.println(codigoRespuestaHTTP);
      Serial.println(respuesta);
    } else {
      Serial.print("Error en la conexión: ");
      Serial.println(codigoRespuestaHTTP);
    }
    http.end();
  } else {
    Serial.println("Error en la conexión WiFi");
  }
}