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
        std::map<const char *,call_back_func>::iterator iter;
        if(command.hasOwnProperty("command")){
            iter = action_list.find((const char *)command["command"]);
            //find the command
            if(iter != action_list.end()){
                //and then run the call back function
                Serial.println(iter->first);
                (*(iter->second))();
                return true;
            }
            else{
                return false;
            }
        }   
    }

};