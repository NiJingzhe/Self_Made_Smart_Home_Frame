#pragma once

#include <Arduino_JSON.h>
using namespace std;

class command_processer{
public:
    map<char *, void (*pf)()> action_list;
  
};