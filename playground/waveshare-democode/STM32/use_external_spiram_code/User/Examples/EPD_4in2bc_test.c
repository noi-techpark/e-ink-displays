/*****************************************************************************
* | File      	:   EPD_4IN2BC_test.c
* | Author      :   Waveshare team
* | Function    :   4.2inch e-paper B and C test demo
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
#include "EPD_4IN2BC.h"

void EPD_4IN2BC_test(void)
{
	printf("4.2inch e-Paper B and C demo\r\n");
	DEV_Module_Init();
	
	EPD_4IN2BC_Init();
	EPD_4IN2BC_Clear();


#if 1
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    printf("IMAGE_BW\n");
    Paint_NewImage(IMAGE_BW, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("4in2b-b.bmp", 0, 0);
		
    //Draw yellow picture
    printf("IMAGE_BWR\n");
    Paint_NewImage(IMAGE_BWR, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    SDCard_ReadBMP("4in2b-r.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_4IN2BC_Display();
    DEV_Delay_ms(2000);
#else 
		printf("show image for array\r\n");
    //1.Draw black image
    Paint_NewImage(IMAGE_BW, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_4in2bc_b);

    //2.Draw red image
    Paint_NewImage(IMAGE_BWR, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
		Paint_Clear(WHITE);		
		Paint_DrawBitMap(gImage_4in2bc_ry);
    
		printf("EPD_4IN2BC_Display\r\n");
    //3.Refresh the image in RAM to e-Paper
    EPD_4IN2BC_Display();
    DEV_Delay_ms(2000);
#endif

#if 1
    //1.Create a new image cache named IMAGE_BW and fill it with white
    //Draw black picture
    Paint_NewImage(IMAGE_BW, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 20, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawLine(20, 20, 50, 50, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawLine(50, 20, 20, 50, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
    Paint_DrawRectangle(60, 20, 90, 50, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawCircle(35, 90, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 120, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(5, 140, 123456789, &Font12, BLACK, WHITE);
    // EPD_4IN2BC_SetBlack();

    //Draw yellow picture
    Paint_NewImage(IMAGE_BWR, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
    
    Paint_DrawPoint(5, 30, RED, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, RED, DOT_PIXEL_4X4, DOT_STYLE_DFT);
    Paint_DrawLine(35, 75, 35, 105, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawLine(20, 90, 50, 90, RED, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
    Paint_DrawRectangle(20, 20, 50, 50, RED, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
    Paint_DrawCircle(75, 90, 15, RED, DRAW_FILL_FULL, DOT_PIXEL_1X1);
    Paint_DrawString_EN(5, 160, "waveshare", &Font16, RED, WHITE);
    Paint_DrawNum(5, 180, 987654321, &Font16, WHITE, RED);
    // EPD_4IN2BC_SetRed();

    //show
    printf("EPD_4IN2BC_Display...\n");
    EPD_4IN2BC_Display();
		DEV_Delay_ms(4000);
#endif
	DEV_Delay_ms(4000);
	EPD_4IN2BC_Clear();
	
	EPD_4IN2BC_Sleep();
	DEV_Module_Exit();
}





