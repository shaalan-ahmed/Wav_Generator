#include "declarations.h"

void writeBytes(FILE* file, int value, int byte_size) {
    fwrite(&value, byte_size, 1, file);
}

void wavWrite(FILE* file, string s) {
    fwrite(s.c_str(), 1UL, s.size(), file);
}