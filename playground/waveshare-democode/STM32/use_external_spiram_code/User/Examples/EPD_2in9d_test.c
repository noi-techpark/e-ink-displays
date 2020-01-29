/*****************************************************************************
* | File      	:   EPD_2IN9D_test.c
* | Author      :   Waveshare team
* | Function    :   2.9inch e-paper D test demo
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
#include "EPD_2in9d.h"

void EPD_2in9d_test(void)
{
	printf("2.9inch e-Paper D demo\r\n");
	DEV_Module_Init();
	EPD_2IN9D_Init();
	EPD_2IN9D_Clear();
	DEV_Delay_ms(500);
#if 1
	    /*show sd card pic*/
    //1.Initialize the SD card
    SDCard_Init();

    //2.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);

    //3.Read BMP pictures into RAM
    SDCard_ReadBMP("2in9.bmp", 0, 0);

    //4.Refresh the picture in RAM to e-Paper
    EPD_2IN9D_Display();
    DEV_Delay_ms(2000);
#else
    /*show image for array*/
    printf("show image for array\r\n");
    //1.Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);    
		
    printf("Paint_DrawBitMap\r\n");
    //2.show image for array, IMAGE_ROTATE_0 and IMAGE_COLOR_POSITIVE will not affect reading
    Paint_DrawBitMap(gImage_2in9);

    printf("EPD_2IN9D_Display\r\n");
    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN9D_Display();
    DEV_Delay_ms(2000);
//		
//			SPIRAM_Usertest();
#endif

#if 1
    //1.Create a new image cache named IMAGE_BW and fill it with white
    UBYTE Rotate = IMAGE_ROTATE_90;
    Paint_NewImage(IMAGE_BW, EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, Rotate, IMAGE_COLOR_POSITIVE);
    Paint_Clear(WHITE);
		
    //2.Drawing on the image
     if (Rotate == IMAGE_ROTATE_0 || Rotate == IMAGE_ROTATE_180) {
        printf("Vertical screen\r\n");
        
        Paint_DrawPoint(10, 20, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 30, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

        Paint_DrawLine(20, 20, 70, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(70, 20, 20, 70, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(30, 120, 60, 120, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
        Paint_DrawLine(45, 135, 45, 105, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

        Paint_DrawRectangle(20, 20, 70, 70, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawRectangle(75, 20, 120, 70, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawCircle(45, 120, 15, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawCircle(100, 120, 15, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawString_EN(10, 150, "hello world", &Font12, WHITE, BLACK);
        Paint_DrawString_EN(10, 170, "waveshare", &Font16, BLACK, WHITE);

        Paint_DrawNum(10, 200, 123456789, &Font12, BLACK, WHITE);
        Paint_DrawNum(10, 220, 987654321, &Font16, WHITE, BLACK);
    } else {
        printf("Horizontal screen\r\n");
            
        Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
        Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

        Paint_DrawLine(20, 70, 70, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(70, 70, 20, 120, BLACK, LINE_STYLE_SOLID, DOT_PIXEL_1X1);
        Paint_DrawLine(140, 95, 180, 95, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);
        Paint_DrawLine(160, 75, 160, 115, BLACK, LINE_STYLE_DOTTED, DOT_PIXEL_1X1);

        Paint_DrawRectangle(20, 70, 70, 120, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawRectangle(80, 70, 130, 120, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawCircle(160, 95, 20, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_1X1);
        Paint_DrawCircle(210, 95, 20, BLACK, DRAW_FILL_FULL, DOT_PIXEL_1X1);

        Paint_DrawString_EN(10, 0, "waveshare Electronics", &Font16, BLACK, WHITE);
        Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

        Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
        Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);        
    }

    //3.Refresh the picture in RAM to e-Paper
    EPD_2IN9D_Display();
    DEV_Delay_ms(2000);
		
    //4.Partial refresh, example shows time
//			UBYTE Rotate = IMAGE_ROTATE_90;
    Paint_NewImage(IMAGE_BW, EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, IMAGE_ROTATE_90, IMAGE_COLOR_POSITIVE);
		//Paint_Clear(WHITE);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    for (int i=0; i<10; i++){
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        if (Rotate == IMAGE_ROTATE_0 || Rotate == IMAGE_ROTATE_180) {
            Paint_ClearWindows(15, 75, 15 + Font20.Width * 7, 75 + Font20.Height, WHITE);
            Paint_DrawTime(15, 75, &sPaint_time, &Font20, WHITE, BLACK);
        } else {
            Paint_ClearWindows(120, 30, 120 + Font20.Width * 7, 30 + Font20.Height, WHITE);
            Paint_DrawTime(120, 30, &sPaint_time, &Font20, WHITE, BLACK);
        }
        EPD_2IN9D_DisplayPart();
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif
	DEV_Delay_ms(3000);
	EPD_2IN9D_Clear();
	
	EPD_2IN9D_Sleep();
	DEV_Module_Exit();
}





