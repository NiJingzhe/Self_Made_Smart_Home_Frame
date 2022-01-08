#pragma once 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>


class sender{
public:
	sender(){}
	~sender(){}
	void send_message(WiFiUDP SEND_udp,WiFiUDP RECV_udp,String message,int remotePort){		
		SEND_udp.beginPacket(RECV_udp.remoteIP(), remotePort);
    	SEND_udp.write(message.c_str());
    	SEND_udp.endPacket();
	}
};
