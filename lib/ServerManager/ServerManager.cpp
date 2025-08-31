#include <ServerManager.h>

void ServerManager::init() {
    Serial.println("Connecting to WiFi: " + _settings.ssid);
    int n = WiFi.scanNetworks();
    Serial.println("Available Networks: ");
    for(int i = 0; i < n; i++)
    {
        Serial.println(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm)");
    }
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(_settings.ssid.c_str(), _settings.pass.c_str());

    _gotIpHandler = WiFi.onStationModeGotIP([this](const WiFiEventStationModeGotIP &event){
        Serial.println("Wifi Connected, IP: " + WiFi.localIP().toString());
        startServer();

    });

    _disconnectedHandler = WiFi.onStationModeDisconnected([this](const WiFiEventStationModeDisconnected &event){
        Serial.print("Wifi disconnected, status code: ");
        Serial.println(WiFi.status());
    });
}

void ServerManager::update() {
    _ws.cleanupClients();
}

void ServerManager::startServer() {
    _ws.onEvent([](AsyncWebSocket *server,
        AsyncWebSocketClient *client, 
        AwsEventType type, 
        void *arg, 
        uint8_t *data, 
        size_t len
    ) {
        if (type == WS_EVT_CONNECT) {
            Serial.printf("Client connected: %s\n", client->remoteIP().toString().c_str());
            client->text("Hello world! from esp8266");
        }
        else if (type == WS_EVT_DATA) {
            String msg = "";
            for(size_t i = 0; i < len; i++) {
                msg += (char)data[i];
            }
            Serial.printf("Received from Client %s: %s\n", client->remoteIP().toString().c_str(), msg.c_str());
        }
        else if (type == WS_EVT_DISCONNECT) {
            Serial.printf("Client %s disconnected\n", client->remoteIP().toString().c_str());
        }
    });

    _server.addHandler(&_ws);
    _server.begin();

    Serial.println("WebSocket server started!");
}
