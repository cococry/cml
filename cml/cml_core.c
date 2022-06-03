#include "internal/cml_core.h"

void swap_int(int* _1, int* _2) {
    *_1 ^= *_2;
    *_2 = *_1 ^ *_2;
    *_1 ^= *_2;
}

void swap_float(float* _1, float* _2) { swap_int((int*)_1, (int*)_2); }