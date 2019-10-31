#include "EPD.h"
#include "GUI_Paint.h"
#include "graphics.c"

char inByte; // Stores incoming command

void setup() {
    Serial.begin(9600);
    Serial.println("7.5INCH E-PAPER DEMO");

    DEV_Module_Init();
    EPD_7IN5_Init();
    EPD_7IN5_Clear();
    DEV_Delay_ms(500);

    Serial.println("Display Init done");

    paint_image_noi_noimage();

    Serial.println("Initial screen sent: Type 0 for NOI, 1 for NOI-IMAGE and 2 for CAR...");
}

void loop() {
    if(Serial.available() > 0) { // A byte is ready to receive
        inByte = Serial.read();
        Serial.print("Reading char = ");
        Serial.println(inByte);

        if (inByte == '0') {
            paint_image_noi_noimage();
        } else if (inByte == '1') {
            paint_image_noi();
        } else if (inByte == '2') {
            paint_image_car();
        } else {
            Serial.println("Invalid input: Type 0 for NOI, 1 for NOI-IMAGE and 2 for CAR...");
        }
    }
} 

void paint_image_noi_noimage() {
    paint_init("NOI (NO IMAGE)");
    Paint_DrawString_EN(50, 20, "A1.1.33l", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "NOI", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Free Software Lab", &Font24, BLACK, WHITE);
    paint_finalize();
}

void paint_image_noi() {
    paint_init("NOI");
    paint_draw(300, 50, 272, 131, BLACK, WHITE, noi_inv);
    Paint_DrawString_EN(50, 20, "A1.1.33l", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "NOI", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Free Software Lab", &Font24, BLACK, WHITE);
    paint_finalize();
}

void paint_image_car() {
    paint_init("CAR");
    paint_draw(400, 100, 195, 146, BLACK, WHITE, car);
    Paint_DrawString_EN(50, 20, "Parking Lot", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "Bolzano", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Waltherplatz", &Font24, BLACK, WHITE);
    paint_finalize();
}

void paint_init(const char *img_name) {
    Serial.print("SWITCHING TO ");
    Serial.print(img_name);
    Serial.println(". PLEASE WAIT...");
    Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(BLACK);
}

void paint_finalize() {
    Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
    EPD_7IN5_Display();
}

/******************************************************************************
function:	Show English characters
parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void paint_draw(UWORD Xpoint, UWORD Ypoint, UWORD Width, UWORD Height, UWORD Color_Background, UWORD Color_Foreground,const unsigned char* image_buffer)
{
    UWORD Page, Column;

    const unsigned char *ptr = image_buffer;

    for (Page = 0; Page < Height; Page ++ ) {
        for (Column = 0; Column < Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if (pgm_read_byte(ptr) & (0x80 >> (Column % 8)))
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if (pgm_read_byte(ptr) & (0x80 >> (Column % 8))) {
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    Paint_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            //One pixel is 8 bits
            if (Column % 8 == 7)
                ptr++;
        }// Write a line
        if (Width % 8 != 0)
            ptr++;
    }// Write all
}
