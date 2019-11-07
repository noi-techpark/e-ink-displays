#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../image.h"




int main() {
    int pos = 0;
    int chunkSize = 5;

    char *ptr;
    char input[] = "Noi Display,100,0,22,7,03,80,00";
    char input2[] = "03,80,00,00,01,00,00,01,00,03,80,00";

    printf("%p\n", input);
    ImagePtr img = imageNew();

    ptr = imageParseInputHeader(img, input);
    ptr = imageParseInputBodyChunk(img, ptr);
    ptr = imageParseInputBodyChunk(img, input2);

    imagePrint(img, true);
    img = imageFree(img);

    return 0;
}