#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WString.h>
#include "webpage/wifi_setting_html.h"
using namespace std;

//const int led = LED_BUILTIN;

class set_wifi_server{
private:
    unsigned int port;
    String ssid;
    String passwd;
    ESP8266WebServer server;
    String postForms = wifi_setting_html;

    set_wifi_server(unsigned int port):port(port),server(ESP8266WebServer(port)){
        this->ssid = "";
        this->passwd = "";
    }

    void handleRoot() {
        this->server.send(200, "text/html", postForms);
    }

    void set_wifi() {
        if (this->server.method() != HTTP_POST) {
            this->server.send(405, "text/plain", "Method Not Allowed");
        } else {
            //String message = "POST form was:\n";
            this->ssid = this->server.arg(0);
            this->passwd = this->server.arg(1);
            Serial.println(this->ssid, this->passwd);
            String message = "<html>\
                                <head>\
                                    <title>配网界面</title>\
                                    <style>\
                                        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
                                    </style>\
                                </head>\
                                <body>\
                                    <h4>你设置的WiFi名称为：" + this->ssid + "密码为：" + this->passwd + "</h4>" + '\n' + 
                                    "<script type=\"text/javascript\">\
                                        setInterval("myInterval()",3000);//1000为1秒钟
                                        function myInterval()
                                        {
                                            window.location.href=\"/\"
                                        }\
                                    </script>" + '\n' +
                                "</body>\
                             </html>"
            this->server.send(200,"text/plain",message);
            //server.send(200, "text/plain", message);
        }
    }

    void start_server() {
        this->server.on("/",handleRoot);
        this->server.on("/set_wifi/",set_wifi);
        this->server.begin();
    }

    void run(){
        this->server.handleClint();
    }

    String get_ssid(){ return this->ssid; }
    String get_passwd(){ return this->passwd; }

};

