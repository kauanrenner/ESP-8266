#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Ameba";
const char* password = "xyz@1234";

const char* facul = "Funcesi";
const char* senha_facul = "Funcesi2023";

const char* teste = "POCO X6 Pro 5G";
const char* senha_teste = "iopasdf123";

int tentativa = 0;

const char* serverUrl = "https://render-server-2itn.onrender.com/commands";
const char* horario = "https://render-server-2itn.onrender.com/arduino";

String p_antes = "";

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && tentativa < 20){
    delay(1000);
    Serial.println("Conectando à rede AMEBA");
    tentativa += 1;
  }

  tentativa = 0;

  while (WiFi.status() != WL_CONNECTED && tentativa < 20)
  {
    WiFi.begin(facul, senha_facul);
    delay(1000);
    Serial.println("Conectando à rede FUNCESI. Tentativa: ");
    tentativa += 1;
  }

  tentativa = 0;

  while (WiFi.status() != WL_CONNECTED && tentativa < 20)
  {
    WiFi.begin(teste, senha_teste);
    delay(1000);
    Serial.println("Conectando à rede POCO. Tentativa: ");
    tentativa += 1;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Conectado!");
  }
}

void loop(){
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    WiFiClientSecure wifiClient;
    wifiClient.setInsecure();
    http.begin(wifiClient, serverUrl);
    int httpCode = http.GET();

    if (httpCode == 200){
      String payload = http.getString();
      Serial.println("Comando recebido: " + payload);

      if (payload.indexOf("ON") != -1)
      {
        Serial.println("LIGAR");
      } else if (payload.indexOf("OFF") != -1)
      {
        Serial.println("DESLIGAR");
      }
    }

    delay(250);

    http.begin(wifiClient, horario);
    httpCode = http.GET();
    if (httpCode == 200){
      String payload = http.getString();
      Serial.println("Horário Recebido: " + payload);
    }
  }

  delay(250);
}
