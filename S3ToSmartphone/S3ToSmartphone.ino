#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <M5Unified.h>


const char* ssid = "KV-System";
const char* password = "kv123456";

WebServer server(80);
WebSocketsServer webSocket(81);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    
    webSocket.begin();
    Serial.println(WiFi.softAPIP());
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Display.setTextSize(2);     // 文字サイズ
    M5.Display.setCursor(0, 0);    // 表示位置
    M5.Display.print(WiFi.softAPIP());
    
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
        doc["temp"] = random(300, 500) / 10.0;

        String json;
        serializeJson(doc, json);
        webSocket.broadcastTXT(json);
        Serial.println(json);
    }
}