#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../image.h"




int main() {
    char *ptr;
    char input[] = "Noi Display,100,0,22,10,03,8";
    char input2[] = "0,00,03,80,00,03,80,00,01,00,00,01,FF";

    printf("%p\n", input);
    ImagePtr img = imageNew();

    ptr = imageParseInputHeader(img, input);
    imagePrint(img, true);
    ptr = imageParseInputBodyChunk(img, ptr);
    ptr = imageParseInputBodyChunk(img, input2);

    imagePrint(img, true);
    img = imageFree(img);

    return 0;
}