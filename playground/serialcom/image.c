#include "image.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ImagePtr
imageNew() {
    ImagePtr img = malloc(sizeof(struct Image));
    img->x = -1;
    img->y = -1;
    img->w = -1;
    img->h = -1;
    img->hasName = 0;
    memset(img->name, 0, IMAGE_NAME_SIZE);
    img->dataSize = 0;
    img->dataSizeAllocated = 0;
    img->data = NULL;
    img->hasResidual = false;
    return img;
}

void 
imageSetName(ImagePtr img, const char *name) {
    strncpy(img->name, name, IMAGE_NAME_SIZE); 
    img->hasName = 1;
}
#ifndef pgm_read_byte
 #define pgm_read_byte(addr) (*(unsigned char *)(addr))
#endif

void 
imagePrint(ImagePtr img, bool withData) {
    if (img == NULL) {
        printf("Image (NULL)\n");
    } else {
        printf("Image (name=%s, x=%d, y=%d, h=%d, w=%d, dataSize=%ld)\n", img->name, img->x, img->y, img->h, img->w, img->dataSize);
        if (withData) {

            unsigned char *ptr = img->data;

            for(unsigned int y = 0; y < img->h; y++) {
                for (unsigned int x = 0; x < img->w; x++) {
                    if (pgm_read_byte(ptr) & (0x80 >> (x % 8))) {
                        printf("x");
                    } else {
                        printf(".");
                    }
                    
                    //One pixel is 8 bits
                    if (x % 8 == 7) {
                        ptr++;
                    }
                }
                printf("\n");
                if (y % 8 != 0) {
                    ptr++;
                }
            }
        }
    }
}

void 
imageAddData(ImagePtr img, char *dataString) {
    if (img->data == NULL) {
        img->data = malloc(sizeof(long) * IMAGE_DATA_CHUNK_SIZE);
        img->dataSizeAllocated = IMAGE_DATA_CHUNK_SIZE;
    }
    if (img->dataSizeAllocated < img->dataSize) {
        img->dataSizeAllocated += IMAGE_DATA_CHUNK_SIZE;
        img->data = realloc(img->data, img->dataSizeAllocated);
    }
    long data = strtol(dataString, 0, 16);
    if (img->hasResidual && strlen(dataString) == 1) {
        img->data[img->dataSize - 1] = img->data[img->dataSize - 1] * 16 + data;
        img->hasResidual = 0;
        printf("IMG: UPDATE RESIDUAL (%ld): %d\n", img->dataSize - 1, img->data[img->dataSize - 1]);
    } else {
        img->dataSize++;
        img->data[img->dataSize - 1] = data;
        img->hasResidual = strlen(dataString) == 1 ? 1 : 0;
        printf("IMG: ADD DATA (%ld): %d\n", img->dataSize - 1, img->data[img->dataSize - 1]);
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
    printf("L=%d %s\n", length, ptr);

    while(ptr != NULL && *ptr != 0) {
        imageAddData(img, ptr);
        length += strlen(ptr) + 1;
        ptr = strtok(NULL, ",");
        printf("L=%ld length=%d %s\n", ptr == NULL ? -1 : strlen(ptr), length, ptr);
    }
    return ptr + length;
}
