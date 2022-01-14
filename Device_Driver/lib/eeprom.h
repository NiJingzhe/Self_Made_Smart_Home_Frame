#pragma once

#include<EEPROM.h>

class rom{
private:
    int size;
public:
    rom(int size_){
        this->size = size_;
        EEPROM.begin(size_+1);
    }

    ~rom(){}

    uint8_t read_data(int addr){
        if((addr>0) && (addr<this->size)){
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