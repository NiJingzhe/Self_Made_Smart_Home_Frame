#pragma once 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
using namespace std;

class sender{

	sender(){}
	
	void send_message(WiFiUdp SEND_upd,WiFiUdp RECV_upd,char message[],int remotePort){		
		SEND_udp.beginPacket(RECV_udp.remoteIP(), remotePort);
    	SEND_udp.write(message);
    	SEND_udp.endPacket();
	}
};
