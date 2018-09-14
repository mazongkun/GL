/*
 * @Author: mazongkun 
 * @Date: 2018-09-13 11:43:31 
 * @Last Modified by: mazongkun
 * @Last Modified time: 2018-09-13 14:12:10
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdlib.h>

void readFileData(const char *filePath, char *outData, int length)
{
    if (filePath == NULL) {
        perror("file NULL.\n");
        return;
    }

    FILE * file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("file %s open failed.\n", filePath);
        return;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    int readLength = length < size ? length : size;

    fseek(file, 0, SEEK_SET);
    fread(outData, sizeof(char), readLength, file);
    fclose(file);
}

#endif