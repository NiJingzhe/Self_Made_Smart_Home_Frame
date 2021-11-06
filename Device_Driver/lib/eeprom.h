#pragma once

#include<EEPROM.h>
using namespace std;

class rom{

    rom(int size){
        EEPROM.begin(size+1);
    }

    uint8_t read_data(int addr){
        if(addr>0 && addr<size){
            return EEPROM.read(addr);
        }
        else{
            return -1;
        }
    }

    bool write_data(){}

};