#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Main.h"
#include "I2C_Support.h"
#include "Setup_Heater_Temp.h"
#include "Main_Screen.h"
#include "ST7735_TFT.h"


extern char setup_heater_set_text[];
unsigned char setup_heater_set_temp;

char Select_Heater_Temp_Field;
char In_Heater_Temp_Setup;

extern char *txt;
extern char found;
extern unsigned char heater_set_temp;
extern short nec_ok;

void Do_Setup_Heater_Temp(void)
{

In_Heater_Temp_Setup = 1;
    setup_heater_set_temp = heater_set_temp;
    Initialize_Setup_Heater_Screen();                  // Initialize setup heater screen
    Update_Setup_Heater_Screen();                      // Update the screen with latest info

    while (In_Heater_Temp_Setup == 1)
    {
         if (check_for_button_input() == 1)
        {
             nec_ok = 0;
             if (found >= Play_Pause && found <= EQ)
             {
                Do_Beep_Good(); 
                if (found == Prev) Go_Prev_Field();
                if (found == Next) Go_Next_Field();
                if (found == Play/Pause) Do_Save_New_Time();
                if (found == Minus) Decrease_Time();
                if (found == Plus) Increase_Time;
                if (found == EQ) Exit_Time_Setup();
                found = 0xff;
             }
             else
             {
                 Do_Beep_Bad();
             }             
        }                   
    }
}

void Increase_Heater_Temp()
{
	// add code to increase setup_heater_set_temp by 1
	// then check if it is greater than 120. If so, limit to 120

    if(setup_heater_set_temp>=120) Update_Setup_Heater_Screen();
    else
    {
        setup_heater_set_temp++;
        Update_Setup_Heater_Screen();
    }
    
//        if (duty_cycle == 100)
//    {
//        Do_Beep();
//        Do_Beep();
//        do_update_pwm(duty_cycle);
//    }
//    else
//    {
//        duty_cycle = duty_cycle + 5;
//        do_update_pwm(duty_cycle);
//    }
    
    	//Update_Setup_Heater_Screen();                       // Update screen with latest info

}

void Decrease_Heater_Temp()          
{
	// add code to decrease setup_heater_set_temp by 1
	// then check if it is less than 50. If so, limit to 50
    
        if(setup_heater_set_temp<=50) Update_Setup_Heater_Screen();
    else
    {
        setup_heater_set_temp=setup_heater_set_temp-1;
        Update_Setup_Heater_Screen();
    }

    	//Update_Setup_Heater_Screen();                      // Update screen with latest info

        
}

void Exit_Setup_Heater_Temp()
{
    DS3231_Read_Time();                                             // Read time
    Initialize_Screen();                                            // Initialize the screen before returning  
    In_Heater_Temp_Setup = 0;                                   
}

void Do_Save_New_Heater_Temp()
{
    heater_set_temp = setup_heater_set_temp;
    DS3231_Read_Time();                                             // Read time
    Initialize_Screen();                                            // Initialize the screen before returning  
    In_Heater_Temp_Setup = 0;     
}
    
void Initialize_Setup_Heater_Screen(void) 
{ 
    fillScreen(ST7735_BLACK);                               // Fills background of screen with color passed to it
 
    strcpy(txt, "ECE3301L Sp'22 Sx\0");                    // Text displayed 
    drawtext(start_x , start_y, txt, ST7735_WHITE  , ST7735_BLACK, TS_1);   // X and Y coordinates of where the text is to be displayed

    strcpy(txt, "  Heater\0 ");                             // Text displayed 
    drawtext(start_x , start_y+25, txt, ST7735_YELLOW, ST7735_BLACK, TS_2);     
    strcpy(txt, "  Setup\0 ");                              // Text displayed 
    drawtext(start_x , start_y+40, txt, ST7735_YELLOW, ST7735_BLACK, TS_2);                       
    strcpy(txt, "Set Heater Temp");
    drawtext(setup_heater_x , setup_heater_y, txt, ST7735_CYAN  , ST7735_BLACK, TS_1);
}
    
void Update_Setup_Heater_Screen(void)
{
    char dc_char1 = setup_heater_set_temp/100;
    char dc_char2 = setup_heater_set_temp%100/10; // add code here
    char dc_char3 = setup_heater_set_temp%10; // add code here    
    setup_heater_set_text[0] = dc_char1 + '0';
    setup_heater_set_text[1] = dc_char2 + '0';
    setup_heater_set_text[2] = dc_char3 + '0';
    drawtext(setup_data_heater_x, setup_data_heater_y ,setup_heater_set_text, ST7735_RED, ST7735_BLACK, TS_2);
}


