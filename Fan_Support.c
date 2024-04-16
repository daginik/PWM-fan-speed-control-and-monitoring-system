
#include <p18f4620.h>
#include "Main.h"
#include "Fan_Support.h"
#include "stdio.h"

extern char HEATER;
extern char FAN;
extern char duty_cycle;
extern char heater_set_temp;
extern signed int DS1621_tempF;

int get_duty_cycle(signed int temp, int set_temp)
{
// add code to check if temp is greater than set_temp. If so, set dc according to the handout
// check if dc is greater than 100. If so, set it to 100
// if dc is negative, set to 0
// return dc

}

void Monitor_Heater()
{
    duty_cycle = get_duty_cycle(DS1621_tempF, heater_set_temp);
    do_update_pwm(duty_cycle);

    if (HEATER == 1) 
    {
        FAN_EN = 1;
    }
    else FAN_EN = 0;
}

void Toggle_Heater()
{
// add code just to flip the variable FAN
    FAN=!FAN
}

int get_RPM()
{
    int RPS = TMR3L / 2; // read the count. Since there are 2 pulses per rev 
    // then RPS = count /2 
    TMR3L = 0; // clear out the count 
return (RPS * 60); // return RPM = 60 * RPS 
}

void Turn_Off_Fan()
{
    FAN = 0;
    FAN_EN = 0;
    //FANEN_LED = 0;   

}

void Turn_On_Fan()
{
    FAN = 1;
    do_update_pwm(duty_cycle);
    FAN_EN = 1;
    //FANEN_LED = 1; 
}







