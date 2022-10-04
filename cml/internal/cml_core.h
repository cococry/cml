#ifndef CML_CORE_INCLUDED
#define CML_CORE_INCLUDED

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define NUM_OF_ARGS(type, ...) \
    (sizeof((type[]){0.0f, ##__VA_ARGS__}) / sizeof(type) - 1)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed char i16;
typedef signed char i32;
typedef signed char i64;

void swap_int(int* _1, int* _2);

void swap_float(float* _1, float* _2);

#endif