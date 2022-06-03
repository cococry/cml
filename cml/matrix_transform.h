#ifndef CML_MATRIX_TRANSFORM_INCLUDED
#define CML_MATRIX_TRANSFORM_INCLUDED

#include "matrix.h"
#include "vector.h"

matrix cml_translate(matrix m, vector v);

matrix cml_rotate(matrix m, float angle, vector v);

matrix cml_scale(matrix m, vector v);

matrix cml_look_at(vector eye, vector center, vector up);

matrix cml_perspective(float fov, float aspect_ratio, float near_plane, float far_plane);

matrix cml_ortho(float left, float right, float bottom, float top);

#endif  // CML_MATRIX_TRANSFORM_INCLUDED