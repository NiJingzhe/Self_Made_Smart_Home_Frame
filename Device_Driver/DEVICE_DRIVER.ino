#define LED_OUT 14

#include "lib/device.h"
#include "lib/set_wifi_server.h"
ADC_MODE(ADC_VCC)

//declare call_back functions
void handleRoot();
void set_wifi();
void open_led();
void close_led();
void send_state();

//action open,close,get_state;

//each device has one set_wifi_server and a abstract concept of the device
set_wifi_server SERVER(handleRoot,set_wifi);
device test_led("开发板LED",4001,4000);

void setup(){

	//we need to initialize the pin mode of the board first
	Serial.println("\n");
	Serial.println("\n");
	
	pinMode(LED_OUT,OUTPUT);
    digitalWrite(LED_OUT,LOW);

	//and then set wifi mode
	WiFi.mode(WIFI_AP_STA);

	//then check if we have stored previous ssid and password.If yes, we will connect to this wifi
	test_led.check_ssid_and_passwd();

	//wait for 500ms
	//delay(500);

	//open AP and wifi setting server
	test_led.openAP();
	SERVER.start_server();

	//bind commands with the callback functions
    test_led.bind("open",open_led);
	test_led.bind("close",close_led);
	test_led.bind("get_state",send_state); 

	
	/* if (!test_led.processer.action_list.empty()) {
        for (auto i = test_led.processer.action_list.begin(); i != test_led.processer.action_list.end(); ++i) {
            Serial.println(i->first);
			//Serial.println(i->second);
        }
    }  */
}

void loop(){
	//run the server and sub device
	SERVER.run();
	test_led.run();	
}


//call back functions:
void open_led(){
    digitalWrite(LED_OUT,HIGH);
	test_led.device_state = "打开";
	Serial.println("do open");
}

void close_led(){
    digitalWrite(LED_OUT,LOW);
	test_led.device_state = "关闭";
	Serial.println("do close");
}

void send_state(){
	Serial.println("do get_state");
}

void handleRoot() {

	String webpage = "";
	webpage =  "<html>\
					<head>\
						<title>SetPage</title>\
						<style>\
							body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
						</style>\
					</head>\
					<body>\
						<h1>Plaese input the name and password of your WiFi</h1><br>\
						<form method=\"post\" action=\"/set_wifi/\">\
							<p>name</p>\
							<input type=\"text\" name=\"ssid\"}\'><br>\
							<p>password</p>\
							<input type=\"text\" name=\"passwd\"}\'><br>\
							<input type=\"submit\" value=\"Submit\">\
					</body>\
				</html>";

    SERVER.server.send(200, "text/html",webpage);
}

void set_wifi() {
	//this page only allows POST
	if (SERVER.server.method() != HTTP_POST) {
		SERVER.server.send(405, "text/plain", "Method Not Allowed");
	} else {
		//get the arguments,0 is ssid and 1 is password
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

		SERVER.server.send(200,"text/html",webpage);

		Serial.println(SERVER.ssid+"\n"+ SERVER.passwd);

		//tell sub device the password and ssid
		test_led.ssid = SERVER.get_ssid();
		test_led.passwd = SERVER.get_passwd();

		//store the wifi info into eeprom
		if(test_led.ssid != ""){
			test_led.ROM.write_String_data(1,test_led.ssid);
			test_led.ROM.write_String_data(256,test_led.passwd);
			//start wifi
			WiFi.begin(test_led.ssid,test_led.passwd);
		}
	}
}
