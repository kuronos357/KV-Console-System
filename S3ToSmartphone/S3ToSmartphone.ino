#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

const char* ssid = "KV-System";
const char* password = "kv123456";

WebSocketsServer webSocket(81);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    webSocket.begin();
    Serial.println(WiFi.softAPIP());
}

void loop() {
    webSocket.loop();

    static unsigned long lastSend = 0;
    if (millis() - lastSend >= 200) {
        lastSend = millis();

        JsonDocument doc;
        doc["bv"] = random(230, 250) / 10.0;
        doc["bc"] = random(30, 50) / 10.0;
        doc["mv"] = random(220, 240) / 10.0;
        doc["mc"] = random(150, 170) / 10.0;
        doc["speed"] = random(200, 300) / 10.0;

        String json;
        serializeJson(doc, json);
        webSocket.broadcastTXT(json);
    }
}