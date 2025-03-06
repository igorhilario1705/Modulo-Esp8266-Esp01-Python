#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Nome da rede wifi";       
const char* password = "Senha da rede"; 

ESP8266WebServer server(80);

const int rele = 0; // O relé do módulo ESP-01 está ligado ao GPIO0
bool estadoRele = false;

void handleRoot() {
    String paginaHTML = "<html><head><title>Controle de Relé</title></head><body>";
    paginaHTML += "<h1>Controle do Rele</h1>";
    paginaHTML += "<p>Estado atual: " + String(estadoRele ? "Ligado" : "Desligado") + "</p>";
    paginaHTML += "<button onclick=\"window.location.href='/toggle'\">";
    paginaHTML += estadoRele ? "Desligar" : "Ligar";
    paginaHTML += "</button>";
    paginaHTML += "</body></html>";
    server.send(200, "text/html", paginaHTML);
}

void handleToggle() {
    estadoRele = !estadoRele;
    digitalWrite(rele, estadoRele ? LOW : HIGH); // O módulo ativa o relé com LOW
    server.sendHeader("Location", "/");
    server.send(303);
}

void setup() {
    pinMode(rele, OUTPUT);
    digitalWrite(rele, HIGH); // O relé começa desligado

    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado ao Wi-Fi");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/toggle", handleToggle);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    server.handleClient();
}

// O IP é: http://192.168.0.48/
