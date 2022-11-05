#ifndef CML_CORE_INCLUDED
#define CML_CORE_INCLUDED

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

#define NUM_OF_ARGS(type, ...) \
    (sizeof((type[]){0.0f, ##__VA_ARGS__}) / sizeof(type) - 1)

typedef unsigned char cml_u8;
typedef unsigned short cml_u16;
typedef unsigned int cml_u32;
typedef unsigned long long cml_u64;

typedef signed char cml_i8;
typedef signed short cml_i16;
typedef signed int cml_i32;
typedef signed long long cml_i64;

void swap_int(int* _1, int* _2);

void swap_float(float* _1, float* _2);

#endif