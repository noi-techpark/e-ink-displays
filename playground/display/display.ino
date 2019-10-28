//#include <SD.h>

#include "EPD.h"
#include "GUI_Paint.h"
#include "graphics.c"
// #include "EPD_SDCard.h"

#define BUFSIZE 256

unsigned char text[BUFSIZE];
int text_index = 0;
int changed = 0;
char buf[2];
size_t buf_read;

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

    // EPD_7IN5_Sleep();
    // DEV_Module_Exit();
}

//const unsigned char* img = (unsigned char*) malloc(24*3);

 
void loop() {
    if(Serial.available() > 0) { // A byte is ready to receive
        // buf_read = Serial.readBytes(buf, 2);
        inByte = Serial.read();
        // if(buf_read == 2 && buf[0] != '.' && buf[1] != '.' && text_index < BUFSIZE) { 
        //     inByte = buf[0] * 16 + buf[1];
        //     text[text_index] = inByte;
        //     text_index++;
        //     Serial.print("Reading char = ");
        //     Serial.println(inByte, HEX);
        //     changed = 0;
        // } else {
        //     text[text_index] = '\0';
        //     Serial.println("Reading text done!");
        //     changed = 1;
        // }
        Serial.print("Reading char = ");
        Serial.println(inByte);

        if (inByte == '0') {
            // changed = 1;    
            paint_image_noi_noimage();
        } else if (inByte == '1') {
            paint_image_noi();
        } else if (inByte == '2') {
            paint_image_car();
        } else {
            Serial.println("Invalid input: Type 0 for NOI, 1 for NOI-IMAGE and 2 for CAR...");
        }
    }

//    if (changed) {
//        Serial.print("PRINTING: ");
//        // const unsigned char *ptr = img;
//        // for (int y = 0; y < 24; y++) {
//        //     for (int x = 0; x < 3; x++) {
//        //         Serial.print(text[y + x], HEX);
//        //         Serial.print(", ");
//        //     }
//        //     Serial.println();
//        // }
//        // Serial.println(text, HEX);
//
//        Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
//        Paint_Clear(BLACK);
//        // Paint_DrawBitMap();
//
//        // 2. Drawing on the image
//        // Paint_NewImage(IMAGE_BW, 3, 24, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
//        Paint_Draw(400, 100, 195, 146, BLACK, WHITE, car);
//
//        // Paint_DrawPoint(300, 300, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);
//
//        Paint_DrawString_EN(50, 20, "Parking Lot", &Font24, BLACK, WHITE);
//        Paint_DrawString_EN(50, 60, "Bolzano", &Font24, BLACK, WHITE);
//        Paint_DrawString_EN(50, 250, "Waltherplatz", &Font24, BLACK, WHITE);
//
//        // 3. Refresh the picture in RAM to e-Paper
//        Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
//        EPD_7IN5_Display();
//
//        
//        // const unsigned char* tst = text;
//        // Paint_Draw(100, 100, 17, 24, BLACK, WHITE, tst);
//        // // Paint_DrawPoint(20, 20, BLACK, DOT_PIXEL_DFT, DOT_STYLE_DFT);
//        // // Paint_DrawString_EN(50, 300, text, &Font24, BLACK, WHITE);
//        // EPD_7IN5_Display();
//        // // EPD_7IN5_Sleep();
//        // changed = 0;
//        // text_index = 0;
//        // for (int i = 0; i < BUFSIZE; i++) {
//        //     text[i] = 0;
//        // }
//    }
} 

void paint_image_noi_noimage() {
    Serial.println("SWITCHING TO NOI (NO IMAGE). PLEASE WAIT...");
    Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(BLACK);
    Paint_DrawString_EN(50, 20, "A1.1.33l", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "NOI", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Free Software Lab", &Font24, BLACK, WHITE);
    Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
    EPD_7IN5_Display();
}

void paint_image_noi() {
    Serial.println("SWITCHING TO NOI. PLEASE WAIT...");
    // 1. Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(BLACK);
    // EPD_7IN5_Display();
    // Paint_DrawBitMap(full);

    // 2. Drawing on the image
    // Paint_NewImage(IMAGE_BW, 3, 24, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);

    Paint_Draw(300, 50, 272, 131, BLACK, WHITE, noi_inv);

    // Paint_DrawPoint(300, 300, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);

    Paint_DrawString_EN(50, 20, "A1.1.33l", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "NOI", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Free Software Lab", &Font24, BLACK, WHITE);

    // 3. Refresh the picture in RAM to e-Paper
    Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
    EPD_7IN5_Display();
}

void paint_image_car() {
    Serial.println("SWITCHING TO CAR. PLEASE WAIT...");
    // 1. Create a new image cache named IMAGE_BW and fill it with white
    Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Clear(BLACK);
    // Paint_DrawBitMap();

    // 2. Drawing on the image
    // Paint_NewImage(IMAGE_BW, 3, 24, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
    Paint_Draw(400, 100, 195, 146, BLACK, WHITE, car);

    // Paint_DrawPoint(300, 300, WHITE, DOT_PIXEL_2X2, DOT_STYLE_DFT);

    Paint_DrawString_EN(50, 20, "Parking Lot", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 60, "Bolzano", &Font24, BLACK, WHITE);
    Paint_DrawString_EN(50, 250, "Waltherplatz", &Font24, BLACK, WHITE);

    // 3. Refresh the picture in RAM to e-Paper
    Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
    EPD_7IN5_Display();
}

/******************************************************************************
function:	Display monochrome bitmap
parameter:
    image_buffer ：A picture data converted to a bitmap
info:
    Use a computer to convert the image into a corresponding array,
    and then embed the array directly into Imagedata.cpp as a .c file.
******************************************************************************/
// void Paint_DrawBitMap2(UWORD Xpoint, UWORD Ypoint, UWORD Width, UWORD Height, const unsigned char* image_buffer)
// {
//     UWORD Xpoint, Ypoint, Height, Width;
//     Height = Paint_Image.Memory_Height;
//     Width = (Paint_Image.Memory_Width % 8 == 0)? (Paint_Image.Memory_Width / 8 ): (Paint_Image.Memory_Width / 8 + 1);
//     UDOUBLE Offset = Paint_Image.Image_Offset;
//     UDOUBLE Addr = 0;

//     for (Ypoint = 0; Ypoint < Height; Ypoint++) {
//         for (Xpoint = 0; Xpoint < Width; Xpoint++) {//8 pixel =  1 byte
//             Addr = Xpoint + Ypoint * Width + Offset;					
//             SPIRAM_WR_Byte(Addr, pgm_read_byte(image_buffer+Xpoint + Ypoint * Width));
//         }
//     }
// }


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
void Paint_Draw(UWORD Xpoint, UWORD Ypoint, UWORD Width, UWORD Height, UWORD Color_Background, UWORD Color_Foreground,const unsigned char* image_buffer)
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
