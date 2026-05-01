#include <WiFi.h>
#include <WiFiClientSecure.h>   
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid     = "Wokwi-GUEST";
const char* password = "";         

const char* mqtt_server = "3c63db4cbaf348a08ce33fae7f1aea6f.s1.eu.hivemq.cloud"; // ← sem http://
const int   mqtt_port   = 8883;
const char* mqtt_user   = "Wokwi-GUEST";
const char* mqtt_pass   = "Moises12@";

const char* topic_ultra   = "grama/sensor/ultrassom";
const char* topic_umidade = "grama/sensor/umidade";

WiFiClientSecure espClient;             
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi OK");
}

void reconnect() {
  while (!client.connected()) {

    if (client.connect("ESP32_Simulador", mqtt_user, mqtt_pass)) {
      Serial.println("MQTT conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

float lerUltrassom() {
  digitalWrite(5, LOW);
  delayMicroseconds(2);
  digitalWrite(5, HIGH);
  delayMicroseconds(10);
  digitalWrite(5, LOW);
  long duracao = pulseIn(18, HIGH, 30000);
  return duracao * 0.034 / 2;
}

float lerUmidade() {
  int valor = analogRead(34);
  return (valor / 4095.0) * 100.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(18, INPUT);

  setup_wifi();

  espClient.setInsecure();              
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float distancia = lerUltrassom();
  float umidade   = lerUmidade();

  StaticJsonDocument<200> doc1;
  doc1["sensor"] = "ultrassom";
  doc1["valor"]  = distancia;
  char buffer1[200];
  serializeJson(doc1, buffer1);

  StaticJsonDocument<200> doc2;
  doc2["sensor"] = "umidade";
  doc2["valor"]  = umidade;
  char buffer2[200];
  serializeJson(doc2, buffer2);

  client.publish(topic_ultra,   buffer1);
  client.publish(topic_umidade, buffer2);

  Serial.println("-----");
  Serial.println(buffer1);
  Serial.println(buffer2);

  delay(2000);
}

