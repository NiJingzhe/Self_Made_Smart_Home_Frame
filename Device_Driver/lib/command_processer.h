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
       /* std::map<JSONVar,call_back_func>::iterator iter;
        if(command.hasOwnProperty("command")){
            JSONVar tmp_command;
            tmp_command["command"] = command["command"];
            iter = action_list.find(tmp_command);
            //find the command
            if(iter != action_list.end()){
                //and then run the call back function
                Serial.println((const char *)(iter->first));
                (*(iter->second))();
                return true;
            }
            else{
                return false;
            } 
        }    */
        if(command.hasOwnProperty("command")){
            for (auto &iter : action_list){
                JSONVar tmp_command;
                tmp_command["command"] = iter.first;
                if(tmp_command["command"] == command["command"]){
                    (*(iter.second))();
                    return true;
                    delay(500);
                }
                else{
                    return false;
                    delay(500);
                }
            }
        }
        
    }

};