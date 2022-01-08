#pragma once

#include <Arduino_JSON.h>
using namespace std;

class command_processer{
public:
    map<char *, void (*pf)()> action_list;
    
    command_processer(){}
    ~command_processer(){}

    bool process(JSONVar command){
        if(command.hasOwnProperty("command")){
            map<char *,void (*pf)()>::iterator iter;
            iter = action_list.find(command["command"]);
            if(iter != action_list.end()){
                (iter->second)();
                return true;
            }
            else{
                return false;
            }
        }   
    }

};