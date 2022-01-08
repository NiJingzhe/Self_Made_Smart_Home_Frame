#include "device.h"
using namespace std;

device test_led("test_led",4001,4000,80);

void setup(){
    if(!test_led.check_ssid_and_passwd())
        test_led.start_set_wifi();
}

void loop(){
    test_led.set_wifi_server_run();
    test_led.run();
}