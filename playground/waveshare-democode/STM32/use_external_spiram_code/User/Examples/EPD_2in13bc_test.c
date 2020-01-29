/*****************************************************************************
* | File      	:   EPD_2IN13bc_test.c
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper B and C test demo
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
#include "EPD_2IN13bc.h"

void EPD_2IN13bc_test(void)
{
	printf("2.13inch e-Paper B and C demo\r\n");
	DEV_Module_Init();
	EPD_2IN13BC_Init();
	EPD_2IN13BC_Clear();
	DEV_Delay_ms(100);
	
#if 0
    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black image
    printf("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP images into RAM
//    SDCard_ReadBMP("2in13b-b.bmp", 0, 0);
		SDCard_ReadBMP("2in13c-b.bmp", 0, 0);
	
    //Draw red image
    printf("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
//    SDCard_ReadBMP("2in13b-r.bmp", 0, 0);
		SDCard_ReadBMP("2in13c-y.bmp", 0, 0);

    //4.Refresh the image in RAM to e-Paper
    EPD_2IN13BC_Display();
    DEV_Delay_ms(2000);  
#else
    /*show image for array*/
		printf("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_2in13b_b);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
		Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_2in13b_r);
    
		printf("EPD_2IN13BC_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_2IN13BC_Display();
    DEV_Delay_ms(2000);
#endif

#if 1
    /*Horizontal screen*/
    //1.Draw black image
		printf("Draw black image\r\n");
    Paint_NewImage(IMAGE_BW, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 70, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 80, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 50, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 70, 20, 100, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(60, 70, 90, 100, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(125, 85, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 15, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(5, 30, 123456789, &Font16, BLACK, WHITE);

    //2.Draw red image
		printf("Draw red image\r\n");
    Paint_NewImage(IMAGE_BWR, EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    Paint_DrawPoint(5, 90, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 100, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(125, 70, 125, 100, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(110, 85, 140, 85, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 70, 50, 100, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(165, 85, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 0, "waveshare Electronics", &Font12, BLACK, WHITE);
    Paint_DrawNum(5, 50, 987654321, &Font16, WHITE, RED);

    //3.Refresh the image in RAM to e-Paper
		printf("EPD_2IN13BC_Display\r\n");
    EPD_2IN13BC_Display();
		
#endif    
	DEV_Delay_ms(3000);
	EPD_2IN13BC_Clear();

	EPD_2IN13BC_Sleep();
	DEV_Module_Exit();
}





