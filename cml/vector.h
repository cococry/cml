#ifndef CML_VECTOR_INCLUDED
#define CML_VECTOR_INCLUDED

#include <stdarg.h>
#include <stdio.h>

#include "internal/cml_core.h"

/*
    Defines the structure of a vector
    (dimension and values)
*/
typedef struct {
    cml_u32 dimension;
    float* values;
} vector;

/*
    Allocates memory for a vector with
    a given dimension (allocates space for
    n values | n = dimension).
*/
vector cml_vector_allocate(cml_u32 dimension);

/*
    Constructs and returns a vector with a given dimension.
    All values of the vector will be set to the
    given value.
*/
vector cml_vector_default(cml_u32 dimension, float value);

/*
    Constructs and returns a vector with a given dimension.
    All values of the vector will be set to zero.
*/
vector cml_vector_empty(cml_u32 dimension);

/*
    NOTE: Not recommended to use this function in client code.
          Use cml_vector() instead.

    Constructs and returns a vector with a given dimension
    and given values.
*/

/*
    Returns a stack allocated copy of the given vector.
*/
vector cml_vector_copy_mem(vector* v);

/*
    Free's the memory of the given vector.
*/

void cml_vector_free_mem(vector* v);

vector clm_vector_construct(cml_u32 dimension, ...);

/*
    This function prints a given vector "v" values
    in a specific layout to the console.
    LAYOUT: {10, 20, 30}
*/
void cml_vector_print(vector v);

/*
    Returns a boolean value that states if
    all elments of both given vectors v1 and v2
    are equal.
*/
BOOL cml_vector_compare(vector v1, vector v2);

/*
    Returns a vector which corresponds to the input
    vecotr v multiplied by the input scaler.
*/
vector cml_vector_scaler_mult(vector v, float scaler);

/*
    Multiplies the given vector v by the given scaler.
*/
void cml_vector_mult_by_scaler(vector* v, float scaler);

/*
    Returns a vector which corresponds to the input
    vecotr v divided by the input scaler.
*/
vector cml_vector_scaler_div(vector v, float scaler);

/*
    Divides the given vector v by the given scaler.
*/
void cml_vector_div_by_scaler(vector* v, float scaler);

/*
    Returns a vector which corresponds to the input
    scaler added to the input vector v.
*/
vector cml_vector_scaler_addition(vector v, float scaler);

/*
    Adds the given scaler to the given vector v.
*/
void cml_vector_add_scaler(vector* v, float scaler);

/*
    Returns a vector which corresponds to the input
    scaler substracted from the input vector v.
*/
vector cml_vector_scaler_subst(vector v, float scaler);

/*
    Substracts the given scaler from the given vector v.
*/

void cml_vector_subst_scaler(vector* v, float scaler);

/*
    Returns a vector which corresponds to the inpute
    vectors v1 and v2 multiplied.
*/
vector cml_vec_vec_mult(vector v1, vector v2);

/*
    Multiplies the input vector v1 with the input
    vector v2.
*/
void cml_vec_mult_with_vec(vector* v1, vector v2);

/*
    Returns a vector which corresponds to the input
    vector v1 divided by the input vector v2.
*/
vector cml_vec_vec_div(vector v1, vector v2);

/*
    Divides the given vector v1 by the given vector
    v2.
*/
void cml_vec_div_by_vec(vector* v1, vector v2);

/*
    Returns a vector which corresponds to the input
    vector v2 added to the input vector v1.
*/
vector cml_vec_vec_add(vector v1, vector v2);

/*
    Adds the given vector v2 to the given vector v1
*/
void cml_vec_add_to_vec(vector* v1, vector v2);

/*
    Returns a vector which corresponds to the input
    vector v2 substracted from the input vector v1.
*/
vector cml_vec_vec_subst(vector v1, vector v2);

/*
    Substracts the given vector v2 from the given vector v1,
*/
void cml_subst_vec_from_vec(vector* v1, vector v2);

/*
    Returns the dot product of the two given vectors v1 and v2,
*/
float cml_dot(vector v1, vector v2);

/*
    Returns a vector that represents the cross product of
    the two given vectors v1 and v2.
*/
vector cml_cross(vector v1, vector v2);

/*
    Returns if two vectors are perpendicular to another.
    This is clarified by checking if the dot product of
    the two given vectors is zero.
*/

/*
    Returns the magnitude of the given vector v.
*/
float cml_vector_magnitude(vector v);

/*
    Returns the squared magnitude of the given vector v.
*/
float cml_vector_magnitude_squared(vector v);

BOOL cml_vector_perpendicular(vector v1, vector v2);

/*
    Returns a vector that is the normalized verison of
    the given vector v.
*/
vector cml_vector_normalized(vector v);

/*
    Normalizes a given vector v.
*/
void cml_vector_normalize(vector* v);

/*
    Returns a vector that is the given vector v
    raised by the power of the given value "val".
*/
vector cml_vector_raised_by(vector v, float val);

/*
    Raises the vector to the power of the given
    value "val".
*/
void cml_vector_raise_by(vector* v, float val);

/*
    Returns the value at the given index from
    the given vectors values array.
*/
float cml_vector_get_value_at_index(vector v, cml_u32 index);

/*
    Returns the distance between two vectors.
*/
float cml_vector_distance(vector v1, vector v2);

/*
    This macro is used to construct a vector in client code.

    The macro calls the internal "cml_vector_construct" function
    and uses "NUM_OF_ARGS" (defined in cml_core.h) as the dimension.
    It passes all the given values (__VA_ARGS__) to the function.
*/
#define cml_vector(...) \
    clm_vector_construct(NUM_OF_ARGS(float, __VA_ARGS__), ##__VA_ARGS__)

#endif