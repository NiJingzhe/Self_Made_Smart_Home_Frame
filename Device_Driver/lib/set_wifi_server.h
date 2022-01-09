#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WString.h>

//const int led = LED_BUILTIN;

class set_wifi_server{
public:
    unsigned int port;
    String ssid;
    String passwd;
    ESP8266WebServer server;
    
public:
    set_wifi_server(void (*handle_root)(), void (*set_wifi)()):server(ESP8266WebServer(80)){
        this->ssid = "";
        this->passwd = "";
        this->server.on("/",(*handle_root));
        this->server.on("/set_wifi/",(*set_wifi));
    }


    void start_server() {
        this->server.begin();
    }

    void run(){
        this->server.handleClient();
    }

    String get_ssid(){ return this->ssid; }
    String get_passwd(){ return this->passwd; }

};




