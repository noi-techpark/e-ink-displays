/*****************************************************************************
* | File      	:   EPD_7IN5BC_test.c
* | Author      :   Waveshare team
* | Function    :   7.5inch e-paper B and C test demo
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
#include "EPD_7IN5BC.h"

void EPD_7IN5BC_test(void)
{
	printf("7.5inch e-Paper B and C demo\r\n");
	DEV_Module_Init();
	
	EPD_7IN5BC_Init();
	EPD_7IN5BC_Clear();
	DEV_Delay_ms(300);

#if 1
	    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    printf("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("7in5b-b.bmp", 0, 0);

    //Draw red picture
    printf("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("7in5b-r.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_7IN5BC_Display();
    DEV_Delay_ms(2000);
		
#else 
		printf("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_7in5bc_b);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
		Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_7in5bc_ry);
    
		printf("EPD_7IN5BC_7IN5BC_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_7IN5BC_Display();
    DEV_Delay_ms(2000);

#endif

#if 1
		//1.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    Paint_NewImage(IMAGE_BW, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
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

    //Draw red picture
    Paint_NewImage(IMAGE_BWR, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    Paint_DrawRectangle(50, 50, 150, 150, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawRectangle(200, 50, 300, 150, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawCircle(100, 250, 50, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(250, 250, 50, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);

    Paint_DrawString_EN(10, 310, "hello world", &Font24, WHITE, RED);
    Paint_DrawString_EN(10, 335, "Waveshare Electronics", &Font24, RED, WHITE);

    Paint_DrawNum(10, 360, 123456789, &Font24, RED, WHITE);

    //3.Refresh the picture in RAM to e-Paper
    EPD_7IN5BC_Display();
#endif



	DEV_Delay_ms(4000);
	EPD_7IN5BC_Clear();
	
	EPD_7IN5BC_Sleep();
	DEV_Module_Exit();
}

