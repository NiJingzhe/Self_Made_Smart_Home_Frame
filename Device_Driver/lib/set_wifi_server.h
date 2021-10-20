#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WString.h>
using namespace std;

//const int led = LED_BUILTIN;

class set_wifi_server{
private:
    unsigned int port;
    char ssid[];
    char passwd[];
    ESP8266WebServer server;
    const String postForms = "<html>\
                                <head>\
                                    <title>配网界面</title>\
                                    <style>\
                                        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
                                    </style>\
                                </head>\
                                <body>\
                                    <h1>输入WiFi的ssid和密码</h1><br>\
                                    <form method=\"post\" action=\"/setwifi/\">\
                                        <input type=\"text\" name=\"ssid\"}\'><br>\
                                        <input type=\"text\" name=\"passwd\"}\'><br>\
                                        <input type=\"submit\" value=\"Submit\">\
                                </body>\
                            </html>";

    set_wifi_server(unsigned int port):port(port),server(ESP8266WebServer(port)){}

    void handleRoot() {
        server.send(200, "text/html", postForms);
    }

    void handleForm() {
        if (server.method() != HTTP_POST) {
            server.send(405, "text/plain", "Method Not Allowed");
        } else {
            String message = "POST form was:\n";
            for (uint8_t i = 0; i < server.args(); i++) {
                message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
            }
            server.send(200, "text/plain", message);
        }
    }

}

