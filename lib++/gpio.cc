//
// Copyright (c) 2016-2019 Janick Bergeron
// All Rights Reserved
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//


#include "gpio.hh"


#include "wiringPi.h"

#include <map>
#include <stdio.h>
#include <string.h>

struct pinMap_s {
    const char*  name;
    unsigned int gpioNum;
    unsigned int wiPiNum;
} gPinMap[29] = {{"PIN3",   2,  8},
                 {"PIN5",   3,  9},
                 {"PIN7",   4,  7},
                 {"PIN8",  14, 15},
                 {"PIN10", 15, 16},
                 {"PIN11", 17,  0},
                 {"PIN12", 18,  1},
                 {"PIN13", 27, 13},
                 {"PIN15", 22, 15},
                 {"PIN16", 23,  4},
                 {"PIN18", 24,  5},
                 {"PIN19", 10, 19},
                 {"PIN21",  9, 13},
                 {"PIN22", 25,  6},
                 {"PIN23", 11, 14},
                 {"PIN24",  8, 10},
                 {"PIN26",  7, 11},
                 {"PIN27",  0, 30},
                 {"PIN28",  1, 31},
                 {"PIN29",  5, 21},
                 {"PIN31",  6, 22},
                 {"PIN32", 12, 26},
                 {"PIN33", 13, 23},
                 {"PIN35", 19, 24},
                 {"PIN36", 16, 27},
                 {"PIN37", 26, 25},
                 {"PIN38", 20, 28},
                 {"PIN40", 21, 29},
                 {NULL,     0,  0}};


typedef struct gpioImp_s {
    int  pinNum;
    bool isInput;
} gpioImp_t;

static std::map<unsigned int, libSOC::gpio*>  g_singletons;
static bool init = false;

libSOC::gpio*
libSOC::gpio::get(unsigned int pin)
{
    if (!init) {
        wiringPiSetup();
        init = true;
    }

    int wiPin = -1;
    for (unsigned int i = 0; gPinMap[i].name != NULL; i++) {
        if (gPinMap[i].gpioNum == pin) {
            wiPin = gPinMap[i].wiPiNum;
            break;
        }
    }
    if (wiPin < 0) {
        fprintf(stderr, "Invalid pin number %d.\n", pin);
        return NULL;
    }
      
    libSOC::gpio *p = g_singletons[wiPin];
    if (p != NULL) return p;

    p = new libSOC::gpio();

    gpioImp_t *imp = new gpioImp_t;
    imp->pinNum = wiPin;
    
    p->m_imp = imp;
    
    g_singletons[wiPin] = p;

  return p;
}


libSOC::gpio*
libSOC::gpio::get(const char* name)
{
    if (!init) {
        wiringPiSetup();
        init = true;
    }

    int wiPin = -1;
    for (unsigned int i = 0; gPinMap[i].name != NULL; i++) {
        if (strcmp(gPinMap[i].name, name) == 0) {
            libSOC::gpio *p = g_singletons[gPinMap[i].gpioNum];
            if (p != NULL) return p;
            
            wiPin = gPinMap[i].wiPiNum;
            break;
        }
    }
    if (wiPin < 0) {
        fprintf(stderr, "Invalid pin name \"%s\".\n", name);
        return NULL;
    }
      
    libSOC::gpio *p = g_singletons[wiPin];
    if (p != NULL) return p;

    p = new libSOC::gpio();

    gpioImp_t *imp = new gpioImp_t;
    imp->pinNum = wiPin;
    
    p->m_imp = imp;
    
    g_singletons[wiPin] = p;

    return p;
}

        
bool
libSOC::gpio::makeOutput()
{
    pinMode(((gpioImp_t*) m_imp)->pinNum, OUTPUT);
    ((gpioImp_t*) m_imp)->isInput = false;

    pullUpDnControl(((gpioImp_t*) m_imp)->pinNum, PUD_OFF);
    return true;
}


bool
libSOC::gpio::makeInput()
{
    pinMode(((gpioImp_t*) m_imp)->pinNum, INPUT);
    ((gpioImp_t*) m_imp)->isInput = true;

    pullUpDnControl(((gpioImp_t*) m_imp)->pinNum, PUD_OFF);
    return true;
}


bool
libSOC::gpio::makeInterrupt(void (*fct)(void), libSOC::gpio::edge_t edge)
{
    int mode = 0;

    switch (edge) {
    case RISING:
        mode = INT_EDGE_FALLING;
        break;
    case FALLING:
        mode = INT_EDGE_RISING;
        break;
    case BOTH:
        mode = INT_EDGE_FALLING | INT_EDGE_RISING;
        break;
    }

    return wiringPiISR(((gpioImp_t*) m_imp)->pinNum, mode, fct) == 0;
}


bool
libSOC::gpio::isInput()
{
    return     ((gpioImp_t*) m_imp)->isInput;
}


bool
libSOC::gpio::setValue(bool val)
{
    digitalWrite(((gpioImp_t*) m_imp)->pinNum, val);
    return true;
}


bool
libSOC::gpio::getValue()
{
    return digitalRead(((gpioImp_t*) m_imp)->pinNum);
}
    
    
