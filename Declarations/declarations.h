#pragma once

#define MAX_AMPLITUDE 32760

#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

void write_as_bytes(FILE* file, int value, int byte_size);
void wavWrite(FILE* file, string s);