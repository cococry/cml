#include "matrix_transform.h"

#include <assert.h>
#include <math.h>

matrix cml_translate(matrix m, vector v) {
    assert(m.cols == 4 && m.rows == 4);

    matrix ret = m;
    ret.values[3][0] += v.values[0];
    ret.values[3][1] += v.values[1];
    ret.values[3][2] += v.values[2];

    return ret;
}

matrix cml_rotate(matrix m, float angle, vector v) {
    assert(m.cols == 4 && m.rows == 4);

    const float a = angle;
    const float c = cos(a);
    const float s = sin(a);

    vector axis = cml_vector_normalized(v);

    vector tmp = cml_vector_default(3, 1 - c);

    cml_vec_mult_with_vec(&tmp, axis);

    matrix rotate = cml_matrix_allocate(4, 4);

    rotate.values[0][0] = c + tmp.values[0] * axis.values[0];
    rotate.values[0][1] = tmp.values[0] * axis.values[1] + s * axis.values[2];
    rotate.values[0][2] = tmp.values[0] * axis.values[2] - s * axis.values[1];

    rotate.values[1][0] = tmp.values[1] * axis.values[0] - s * axis.values[2];
    rotate.values[1][1] = c + tmp.values[1] * axis.values[1];
    rotate.values[1][2] = tmp.values[1] * axis.values[2] + s * axis.values[0];

    rotate.values[2][0] = tmp.values[2] * axis.values[0] + s * axis.values[1];
    rotate.values[2][1] = tmp.values[2] * axis.values[1] - s * axis.values[0];
    rotate.values[2][2] = c + tmp.values[2] * axis.values[2];

    matrix ret = cml_matrix_allocate(4, 4);

    vector r0 = cml_vec_vec_add(
        cml_vec_vec_add(cml_vector_scaler_mult(cml_matrix_get_col(&m, 1),
                                               rotate.values[0][0]),
                        cml_vector_scaler_mult(cml_matrix_get_col(&m, 2),
                                               rotate.values[0][1])),
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 3), rotate.values[0][2]));
    vector r1 = cml_vec_vec_add(
        cml_vec_vec_add(cml_vector_scaler_mult(cml_matrix_get_col(&m, 1),
                                               rotate.values[1][0]),
                        cml_vector_scaler_mult(cml_matrix_get_col(&m, 2),
                                               rotate.values[1][1])),
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 3), rotate.values[1][2]));
    vector r2 = cml_vec_vec_add(
        cml_vec_vec_add(cml_vector_scaler_mult(cml_matrix_get_col(&m, 1),
                                               rotate.values[2][0]),
                        cml_vector_scaler_mult(cml_matrix_get_col(&m, 2),
                                               rotate.values[2][1])),
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 3), rotate.values[2][2]));
    vector r3 = cml_matrix_get_col(&m, 4);

    cml_matrix_set_row(&ret, 1, r0);
    cml_matrix_set_row(&ret, 2, r1);
    cml_matrix_set_row(&ret, 3, r2);
    cml_matrix_set_row(&ret, 4, r3);

    return ret;
}

matrix cml_scale(matrix m, vector v) {
    assert(m.cols == 4 && m.rows == 4);

    matrix ret = cml_matrix_allocate(4, 4);
    cml_matrix_set_row(
        &ret, 1,
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 1), v.values[0]));
    cml_matrix_set_row(
        &ret, 2,
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 2), v.values[1]));
    cml_matrix_set_row(
        &ret, 3,
        cml_vector_scaler_mult(cml_matrix_get_col(&m, 3), v.values[2]));
    cml_matrix_set_row(&ret, 4, cml_matrix_get_col(&m, 4));

    return ret;
}

matrix cml_look_at(vector eye, vector center, vector up) {
    assert(eye.dimension == 3 && center.dimension == 3 && up.dimension == 3);

    const vector f = cml_vector_normalized(cml_vec_vec_subst(center, eye));
    const vector s = cml_vector_normalized(cml_cross(f, up));
    const vector u = cml_cross(s, f);

    matrix ret = cml_matrix_identity(4);
    ret.values[0][0] = s.values[0];
    ret.values[1][0] = s.values[1];
    ret.values[2][0] = s.values[2];
    ret.values[0][1] = u.values[0];
    ret.values[1][1] = u.values[1];
    ret.values[2][1] = u.values[2];
    ret.values[0][2] = -f.values[0];
    ret.values[1][2] = -f.values[1];
    ret.values[2][2] = -f.values[2];
    ret.values[3][0] = -cml_dot(s, eye);
    ret.values[3][1] = -cml_dot(u, eye);
    ret.values[3][2] = cml_dot(f, eye);

    return ret;
}

matrix cml_perspective(float fov, float aspect_ratio, float near_plane,
                       float far_plane) {
    const float tan_half_fov = tan(fov / 2);

    matrix ret = cml_matrix_empty(4, 4);
    ret.values[0][0] = 1 / (aspect_ratio * tan_half_fov);
    ret.values[1][1] = 1 / tan_half_fov;
    ret.values[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
    ret.values[2][3] = -1;
    ret.values[3][2] = -(2 * far_plane * near_plane) / (far_plane - near_plane);

    return ret;
}

matrix cml_ortho(float left, float right, float bottom, float top) {
    matrix ret = cml_matrix_identity(4);
    ret.values[0][0] = 2 / (right - left);
    ret.values[1][1] = 2 / (top - bottom);
    ret.values[2][2] = -1;
    ret.values[3][0] = -(right + left) / (right - left);
    ret.values[3][1] = -(top + bottom) / (top - bottom);

    return ret;
}