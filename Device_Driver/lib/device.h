#pragma once

#include <map>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
#include "sender.h"
#include "receiver.h"
#include "eeprom.h"
#include "command_processer.h"
using namespace std;

class device{
public:	

	WiFiUDP SEND_udp,RECV_udp;
	sender SENDER;
	receiver RECEIVER;
	String ssid,passwd;
	unsigned int RECV_port,SEND_port;
	String name;
	rom ROM;
	command_processer processer;

public:	

	bool need_set_wifi;
	String device_state;
	int device_value;

	device(
		char * name_,
		//WiFiUDP SEND_udp_,WiFiUDP RECV_udp_,
		unsigned int SEND_port_,unsigned int RECV_port_
		):
		name(name_),
		SEND_port(SEND_port_),RECV_port(RECV_port_),
		SEND_udp(WiFiUDP()),RECV_udp(WiFiUDP()),
		SENDER(sender()),RECEIVER(receiver()),
		ROM(rom(4095)),processer(command_processer()),
		need_set_wifi(false)
		{
			SEND_udp.begin(SEND_port);
			RECV_udp.begin(RECV_port);
			this->device_value = 0;
			this->device_state = "关闭";
			Serial.begin(115200);
		}
		
		~device();

		bool check_ssid_and_passwd();
		void run();
		void bind(char * command,void (*pf)());
};

bool device::check_ssid_and_passwd(){

	int length_of_ssid = ROM.read_data(1);
	for(int i = 2; i<=1+length_of_ssid; i++){
		this->ssid += ROM.read_data(i);
	}

	int length_of_password = ROM.read_data(256);
	if(length_of_password == 0) 
		this->passwd = "";
	else
		for(int i = 257; i<=256+length_of_password; i++){
			this->passwd += ROM.read_data(i);
		}



	if((this->ssid != "")){
		Serial.println("ssid: "+this->ssid+" password: "+this->passwd);
		this->need_set_wifi = false;
		WiFi.begin(this->ssid,this->passwd);
		return true;
	}
	else{
		Serial.println("Starting Set WiFi Server");
		this->need_set_wifi = true;
		return false;
	}

}

void device::run(){
	//if(this->need_set_wifi)
	//	return;

	JSONVar command = RECEIVER.receive(RECV_udp);
	String task_state;
	if(command.hasOwnProperty("device_name"))
		if((const char *)command["device_name"] == this->name.c_str()){
			task_state = this->processer.process(command)? "finished" : "unfinished";
		}
			
	
	JSONVar feedback;
	feedback["device_name"] = this->name;
	feedback["command"] = "feedback";
	JSONVar result;
	result["device_state"] = this->device_state;
	result["device_value"] = "";
	result["task_state"] = task_state;
	feedback["result"] = result;

	String feedback_string = JSON.stringify(feedback);

	SENDER.send_message(SEND_udp,RECV_udp,feedback_string,this->SEND_port);

}

void device::bind(char * command, void (*pf)()){
	this->processer.action_list.insert(make_pair(command,(*pf)));
}

device::~device(){}


