#include "EPD.h"
#include "GUI_Paint.h"

const byte BUFFER_SIZE = 128;
char inputBuffer[BUFFER_SIZE];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char messageFromPC[BUFFER_SIZE] = {0};

// Image specification retrieved
int imgHeight = 0;
int imgWidth = 0;
int imgPosX = 0;
int imgPosY = 0;
int imgDataIdx = 0;
const unsigned int IMG_DATA_SIZE = 512;
unsigned char imgData[IMG_DATA_SIZE];


unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

//=============

void setup() {
  Serial.begin(9600);

  DEV_Module_Init();
  EPD_7IN5_Init();
  EPD_7IN5_Clear();
  DEV_Delay_ms(500);

  Serial.println("Display Init done");

  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
}

//=============

void loop() {
  curMillis = millis();
  getDataFromPC();
  replyToPC();
}

//=============

void getDataFromPC() {

  // receive data from PC and save it into inputBuffer

  if (Serial.available() > 0) {

    char x = Serial.read();

    // the order of these IF clauses is significant

    if (x == endMarker || bytesRecvd == BUFFER_SIZE) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }

    if (readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == BUFFER_SIZE) {
        bytesRecvd = BUFFER_SIZE - 1;
      }
    }

    if (x == startMarker) {
      bytesRecvd = 0;
      readInProgress = true;
    }
  }
}

//=============

void parseData() {

  // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(inputBuffer, ",");
  strcpy(messageFromPC, strtokIndx);

  strtokIndx = strtok(NULL, ",");
  imgPosX = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  imgPosY = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  imgWidth = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  imgHeight = atoi(strtokIndx);

  imgDataIdx = 0;
  while (strtokIndx != NULL) {
    strtokIndx = strtok(NULL, ",");
    imgData[imgDataIdx] = strtol(strtokIndx, 0, 16);
    imgDataIdx++;
    Serial.print(imgDataIdx);
    Serial.print(": \t ");
    Serial.print(strtokIndx);
    Serial.print("\t = ");
    Serial.print(imgData[imgDataIdx], HEX);
    Serial.println();
  }
  imgDataIdx--;

}

//=============

void replyToPC() {

  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<IMG = ");
    Serial.print(messageFromPC);
    Serial.print("; HEIGHT = ");
    Serial.print(imgHeight);
    Serial.print("; WIDTH = ");
    Serial.print(imgWidth);
    Serial.print("; POSX = ");
    Serial.print(imgPosX);
    Serial.print("; POSY = ");
    Serial.print(imgPosY);
    Serial.print("; DATA = ");
    for (int i = 0; i < imgDataIdx; i++) {
      Serial.print(imgData[i], HEX);
      Serial.print(" ");
    }
    Serial.println(">");

    paint_init(messageFromPC);
    paint_draw(imgPosX, imgPosY, imgWidth, imgHeight, BLACK, WHITE, imgData);
    paint_finalize();
  }
}

/******************************************************************************
  function:  Show English characters
  parameter:
    Xpoint           ：X coordinate
    Ypoint           ：Y coordinate
    Acsii_Char       ：To display the English characters
    Font             ：A structure pointer that displays a character size
    Color_Background : Select the background color of the English character
    Color_Foreground : Select the foreground color of the English character
******************************************************************************/
void paint_draw(UWORD Xpoint, UWORD Ypoint, UWORD Width, UWORD Height, UWORD Color_Background, UWORD Color_Foreground, const unsigned char* image_buffer)
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

void paint_init(const char *img_name) {
  Serial.print("SWITCHING TO ");
  Serial.print(img_name);
  Paint_NewImage(IMAGE_BW, EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, IMAGE_ROTATE_0, IMAGE_COLOR_INVERTED);
  Paint_Clear(BLACK);
}

void paint_finalize() {
  Serial.println("Use EPD_Display to move picture from RAM to e-Paper");
  EPD_7IN5_Display();
}
