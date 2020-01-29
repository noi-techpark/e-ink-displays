/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-07-24
* | Info        :   Here is a Chinese version of the documentation for your quick use.
******************************************************************************/
This file is to help you use this routine.

1.Basic Information：
This routine was developed based on Arduino, and the routines were verified on the Arduino UNO.
This routine was verified using the e-Paper Shield module.

2.Pin connection：
Pin connections can be viewed in DEV_Config.h and will be repeated here:
e-Paper Shield   =>    STM32F103
SCLK             ->    PA5
MISO             ->    PA6
MOSI             ->    PA7
EPD_CS           ->    PB6
EPD_DC           ->    PC7
EPD_RST          ->    PA9
EPD_BUSY         ->    PA8
SD_CS_0          ->    PB10
SPIRAM_CS        ->    PB4

3.Basic use：
Since this project is a comprehensive project, you may need to read the following for use:
Example 1:
    If you purchased 5.83inch e-paper, then you should remove the 
    comment for the corresponding 115 lines of code, ie:
        //		EPD_5in83_test();
    Changed to:
        EPD_5in83_test();
        
Example 2:
    If you buy a 2.9inch e-paper (B), since the 2.9-inch Type B and Type C are common driver codes,
     Then you should remove the comment for the corresponding 129 lines of code, ie:
    //		EPD_2in9bc_test();
    Changed to:
        EPD_2in9bc_test();

Note: For EPD_1in54_V2_test() and EPD_2in13_V2_test(), please note that the V2 logo 
      is attached to the back of your screen.
Then compile and burn