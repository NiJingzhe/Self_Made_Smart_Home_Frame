#pragma once

#include<EEPROM.h>
using namespace std;

class rom{

    rom(int size){
        EEPROM.begin(size+1);
    }

    ~rom(){}

    uint8_t read_data(int addr){
        if(addr>0 && addr<size){
            return EEPROM.read(addr);
        }
        else{
            return -1;
        }
    }

    void write_String_data(int addr,String data){
        EEPROM.write(addr,data.length());
        for(int i = 0; i<data.length(); i++){
            EEPROM.write(addr+1+i,data[i]);
        }
        EEPROM.commit();
    }

};