/*****************************************************************************
* | File      	:   EPD_5IN83_test.c
* | Author      :   Waveshare team
* | Function    :   5.83inch e-paper test demo
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
#include "EPD_5IN83.h"

void EPD_5IN83_test(void)
{
	printf("5.83inch e-Paper demo\r\n");
	DEV_Module_Init();
	
	EPD_5IN83_Init();
	EPD_5IN83_Clear();
	
	DEV_Delay_ms(500);
#if 1
	    /*show sd card pic*/
		printf("show sd card pic\r\n");
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_5IN83_WIDTH, EPD_5IN83_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("5in83.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
		printf("EPD_5IN83_Display\r\n");
    EPD_5IN83_Display();
    DEV_Delay_ms(2000);
#else 
		 /*show image for array*/
    printf("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_5IN83_WIDTH, EPD_5IN83_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);		
		
    printf("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(gImage_5in83);

    printf("EPD_4IN2_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_5IN83_Display();
    DEV_Delay_ms(2000);
		
#endif

#if 1
		printf("Paint_NewImage\r\n");
		
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_5IN83_WIDTH, EPD_5IN83_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);

    //2.Drawing on the image
    Paint_DrawPoint(25, 50, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 70, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 90, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 110, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(50, 50, 150, 150, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(150, 50, 50, 150, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(100, 200, 100, 300, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 250, 150, 250, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

    Paint_DrawRectangle(50, 50, 150, 150, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(200, 50, 300, 150, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(100, 250, 50, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(250, 250, 50, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 310, "hello world", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 335, "Waveshare Electronics", &Font24, BLACK, WHITE);

    Paint_DrawNum(10, 360, 123456789, &Font24, BLACK, WHITE);

    //3.Refresh the picture in RAM to e-Paper
		printf("EPD_5IN83_Display\r\n");
    EPD_5IN83_Display();
#endif

	DEV_Delay_ms(4000);
	EPD_5IN83_Clear();
	
	EPD_5IN83_Sleep();
	DEV_Module_Exit();
}





