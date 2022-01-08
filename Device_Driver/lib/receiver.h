#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>

class receiver{
private:
	char RECV_buffer[UDP_TX_PACKET_MAX_SIZE+1];
public:	
	receiver(){}
	~receiver(){}
	JSONVar receive(WiFiUDP RECV_udp){
		int packetSize = RECV_udp.parsePacket();
		JSONVar message = NULL;
		if (packetSize) {
		/*Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
		              packetSize,
		              udp.remoteIP().toString().c_str(), udp.remotePort(),
		              udp.destinationIP().toString().c_str(), udp.localPort(),
		              ESP.getFreeHeap()); */
		
			int n = RECV_udp.read(RECV_buffer, UDP_TX_PACKET_MAX_SIZE);
			RECV_buffer[n] = 0;
			message = JSON.parse(RECV_buffer);
			
		}
		return message;
	}
};
