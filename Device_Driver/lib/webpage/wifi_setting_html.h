#pragma once
#include <WString.h>
const String wifi_setting_html = "<html>\
                                <head>\
                                    <title>配网界面</title>\
                                    <style>\
                                        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
                                    </style>\
                                </head>\
                                <body>\
                                    <h1>输入WiFi的ssid和密码</h1><br>\
                                    <form method=\"post\" action=\"/setwifi/\">\
                                        <input type=\"text\" name=\"ssid\"}\'><br>\
                                        <input type=\"text\" name=\"passwd\"}\'><br>\
                                        <input type=\"submit\" value=\"Submit\">\
                                </body>\
                            </html>";