/*****************************************************************************
* | File      	:   EPD_1IN54b_test.c
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper B test demo
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
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_1in54b.h"

void EPD_1in54B_test(void)
{
	DEV_Module_Init();
	printf("1.54inch e-Paper B demo\r\n");
	EPD_1IN54B_Init();
	EPD_1IN54B_Clear();
	DEV_Delay_ms(500);
	
#if 1
    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black image
    printf("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP images into RAM
    SDCard_ReadBMP("1in54b-b.bmp", 0, 0);

    //Draw red image
    printf("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("1in54b-r.bmp", 0, 0);
    //4.Refresh the image in RAM to e-Paper
    EPD_1IN54B_Display();
    DEV_Delay_ms(2000);  
#else
    /*show image for array*/
		printf("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_1in54b_Black);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
		Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_1in54b_Red);
    
		printf("EPD_1IN54B_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_1IN54B_Display();
    DEV_Delay_ms(2000);
#endif    

#if 1
    /*Horizontal screen*/
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 10, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);   
    Paint_DrawLine(45, 70, 45, 110, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    Paint_DrawLine(25, 90, 65, 90, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_2X2);
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
    Paint_DrawCircle(115, 90, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_2X2);
    Paint_DrawNum(30, 145, 123456789, &Font20, WHITE, BLACK);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 10, 70, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
    Paint_DrawLine(70, 10, 20, 60, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_2X2);        
    Paint_DrawRectangle(90, 10, 140, 60, BLACK, DRAW_FILL_FULL, DOT_PIXEL_2X2);        
    Paint_DrawCircle(45, 90, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);    
    Paint_DrawString_EN(30, 115, "waveshare", &Font20, BLACK, WHITE);    
    
    //3.Refresh the image in RAM to e-Paper
    EPD_1IN54B_Display();  
		
#endif
		DEV_Delay_ms(3000);
		EPD_1IN54B_Clear();
		
    EPD_1IN54B_Sleep();
		DEV_Module_Exit();
		
}




