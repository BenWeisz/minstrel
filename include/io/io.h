#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>

#include "io/log.h"

#define RESOURCE "../data/"

unsigned char* IO_read_internal(const char* path, unsigned int* size, const unsigned int padding);

unsigned char* IO_read_uchar(const char* path, unsigned int* size);

char* IO_read_char(const char* path);

char* IO_read_char_sized(const char* path, unsigned int* size);

#endif // IO_H
