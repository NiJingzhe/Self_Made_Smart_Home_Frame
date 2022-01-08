#pragma once
#include <map>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WString.h>
#include "webpage/wifi_setting_html.h"

//const int led = LED_BUILTIN;

class set_wifi_server{
private:
    unsigned int port;
    String ssid;
    String passwd;
    ESP8266WebServer server;
    String postForms = wifi_setting_html;
    
public:
    set_wifi_server(unsigned int port, void (*handle_root)(), void (*set_wifi)()):port(port),server(ESP8266WebServer(port)){
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




