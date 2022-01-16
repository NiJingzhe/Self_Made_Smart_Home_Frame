#define LED_OUT 14

#include "lib/device.h"
#include "lib/set_wifi_server.h"
#include "lib/webpage/wifi_setting_html.h"


void handleRoot();
void set_wifi();
void open_led();
void close_led();
void send_state();

set_wifi_server SERVER(handleRoot,set_wifi);
device test_led("test_led",4001,4000);

void setup(){
	pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
	WiFi.mode(WIFI_AP_STA);

	test_led.check_ssid_and_passwd();

	delay(500);

	WiFi.softAP(test_led.name,test_led.name,11,0,4);
	SERVER.start_server();


    test_led.bind("open",open_led);
    test_led.bind("close",close_led);
	test_led.bind("get_state",send_state);
}

void loop(){

	test_led.run();
    SERVER.run();
		
}

void open_led(){
    digitalWrite(LED_BUILTIN,LOW);
	test_led.device_state = "打开";
	Serial.println("do open");
	return;
}

void close_led(){
    digitalWrite(LED_BUILTIN,HIGH);
	test_led.device_state = "关闭";
	Serial.println("do close");
	return;
}

void send_state(){
	Serial.println("do get_state");
	return;
}

void handleRoot() {
    SERVER.server.send(200, "text/html", wifi_setting_html);
}

void set_wifi() {
	if (SERVER.server.method() != HTTP_POST) {
		SERVER.server.send(405, "text/plain", "Method Not Allowed");
	} else {
		//String message = "POST form was:\n";

		SERVER.ssid = SERVER.server.arg(0);
		SERVER.passwd = SERVER.server.arg(1);
		
		
		String webpage = "";
		webpage = "<html>\
						<head>\
							<title>SetPage</title>\
							<style>\
								body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
							</style>\
						</head>\
						<body>\
							<h4>the name of your WiFi: " + SERVER.ssid + " and the password is: " + SERVER.passwd + "</h4>" + '\n' + 
							"<form method=\"POST\" action=\"/\">\
								<input type=\"submit\" value=\"Back\">\
						</body>\
					</html>";

		SERVER.server.send(200,"text/plain",webpage);

		Serial.println(SERVER.ssid+"\n"+ SERVER.passwd);

		test_led.ssid = SERVER.get_ssid();
		test_led.passwd = SERVER.get_passwd();

		if(test_led.ssid != ""){
			test_led.ROM.write_String_data(1,test_led.ssid);
			test_led.ROM.write_String_data(256,test_led.passwd);
			//WiFi.softAPdisconnect(true);
			WiFi.begin(test_led.ssid,test_led.passwd);
		}
		//server.send(200, "text/plain", message);
	}
}
