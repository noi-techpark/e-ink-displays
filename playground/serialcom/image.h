/*
 * image.h
 */
#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdlib.h>
#include <stdbool.h>

#define IMAGE_NAME_SIZE 16
#define IMAGE_DATA_CHUNK_SIZE 512

#ifndef pgm_read_byte2
  #define pgm_read_byte2(addr) (*(unsigned char *)(addr))
#endif


struct Image {
    bool hasName;
    bool hasResidual;
    char name[IMAGE_NAME_SIZE];
    unsigned int x, y, w, h;
    size_t dataSize;
    size_t dataSizeAllocated;
    unsigned char *data;
};

typedef struct Image *ImagePtr;

ImagePtr 
imageNew();

void 
imageSetName(ImagePtr img, const char *name);

void 
imagePrint(ImagePtr img, bool withData);

void 
imageAddData(ImagePtr img, char *dataString);

ImagePtr 
imageFree(ImagePtr img);

char * 
imageParseInputHeader(ImagePtr img, char *input);

char *
imageParseInputBodyChunk(ImagePtr img, char *input);

#endif
