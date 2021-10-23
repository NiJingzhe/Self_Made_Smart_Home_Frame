#pragma once 

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
using namespace std;

class sender{

	sender(){}
	
	void send_message(WiFiUdp SEND_upd,WiFiUdp RECV_upd,char message[]){		
		SEND_udp.beginPacket(RECV_udp.remoteIP(), remote_port);
    	SEND_udp.write(message);
    	SEND_udp.endPacket();
	}
};
