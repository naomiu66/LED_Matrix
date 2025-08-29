#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

struct EspSettings
{
    String ssid;
    String pass;
    uint16_t port;
    String token;
};

class ServerManager {

public:
    ServerManager(const EspSettings& settings) : 
    _settings(settings),
    _server(_settings.port),
    _ws("/ws") {}

    void init();
    void update();

private:
    const EspSettings& _settings;
    AsyncWebServer _server;
    AsyncWebSocket _ws;
    WiFiEventHandler _gotIpHandler;
    WiFiEventHandler _disconnectedHandler;

    void startServer();
};

#endif