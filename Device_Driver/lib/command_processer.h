#pragma once

typedef void (*call_back_func)();
#include <Arduino_JSON.h>
//#include "action.h"


class command_processer{
public:
    //a map about commands and call_back_functions
    std::map<const char *, call_back_func, std::less<const char *>> action_list;
    bool excute = false;
    //action action_list[3];

    command_processer(){}
    ~command_processer(){}

    bool process(JSONVar command){
        if(command.hasOwnProperty("command")){
            //(*(action_list[(const char *)command["command"]]))();
            JSONVar tmp_command;
            for (auto iter = action_list.begin(); iter != action_list.end(); ++iter){
                tmp_command["command"] = iter->first;
                Serial.print("after change, the tmp_command[\"command\"] is: ");
                Serial.println((const char *)tmp_command["command"]);
                if(tmp_command["command"] == command["command"]){
                    Serial.println("Now running call back function..............");
                    (*(iter->second))();
                    //(*(action_list[i].fp))();
                    tmp_command["command"] = "";
                    this->excute = true;
                    Serial.println("");
                    return true;
                }
            }

            if(!(this->excute)){
                Serial.println("Cannot find any command matched!!!!!");
                Serial.println();
                return false;
                //delay(500);
            }          
        }  
    } 
};