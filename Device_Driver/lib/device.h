#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
#include "sender.h"
#include "receiver.h"
#include "set_wifi_server.h"
using namespace std;

class device{
private:
	WiFiUDP SEND_udp,RECV_udp;
	set_wifi_server server;
	unsigned int ssid,passwd,AP_ssid,AP_passwd;
	unsigned int RECV_port,SEND_port;
	char name[255];
	
	device(
		char name_[],
		unsigned int AP_ssid_,unsigned int AP_passwd_,
		//WiFiUDP SEND_udp_,WiFiUDP RECV_udp_,
		unsigned int SEND_port_,unsigned int RECV_port_,unsigned int server_port_,
		):
		name(name_),
		AP_ssid(AP_ssid_),AP_passwd(AP_passwd_),
		SEND_port(SEND_port_),RECV_port(RECV_port_),server(set_wifi_server(server_port_))
		SEND_udp(WiFiUDP()),RECV_udp(WiFiUDP())
		{
			
			//WiFi.mode(WIFI_STA);
			WiFi.softAP(this->ssid,this->passwd);
			while (WiFi.status() != WL_CONNECTED) {
				Serial.print('.');
				delay(500);
			}
			Serial.print("Connected! IP address: ");
			Serial.println(WiFi.localIP());

			this->SEND_udp.begin(this->SEND_port);
			this->RECV_udp.begin(this->RECV_port);
		}
}

