#define LED_OUT 14

#include "lib/device.h"

device test_led("test_led",4001,4000,80);

void setup(){
    pinMode(LED_OUT, OUTPUT);
    digitalWrite(LED_OUT, LOW);

    if(!test_led.check_ssid_and_passwd())
        test_led.start_set_wifi();

    test_led.bind("open",open_led);
    test_led.bind("close",close_led);
}

void loop(){
    test_led.set_wifi_server_run();
    test_led.run();
}

static void open_led(){
    digitalWrite(LED_OUT,HIGH);
}

static void close_led(){
    digitalWrite(LED_OUT,LOW);
}