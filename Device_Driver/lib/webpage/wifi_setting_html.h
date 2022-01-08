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
                                    <h1>Plaese input the name and password of your WiFi</h1><br>\
                                    <form method=\"post\" action=\"/setwifi/\">\
                                        <p>name</p>\
                                        <input type=\"text\" name=\"ssid\"}\'><br>\
                                        <p>password</p>\
                                        <input type=\"text\" name=\"passwd\"}\'><br>\
                                        <input type=\"submit\" value=\"Submit\">\
                                </body>\
                            </html>";