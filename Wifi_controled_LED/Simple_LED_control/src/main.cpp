#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

const char* ssid = "";
const char* password = "";

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

    pinMode(26, OUTPUT);
}

int value = 0;

void loop() {
    WiFiClient client = server.available();

    if (client) {
        Serial.print("New client");
        String currentLine = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);

                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
                        client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");
                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(26, HIGH);
                }
                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(26, LOW);
                }
            }
        }

        client.stop();
        Serial.println("client disconnected");
    }
}