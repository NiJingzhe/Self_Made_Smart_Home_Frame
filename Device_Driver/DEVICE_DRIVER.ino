#define LED_OUT 14

#include "lib/device.h"
#include "lib/set_wifi_server.h"
#include "lib/webpage/wifi_setting_html.h"


static void handleRoot();
static void set_wifi();
static void open_led();
static void close_led();

set_wifi_server SERVER(handleRoot,set_wifi);
device test_led("test_led",4001,4000);

void setup(){
    pinMode(LED_OUT, OUTPUT);
    digitalWrite(LED_OUT, LOW);

    if(!test_led.check_ssid_and_passwd()){
        WiFi.mode(WIFI_AP_STA);
	    WiFi.softAP(test_led.name,"",11,0,4);
        SERVER.start_server();
    }


    test_led.bind("open",open_led);
    test_led.bind("close",close_led);
}

void loop(){
    if(test_led.need_set_wifi){
        SERVER.run();

		if(test_led.ssid != ""){
			test_led.ROM.write_String_data(1,test_led.ssid);
			test_led.ROM.write_String_data(256,test_led.passwd);
			test_led.need_set_wifi = false;
			WiFi.softAPdisconnect(true);
			WiFi.begin(test_led.ssid,test_led.passwd);
		}
    }
		
    test_led.run();
}

static void open_led(){
    digitalWrite(LED_OUT,HIGH);
}

static void close_led(){
    digitalWrite(LED_OUT,LOW);
}

static void handleRoot() {
    SERVER.server.send(200, "text/html", wifi_setting_html);
}

static void set_wifi() {
	if (SERVER.server.method() != HTTP_POST) {
		SERVER.server.send(405, "text/plain", "Method Not Allowed");
	} else {
		//String message = "POST form was:\n";

		SERVER.ssid = SERVER.server.arg(0);
		SERVER.passwd = SERVER.server.arg(1);

		test_led.ssid = SERVER.get_ssid();
		test_led.passwd = SERVER.get_passwd();
		//Serial.println(this->ssid, this->passwd);
		String webpage = "";
		webpage = "<html>\
							<head>\
								<title>配网界面</title>\
								<style>\
									body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
								</style>\
							</head>\
							<body>\
								<h4>the name of your WiFi：" + SERVER.ssid + " and the password is：" + SERVER.passwd + "</h4>" + '\n' + 
								"<form method=\"POST\" action=\"/\">\
									<input type=\"submit\" value=\"Back\">\
							</body>\
							</html>";
		SERVER.server.send(200,"text/plain",webpage);
		//server.send(200, "text/plain", message);
	}
}
