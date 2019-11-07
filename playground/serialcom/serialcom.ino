const byte numLEDs = 2;
byte ledPin[numLEDs] = {12, 13};
unsigned long LEDinterval[numLEDs] = {200, 400};
unsigned long prevLEDmillis[numLEDs] = {0, 0};

const byte BUFFER_SIZE = 40;
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
const unsigned int IMG_DATA_SIZE = 1024;
unsigned char imgData[IMG_DATA_SIZE];


unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

//=============

void setup() {
  Serial.begin(9600);

  // flash LEDs so we know we are alive
  for (byte n = 0; n < numLEDs; n++) {
    pinMode(ledPin[n], OUTPUT);
    digitalWrite(ledPin[n], HIGH);
  }
  delay(500); // delay() is OK in setup as it only happens once

  for (byte n = 0; n < numLEDs; n++) {
    digitalWrite(ledPin[n], LOW);
  }

  // tell the PC we are ready
  Serial.println("<Arduino is ready>");
}

//=============

void loop() {
  curMillis = millis();
  getDataFromPC();
  updateFlashInterval();
  replyToPC();
  flashLEDs();
}

//=============

void getDataFromPC() {

  // receive data from PC and save it into inputBuffer

  if (Serial.available() > 0) {

    char x = Serial.read();

    // the order of these IF clauses is significant

    if (x == endMarker) {
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
    for(int i = 0; i < imgDataIdx; i++) {
      Serial.print(imgData[i], HEX);
      Serial.print(" ");
    }
    Serial.println(">");
  }
}

void updateFlashInterval() {

  // this illustrates using different inputs to call different functions
  if (strcmp(messageFromPC, "LED1") == 0) {
    updateLED1();
  }

  if (strcmp(messageFromPC, "LED2") == 0) {
    updateLED2();
  }
}

void updateLED1() {

  if (imgHeight > 100) {
    LEDinterval[0] = imgHeight;
  }
}

void updateLED2() {

  if (imgHeight > 100) {
    LEDinterval[1] = imgHeight;
  }
}

void flashLEDs() {

  for (byte n = 0; n < numLEDs; n++) {
    if (curMillis - prevLEDmillis[n] >= LEDinterval[n]) {
      prevLEDmillis[n] += LEDinterval[n];
      digitalWrite( ledPin[n], ! digitalRead( ledPin[n]) );
    }
  }
}
