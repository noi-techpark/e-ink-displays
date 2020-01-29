#include "image.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEST 0

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    #include <Arduino.h>
    static char sprintfBuffer[256] = {0};
    #define out(...) do { sprintf(sprintfBuffer, __VA_ARGS__); Serial.print(sprintfBuffer); } while(0)
#elif TEST

    static char sprintfBuffer[128] = {0};
    #define out(...) do { sprintf(sprintfBuffer, __VA_ARGS__); printf("%s", sprintfBuffer); } while(0)

#endif

ImagePtr
imageNew() {
    ImagePtr img = (ImagePtr) calloc(sizeof(struct Image), 1);
    Serial.println("NEW IMAGE CREATED");
    return img;
}

void 
imageSetName(ImagePtr img, const char *name) {
    //out("DATAS = %ld\n", img->dataSize);
    strncpy(img->name, name, IMAGE_NAME_SIZE-1); 
    img->hasName = true;
    Serial.print("NEW IMAGE NAME = ");
    Serial.println(img->name);
    //out("DATAS = %ld\n", img->dataSize);
}

void 
imagePrint(ImagePtr img, bool withData) {
    Serial.print("Image ");
    if (img == NULL) {
        Serial.println("(NULL)");
    } else {
        //out("Image (name=%s, x=%d, y=%d, h=%d, w=%d, dataSize=%ld)\n", img->name, img->x, img->y, img->h, img->w, img->dataSize);
        Serial.print("(name='");
        Serial.print(img->name);
        Serial.print("', x=");
        Serial.print(img->x);
        Serial.print(", y=");
        Serial.print(img->y);
        Serial.print(", w=");
        Serial.print(img->w);
        Serial.print(", h=");
        Serial.print(img->h);
        Serial.print(", dataSize=");
        Serial.print(img->dataSize);
        Serial.println(")");
        if (withData && img->dataSize > 0) {

            unsigned char *ptr = img->data;

            for(unsigned int y = 0; y < img->h; y++) {
                for (unsigned int x = 0; x < img->w; x++) {
                    if (pgm_read_byte2(ptr) & (0x80 >> (x % 8))) {
                        Serial.print("x");
                    } else {
                        Serial.print(".");
                    }
                    //Serial.println((0x80 >> (x % 8)), HEX);                    
                    //One pixel is 8 bits
                    if (x % 8 == 7) {
                        ptr++;
                    }
                }
                //Serial.print("----------------");
                Serial.println("");

            }
        }
    }
}

void 
imageAddData(ImagePtr img, char *dataString) {
    if (img->data == NULL) {
        img->data = (unsigned char *) calloc(sizeof(unsigned char), IMAGE_DATA_CHUNK_SIZE);
        img->dataSizeAllocated = IMAGE_DATA_CHUNK_SIZE;
        //out("DATAS = %ld\n", img->dataSize);
        img->dataSize = 0;
        Serial.print("IMG: NEW ALLOC -> ");
        Serial.println(img->dataSize);
    }
    if (img->dataSizeAllocated < img->dataSize) {
        img->dataSizeAllocated += IMAGE_DATA_CHUNK_SIZE;
        img->data = (unsigned char *) realloc(img->data, img->dataSizeAllocated);
    }
    long data = strtol(dataString, 0, 16);
    if (img->hasResidual && strlen(dataString) == 1) {
        img->data[img->dataSize - 1] = img->data[img->dataSize - 1] * 16 + data;
        img->hasResidual = true;
        //out("IMG: UPDATE RESIDUAL %s/%ld -->  (%ld): %d\n", dataString, data, img->dataSize - 1, img->data[img->dataSize - 1]);
        Serial.print("ADD RSDL SERIAL -->");
        Serial.print(img->dataSize);
        Serial.print(" / ");
        Serial.println(img->data[img->dataSize - 1]);
    } else {
        img->dataSize++;
        img->data[img->dataSize - 1] = data;
        img->hasResidual = strlen(dataString) == 1;
        //out("IMG: ADD DATA        %s/%3ld --> (%ld): %d\n", dataString, data, img->dataSize, img->data[img->dataSize - 1]);
        Serial.print("ADD DATA SERIAL --> ");
        Serial.print(img->dataSize);
        Serial.print(" / ");
        Serial.println(img->data[img->dataSize - 1]);
        //out("DATAS = %ld\n", img->dataSize);
    }
}

ImagePtr 
imageFree(ImagePtr img) {
    free(img->data);
    free(img);
    return NULL;
}

char *
imageParseInputHeader(ImagePtr img, char *input) {
    if (img->hasName) {
      return input;
    }
    char *ptr;
    ptr = strtok(input, ",");
    imageSetName(img, ptr);
    ptr = strtok(NULL, ",");
    img->x = atoi(ptr);
    ptr = strtok(NULL, ",");
    img->y = atoi(ptr);
    ptr = strtok(NULL, ",");
    img->w = atoi(ptr);
    ptr = strtok(NULL, ",");
    img->h = atoi(ptr);
    return ptr + strlen(ptr) + 1;
}

char *
imageParseInputBodyChunk(ImagePtr img, char *input) {
    int length = 0;
    char *ptr;
    ptr = strtok(input, ",");
    length += strlen(ptr) + 1;
    //printf("L=%d %s\n", length, ptr);

    while(ptr != NULL && *ptr != 0) {
        imageAddData(img, ptr);
        length += strlen(ptr) + 1;
        ptr = strtok(NULL, ",");
        //printf("L=%ld length=%d %s\n", ptr == NULL ? -1 : strlen(ptr), length, ptr);
    }
    return ptr + length;
}
