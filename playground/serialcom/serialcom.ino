#include "image.h"

ImagePtr img;
char *inputPtr;

const byte BUFFER_SIZE = 128;
char inputBuffer[BUFFER_SIZE];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;


char messageFromPC[BUFFER_SIZE] = {0};

unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

//=============

void setup() {
  Serial.begin(9600);
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

  Serial.print("R");
  if (Serial.available() > 0) {

    char x = Serial.read();

    Serial.print("R");

    // the order of these IF clauses is significant

    if (readInProgress && (bytesRecvd > BUFFER_SIZE || x == endMarker || x == 10)) {
      if (x == endMarker) {
        readInProgress = false;
      }
      //bytesRecvd = BUFFER_SIZE - 1;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      Serial.print("BUFFER FULL: ");
      Serial.println(inputBuffer);
      bytesRecvd = 0;
      inputPtr = imageParseInputHeader(img, inputBuffer);
      inputPtr = imageParseInputBodyChunk(img, inputPtr);
    }

    if (readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
    }

    if (x == startMarker) {
      Serial.println("STARTMARKER FOUND");
      bytesRecvd = 0;
      readInProgress = true;
      imageFree(img);
      img = imageNew();
      imagePrint(img, true);
    }
  }
}

void replyToPC() {

  if (newDataFromPC) {
    newDataFromPC = false;
    if (!readInProgress) {
      imagePrint(img, true);
    }
  }
}
