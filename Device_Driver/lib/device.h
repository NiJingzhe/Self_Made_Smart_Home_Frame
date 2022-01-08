#pragma once

#include <map>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Arduino_JSON.h>
#include "sender.h"
#include "receiver.h"
#include "set_wifi_server.h"
#include "eeprom.h"
#include "command_processer.h"
using namespace std;

static void handleRoot();
static void set_wifi();

class device{
private:
	WiFiUDP SEND_udp,RECV_udp;
	sender SENDER;
	receiver RECEIVER;
	set_wifi_server server;
	String ssid,passwd;
	unsigned int RECV_port,SEND_port;
	char * name;
	rom ROM;
	command_processer processer;
	bool need_set_wifi;


public:	

	String device_state;
	int device_value;

	device(
		char * name_,
		//WiFiUDP SEND_udp_,WiFiUDP RECV_udp_,
		unsigned int SEND_port_,unsigned int RECV_port_,unsigned int server_port_
		):
		name(name_),
		SEND_port(SEND_port_),RECV_port(RECV_port_),server(set_wifi_server(server_port_,handleRoot,set_wifi)),
		SEND_udp(WiFiUDP()),RECV_udp(WiFiUDP()),
		SENDER(sender()),RECEIVER(receiver()),
		ROM(rom(4095)),processer(command_processer()),
		need_set_wifi(false)
		{
			SEND_udp.begin(SEND_port);
			RECV_udp.begin(RECV_port);
			this->device_value = 0;
			this->device_state = "close";
		}
		
		~device();

		bool check_ssid_and_passwd();
		void start_set_wifi();
		void set_wifi_server_run();
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
		this->need_set_wifi = false;
		WiFi.begin(this->ssid,this->passwd);
		return true;
	}
	else{
		this->need_set_wifi = true;
		return false;
	}

}

void device::start_set_wifi(){
	WiFi.mode(WIFI_AP_STA);
	WiFi.softAP(this->name);
	this->server.start_server();

}

void device::set_wifi_server_run(){
	if(this->need_set_wifi)
		this->server.run();
		this->ssid = this->server.get_ssid();
		this->passwd = this->server.get_passwd();
		if(this->ssid != ""){
			ROM.write_String_data(1,this->ssid);
			ROM.write_String_data(256,this->passwd);
			need_set_wifi = false;
			WiFi.softAPdisconnect(true);
			WiFi.begin(this->ssid,this->passwd);
		}
	else
		return;
}

void device::run(){
	if(this->need_set_wifi)
		return;

	JSONVar command = RECEIVER.receive(RECV_udp);
	bool task_state;
	if(command.hasOwnProperty("device_name"))
		if(command["device_name"].stringify().c_str() == this->name){
			task_state = this->processer.process(command);
		}
			
	
	JSONVar feedback;
	feedback["device_name"] = this->name;
	feedback["command"] = "feedback";
	JSONVar result;
	result["device_state"] = this->device_state;
	result["device_value"] = this->device_value;
	result["task_state"] = task_state;
	feedback["result"] = result;

	String feedback_string = JSON.stringify(feedback);

	SENDER.send_message(SEND_udp,RECV_udp,feedback_string,this->SEND_port);

}

void device::bind(char * command, void (*pf)()){
	this->processer.action_list.insert(make_pair(command,(*pf)));
}

device::~device(){}


static void handleRoot() {
    device.server.server.send(200, "text/html", postForms);
}

static void set_wifi() {
	if (device.server.server.method() != HTTP_POST) {
		device.server.server.send(405, "text/plain", "Method Not Allowed");
	} else {
		//String message = "POST form was:\n";

		device.server.ssid = device.server.server.arg(0);
		device.server.passwd = device.server.server.arg(1);
		//Serial.println(this->ssid, this->passwd);
		String message = "";
		message = "<html>\
							<head>\
								<title>配网界面</title>\
								<style>\
									body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
								</style>\
							</head>\
							<body>\
								<h4>the name of your WiFi：" + device.server.ssid + " and the password is：" + device.server.passwd + "</h4>" + '\n' + 
								"<form method=\"POST\" action=\"/\">\
									<input type=\"submit\" value=\"Back\">\
							</body>\
							</html>";
		device.server.server.send(200,"text/plain",message);
		//server.send(200, "text/plain", message);
	}
}
