#include "vector.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

vector cml_vector_allocate(cml_u32 dimension) {
    vector ret;

    ret.dimension = dimension;
    ret.values = malloc(dimension * sizeof(float));

    return ret;
}

vector cml_vector_default(cml_u32 dimension, float value) {
    vector ret = cml_vector_allocate(dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = value;
    }

    return ret;
}

vector cml_vector_empty(cml_u32 dimension) {
    return cml_vector_default(dimension, 0.0f);
}

vector cml_vector_copy_mem(vector* v) {
    vector ret;
    memcpy(&ret, v, sizeof(vector));

    return ret;
}

void cml_vector_free_mem(vector* v) {
    free(v->values);
    v->dimension = 0;
}
vector clm_vector_construct(cml_u32 dimension, ...) {
    vector ret = cml_vector_allocate(dimension);

    va_list va;
    va_start(va, dimension);

    for (cml_u32 i = 0; i < dimension; i++) {
        ret.values[i] = (float)va_arg(va, double);
    }

    va_end(va);

    return ret;
}

void cml_vector_print(vector v) {
    printf("{ ");

    for (cml_u32 i = 0; i < v.dimension; i++) {
        printf("%f", v.values[i]);

        if (i < v.dimension - 1) {
            printf(", ");
        } else {
            printf(" ");
        }
    }

    printf("}\n");
}

BOOL cml_vector_compare(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    BOOL ret = TRUE;

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        if (v1.values[i] != v2.values[i]) {
            ret = FALSE;
        }
    }

    return ret;
}

vector cml_vector_scaler_mult(vector v, float scaler) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = v.values[i] * scaler;
    }

    return ret;
}

void cml_vector_mult_by_scaler(vector* v, float scaler) {
    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] *= scaler;
    }
}

vector cml_vector_scaler_div(vector v, float scaler) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = v.values[i] / scaler;
    }

    return ret;
}

void cml_vector_div_by_scaler(vector* v, float scaler) {
    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] *= scaler;
    }
}

vector cml_vector_scaler_addition(vector v, float scaler) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = v.values[i] + scaler;
    }

    return ret;
}

void cml_vector_add_scaler(vector* v, float scaler) {
    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] += scaler;
    }
}

vector cml_vector_scaler_subst(vector v, float scaler) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = v.values[i] - scaler;
    }

    return ret;
}

void cml_vector_subst_scaler(vector* v, float scaler) {
    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] -= scaler;
    }
}

vector cml_vec_vec_mult(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    vector ret = cml_vector_allocate(v1.dimension);

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        ret.values[i] = v1.values[i] * v2.values[i];
    }
    return ret;
}

void cml_vec_mult_with_vec(vector* v1, vector v2) {
    assert(v1->dimension == v2.dimension);

    for (cml_u32 i = 0; i < v1->dimension; i++) {
        v1->values[i] *= v2.values[i];
    }
}

vector cml_vec_vec_div(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    vector ret = cml_vector_allocate(v1.dimension);

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        ret.values[i] = v1.values[i] / v2.values[i];
    }
    return ret;
}

void cml_vec_div_by_vec(vector* v1, vector v2) {
    assert(v1->dimension == v2.dimension);

    for (cml_u32 i = 0; i < v1->dimension; i++) {
        v1->values[i] /= v2.values[i];
    }
}

vector cml_vec_vec_add(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    vector ret = cml_vector_allocate(v1.dimension);

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        ret.values[i] = v1.values[i] + v2.values[i];
    }
    return ret;
}

void cml_vec_add_to_vec(vector* v1, vector v2) {
    assert(v1->dimension == v2.dimension);

    for (cml_u32 i = 0; i < v1->dimension; i++) {
        v1->values[i] += v2.values[i];
    }
}

vector cml_vec_vec_subst(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    vector ret = cml_vector_allocate(v1.dimension);

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        ret.values[i] = v1.values[i] - v2.values[i];
    }
    return ret;
}

void cml_subst_vec_from_vec(vector* v1, vector v2) {
    assert(v1->dimension == v2.dimension);

    for (cml_u32 i = 0; i < v1->dimension; i++) {
        v1->values[i] -= v2.values[i];
    }
}

float cml_dot(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    float ret = 0.0f;

    for (cml_u32 i = 0; i < v1.dimension; i++) {
        ret += v1.values[i] * v2.values[i];
    }
    return ret;
}

BOOL cml_vector_perpendicular(vector v1, vector v2) {
    return (v1.dimension == v2.dimension) ? (cml_dot(v1, v2) == 0.0f) : FALSE;
}

vector cml_cross(vector v1, vector v2) {
    assert(v1.dimension == v2.dimension);

    vector ret = cml_vector_allocate(v1.dimension);

    ret.values[0] =
        (v1.values[1] * v2.values[2]) - (v1.values[2] * v2.values[1]);
    ret.values[1] =
        -1 * ((v1.values[0] * v2.values[2]) - (v1.values[2] * v2.values[0]));
    ret.values[2] =
        (v1.values[0] * v2.values[1]) - (v1.values[1] * v2.values[0]);
    return ret;
}

float cml_vector_magnitude(vector v) {
    return (float)sqrt(cml_vector_magnitude_squared(v));
}

float cml_vector_magnitude_squared(vector v) {
    float ret = 0.0f;

    for (cml_u32 i = 0; i < v.dimension; i++) {
        ret += v.values[i] * v.values[i];
    }

    return ret;
}

vector cml_vector_normalized(vector v) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = v.values[i] / cml_vector_magnitude(v);
    }
    return ret;
}

void cml_vector_normalize(vector* v) {
    float mag = cml_vector_magnitude(*v);

    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] /= mag;
    }
}

vector cml_vector_raised_by(vector v, float val) {
    vector ret = cml_vector_allocate(v.dimension);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = powf(v.values[i], val);
    }
    return ret;
}

void cml_vector_raise_by(vector* v, float val) {
    for (cml_u32 i = 0; i < v->dimension; i++) {
        v->values[i] = powf(v->values[i], val);
    }
}

float cml_vector_get_value_at_index(vector v, cml_u32 index) {
    return v.values[index];
}

float cml_vector_distance(vector v1, vector v2) {
    vector ret = cml_vec_vec_subst(v1, v2);

    return cml_vector_magnitude(ret);
}