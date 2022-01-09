#pragma once

typedef void (*call_back_func)();
#include <Arduino_JSON.h>

class command_processer{
public:

    std::map<const char *, call_back_func> action_list;
    
    command_processer(){}
    ~command_processer(){}

    bool process(JSONVar command){
        std::map<const char *,call_back_func>::iterator iter;
        if(command.hasOwnProperty("command")){
            iter = action_list.find((const char *)command["command"]);
            if(iter != action_list.end()){
                (*(iter->second))();
                return true;
            }
            else{
                return false;
            }
        }   
    }

};