#pragma once

typedef void (*call_back_func)();
#include <Arduino_JSON.h>

class command_processer{
public:
    //a map about commands and call_back_functions
    std::map<const char *, call_back_func> action_list;
    
    command_processer(){}
    ~command_processer(){}

    bool process(JSONVar command){
        if(command.hasOwnProperty("command")){
            for (auto &iter : action_list){
                JSONVar tmp_command;
                tmp_command["command"] = iter.first;
                if(tmp_command["command"] == command["command"]){
                    Serial.println("Now running call back function..............")
                    (*(iter.second))();
                    return true;
                    //delay(500);
                }
                else{
                    Serial.println("Cannot find any command matched!!!!!")
                    return false;
                    //delay(500);
                }
            }
        } 
    }
};