#pragma once

#define FUCNTION_BTN_IN 5 
#define FUNCTION_BTN_OUT 4

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
	char * name;
	rom ROM;
	command_processer processer;
	//bool ap_state = false;

public:	

	//bool need_set_wifi;
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
			/*pinMode(LED_BUILTIN, OUTPUT);
			pinMode(FUCNTION_BTN_IN,INPUT);
			pinMode(FUNCTION_BTN_OUT,OUTPUT);
			digitalWrite(FUNCTION_BTN_OUT,HIGH);*/

			SEND_udp.begin(SEND_port);
			RECV_udp.begin(RECV_port);
			this->device_value = 0;
			this->device_state = "关闭";
			Serial.begin(115200);
		}
		
		~device();

		bool check_ssid_and_passwd();
		void run();
		void bind(const char * command,void (*pf)());
		void openAP();
		void disconnectAP();
};

bool device::check_ssid_and_passwd(){

	int length_of_ssid = ROM.read_data(1);
	//int index = 1;
	for(int i = 2; i<=1+length_of_ssid; i++){
		this->ssid += (char)ROM.read_data(i);
		//index++;
	}

	int length_of_password = ROM.read_data(256);
	//index = 1;
	if(length_of_password == 0) 
		this->passwd = "";
	else
		for(int i = 257; i<=256+length_of_password; i++){
			this->passwd += (char)ROM.read_data(i);
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

	/*Serial.println(digitalRead(FUCNTION_BTN_IN));
	if((!ap_state) && (digitalRead(FUCNTION_BTN_IN) == HIGH)){
		Serial.println("HIGH in FB and openAP");
		this->openAP();
	}
	if((ap_state) && (digitalRead(FUCNTION_BTN_IN) == HIGH)){
		Serial.println("HIGH in FBI and disconnectAP");
		this->disconnectAP();
	} */

	bool task_state = false;
	JSONVar command = RECEIVER.receive(RECV_udp);
	//String task_state;
	if(command.hasOwnProperty("device_name")){

		//因为一些奇奇怪怪的原因，如果把command中的device_name字段直接转换类型后比较就会出问题，
		//于是把device的name封装为一个json对象，即反向操作
		JSONVar tmpjson;
		tmpjson["device_name"] = this->name;

		if(command["device_name"] == tmpjson["device_name"]){
			Serial.println((const char *)command["command"]);
			task_state = this->processer.process(command);

			JSONVar feedback;
			feedback["device_name"] = this->name;
			feedback["command"] = "feedback";
			JSONVar result;
			result["device_state"] = this->device_state;
			result["device_value"] = "";
			result["task_state"] = task_state ? "finished" : "unfinish";
			feedback["result"] = result;

			String feedback_string = JSON.stringify(feedback);

			SENDER.send_message(SEND_udp,RECV_udp,feedback_string,this->SEND_port);
		}
	}
}

void device::bind(const char * command, void (*pf)()){
	//JSONVar tmp;
	//tmp["command"] = command;
	this->processer.action_list.insert(std::make_pair(command, pf));
}

void device::openAP(){
	WiFi.softAP(this->name);
	digitalWrite(LED_BUILTIN,LOW);
	this->ap_state = true;
}

void device::disconnectAP(){
	WiFi.disconnect();
	digitalWrite(LED_BUILTIN,HIGH);
	this->ap_state = false;
}

device::~device(){}


