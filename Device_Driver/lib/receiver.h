#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
using namespace std;

class receiver{
private:
	char RECV_buffer[UDP_TX_PACKET_MAX_SIZE+1];
	
	receiver(){}
	
	JSONVar receive(WiFiUdp udp){
		int packetSize = Udp.parsePacket();
		if (packetSize) {
		Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
		              packetSize,
		              udp.remoteIP().toString().c_str(), udp.remotePort(),
		              udp.destinationIP().toString().c_str(), udp.localPort(),
		              ESP.getFreeHeap());
		
		int n = udp.read(RECV_buffer, UDP_TX_PACKET_MAX_SIZE);
		RECV_buffer[n] = 0;
		JSONVar message = JSON.prase(RECV_buffer)
		return message;
	}
}
