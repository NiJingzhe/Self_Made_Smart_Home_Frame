#include <ESP8266WiFi.h>


const char* ssid = "StudyRoom";
const char* password = "n1j2z3456";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,0);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);  //打开目标WiFi热点
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  // Print the IP address & instructions
  Serial.println(WiFi.localIP());   //得到连接后的8266的IP地址
 // Serial.println("To control GPIO, open your web browser.");
  Serial.println("To set GPIO 0 high, type:");
  Serial.print(WiFi.localIP());
  Serial.println("/gpio/1");
  Serial.println("To set GPIO 0 low, type:");
  Serial.print(WiFi.localIP());
  Serial.println("/gpio/0");
  Serial.println("To toggle GPIO 0, type:");
  Serial.print(WiFi.localIP());
  Serial.println("/gpio/0");
}
void loop(){}
