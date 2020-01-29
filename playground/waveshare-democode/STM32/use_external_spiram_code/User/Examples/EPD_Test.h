/*****************************************************************************
* | File      	:	  EPD_Test.h
* | Author      :   Waveshare team
* | Function    :   e-Paper test Demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-11
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR O+THER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _EPD_TEST_H_
#define _EPD_TEST_H_

#include "DEV_Config.h"
#include "imagedata.h"
#include "EPD_1in54c.h"
#include "GUI_Paint.h"
#include "SD_Card_APP.h"
#include "ImageData.h"

void EPD_1in54_test(void);
void EPD_1in54_V2_test(void);
void EPD_1in54C_test(void);
void EPD_1in54B_test(void);

void EPD_2in7_test(void);
void EPD_2in7B_test(void);

void EPD_2in9_test(void);
void EPD_2in9bc_test(void);
void EPD_2in9d_test(void);

void EPD_2IN13_test(void);
void EPD_2IN13V2_test(void);
void EPD_2IN13bc_test(void);
void EPD_2IN13d_test(void);

void EPD_4IN2_test(void);
void EPD_4IN2BC_test(void);

void EPD_5IN83_test(void);
void EPD_5IN83BC_test(void);

void EPD_7IN5_test(void);
void EPD_7IN5BC_test(void);
#endif
