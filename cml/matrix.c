#include "matrix.h"

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

matrix cml_matrix_allocate(cml_u32 rows, cml_u32 cols) {
    matrix ret;

    ret.cols = cols;
    ret.rows = rows;

    ret.values = malloc(sizeof(float) * rows * cols);

    for (cml_u32 i = 0; i < ret.rows; i++) {
        ret.values[i] = malloc(cols * sizeof(float));
    }
    return ret;
}

matrix cml_matrix_identity(cml_u32 dimension) {
    matrix ret = cml_matrix_allocate(dimension, dimension);

    for (cml_u32 r = 0; r < dimension; r++) {
        for (cml_u32 c = 0; c < dimension; c++) {
            ret.values[r][c] = (r == c) ? 1.0f : 0.0f;
        }
    }
    return ret;
}

matrix cml_matrix_empty(cml_u32 rows, cml_u32 cols) {
    matrix ret = cml_matrix_allocate(rows, cols);

    for (cml_u32 r = 0; r < rows; r++) {
        for (cml_u32 c = 0; c < cols; c++) {
            ret.values[r][c] = 0.0f;
        }
    }
    return ret;
}

matrix cml_matrix_construct(cml_u32 rows, cml_u32 cols, cml_u32 num_values, ...) {
    matrix ret = cml_matrix_allocate(rows, cols);

    va_list list;
    va_start(list, num_values);

    cml_u32 i = 0;
    for (cml_u32 r = 0; r < rows; r++) {
        for (cml_u32 c = 0; c < cols; c++) {
            if (i++ < num_values) {
                ret.values[r][c] = (float)va_arg(list, double);
            } else {
                ret.values[r][c] = 0.0f;
            }
        }
    }

    va_end(list);

    return ret;
}

matrix cml_matrix_copy_mem(matrix* m) {
    matrix ret;
    memcpy(&ret, m, sizeof(matrix));

    return ret;
}

void cml_matrix_print(matrix m) {
    printf("\n");
    for (cml_u32 r = 0; r < m.rows; r++) {
        printf("\n");

        printf(" |");
        for (cml_u32 c = 0; c < m.cols; c++) {
            printf(" %f", m.values[r][c]);
        }
        printf(" |");
    }
    printf("\n");
}

BOOL cml_matrix_compare(matrix m1, matrix m2) {
    assert(m1.rows == m2.rows && m1.cols == m2.cols);

    BOOL ret = TRUE;

    for (cml_u32 r = 0; r < m1.rows; r++) {
        for (cml_u32 c = 0; c < m1.cols; c++) {
            if (m1.values[r][c] != m2.values[r][c]) {
                ret = FALSE;
            }
        }
    }
    return ret;
}

vector cml_matrix_get_row(matrix* m, cml_u32 row) {
    row--;
    assert(!(row < 0 || row >= m->rows));

    vector ret = cml_vector_allocate(m->cols);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = m->values[row][i];
    }
    return ret;
}

vector cml_matrix_get_col(matrix* m, cml_u32 col) {
    col--;
    assert(col >= 0 && col <= m->rows);

    vector ret = cml_vector_allocate(m->rows);

    for (cml_u32 i = 0; i < ret.dimension; i++) {
        ret.values[i] = m->values[i][col];
    }
    return ret;
}

matrix cml_matrix_to_row_vec(vector* v) {
    matrix ret = cml_matrix_allocate(1, v->dimension);

    for (cml_u32 i = 0; i < v->dimension; i++) {
        ret.values[0][i] = v->values[i];
    }
    return ret;
}

matrix cml_matrix_to_col_vec(vector* v) {
    matrix ret = cml_matrix_allocate(v->dimension, 1);

    for (cml_u32 i = 0; i < v->dimension; i++) {
        ret.values[i][0] = v->values[i];
    }
    return ret;
}

matrix cml_matrix_scaler_addition(matrix m, float scaler) {
    matrix ret = cml_matrix_allocate(m.rows, m.cols);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = m.values[r][c] + scaler;
        }
    }

    return ret;
}

void cml_matrix_add_scaler(matrix* m, float scaler) {
    for (cml_u32 r = 0; r < m->rows; r++) {
        for (cml_u32 c = 0; c < m->cols; c++) {
            m->values[r][c] += scaler;
        }
    }
}

matrix cml_matrix_scaler_subst(matrix m, float scaler) {
    matrix ret = cml_matrix_allocate(m.rows, m.cols);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = m.values[r][c] - scaler;
        }
    }
    return ret;
}

void cml_matrix_subst_scaler(matrix* m, float scaler) {
    for (cml_u32 r = 0; r < m->rows; r++) {
        for (cml_u32 c = 0; c < m->cols; c++) {
            m->values[r][c] -= scaler;
        }
    }
}

matrix cml_matrix_scaler_mult(matrix m, float scaler) {
    matrix ret = cml_matrix_allocate(m.rows, m.cols);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = m.values[r][c] * scaler;
        }
    }
    return ret;
}

void cml_matrix_mult_by_scaler(matrix* m, float scaler) {
    for (cml_u32 r = 0; r < m->rows; r++) {
        for (cml_u32 c = 0; c < m->cols; c++) {
            m->values[r][c] *= scaler;
        }
    }
}

matrix cml_matrix_scaler_div(matrix m, float scaler) {
    matrix ret = cml_matrix_allocate(m.rows, m.cols);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = m.values[r][c] / scaler;
        }
    }
    return ret;
}

void cml_matrix_div_by_scaler(matrix* m, float scaler) {
    for (cml_u32 r = 0; r < m->rows; r++) {
        for (cml_u32 c = 0; c < m->cols; c++) {
            m->values[r][c] /= scaler;
        }
    }
}

matrix cml_mat_mat_addition(matrix m1, matrix m2) {
    assert(!(m1.rows != m2.rows || m1.cols != m2.cols));

    matrix ret = cml_matrix_allocate(m1.rows, m1.cols);

    for (cml_u32 r = 0; r < m1.rows; r++) {
        for (cml_u32 c = 0; c < m1.cols; c++) {
            ret.values[r][c] = m1.values[r][c] + m2.values[r][c];
        }
    }
    return ret;
}

void cml_add_mat_to_mat(matrix* m1, matrix m2) {
    assert(!(m1->rows != m2.rows || m1->cols != m2.cols));

    for (cml_u32 r = 0; r < m1->rows; r++) {
        for (cml_u32 c = 0; c < m1->cols; c++) {
            m1->values[r][c] += m2.values[r][c];
        }
    }
}

matrix cml_mat_mat_subst(matrix m1, matrix m2) {
    assert(!(m1.rows != m2.rows || m1.cols != m2.cols));

    matrix ret = cml_matrix_allocate(m1.rows, m1.cols);

    for (cml_u32 r = 0; r < m1.rows; r++) {
        for (cml_u32 c = 0; c < m1.cols; c++) {
            ret.values[r][c] = m1.values[r][c] - m2.values[r][c];
        }
    }
    return ret;
}

void cml_subst_mat_from_mat(matrix* m1, matrix m2) {
    assert(!(m1->rows != m2.rows || m1->cols != m2.cols));

    for (cml_u32 r = 0; r < m1->rows; r++) {
        for (cml_u32 c = 0; c < m1->cols; c++) {
            m1->values[r][c] -= m2.values[r][c];
        }
    }
}

matrix cml_mat_mat_mult(matrix m1, matrix m2) {
    assert(m1.cols == m2.rows);

    vector* m1_rows = malloc(m1.rows * sizeof(vector));
    vector* m2_cols = malloc(m2.cols * sizeof(vector));

    for (cml_u32 r = 0; r < m1.rows; r++) {
        m1_rows[r] = cml_matrix_get_row(&m1, r + 1);
    }
    for (cml_u32 c = 0; c < m2.cols; c++) {
        m2_cols[c] = cml_matrix_get_col(&m2, c + 1);
    }

    matrix ret = cml_matrix_allocate(m1.rows, m2.cols);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = cml_dot(m1_rows[r], m2_cols[c]);
        }
    }

    for (cml_u32 r = 0; r < m1.rows; r++) {
        cml_vector_free_mem(m1_rows + r);
    }
    for (cml_u32 c = 0; c < m2.cols; c++) {
        cml_vector_free_mem(m2_cols + c);
    }

    free(m1_rows);
    free(m2_cols);

    return ret;
}

vector cml_matrix_vec_mult(matrix m, vector v) {
    assert(m.cols == v.dimension);

    vector ret = cml_vector_allocate(m.rows);

    for (cml_u32 r = 0; r < ret.dimension; r++) {
        ret.values[r] = cml_dot(v, cml_matrix_get_row(&m, r + 1));
    }
    return ret;
}

matrix cml_matrix_transpose(matrix* m) {
    matrix ret = cml_matrix_allocate(m->cols, m->rows);

    for (cml_u32 r = 0; r < ret.rows; r++) {
        for (cml_u32 c = 0; c < ret.cols; c++) {
            ret.values[r][c] = m->values[c][r];
        }
    }
    return ret;
}

void cml_matrix_swap_rows(matrix* m, cml_u32 row_1, cml_u32 row_2) {
    row_1--;
    row_2--;
    assert(!(row_1 >= m->rows || row_2 >= m->rows));

    float* tmp = m->values[row_1];
    m->values[row_1] = m->values[row_2];
    m->values[row_2] = tmp;
}

void cml_matrix_add_rows(matrix* m, cml_u32 row_1, cml_u32 row_2) {
    row_1--;
    row_2--;
    assert(!(row_1 >= m->rows || row_2 >= m->rows || row_1 == row_2));

    for (cml_u32 c = 0; c < m->cols; c++) {
        m->values[row_1][c] += m->values[row_2][c];
    }
}

void cml_matrix_mulitply_row(matrix* m, cml_u32 r, float scaler) {
    r--;

    assert(!(r >= m->rows || scaler == 0.0f));

    for (cml_u32 c = 0; c < m->cols; c++) {
        m->values[r][c] *= scaler;
    }
}

void cml_matrix_add_mulitple_rows(matrix* m, cml_u32 row_1, cml_u32 row_2,
                                  float scaler) {
    row_1--;
    row_2--;

    assert(!(row_1 >= m->rows || row_2 >= m->rows || scaler == 0.0f ||
             row_1 == row_2));

    for (cml_u32 c = 0; c < m->cols; c++) {
        m->values[row_1][c] += scaler * m->values[row_2][c];
    }
}

void cml_matrix_row_echelon_form(matrix* m) {
    cml_u32 crnt_row = 0;
    for (cml_u32 c = 0; c < m->cols; c++) {
        cml_u32 r = crnt_row;
        if (r >= m->rows) {
            break;
        }

        for (; r < m->rows; r++) {
            if (m->values[r][c] != 0.0f) {
                break;
            }
        }
        if (r == m->rows) {
            continue;
        }

        cml_matrix_swap_rows(m, crnt_row + 1, r + 1);

        float factor = 1 / m->values[crnt_row][c];
        for (cml_u32 col = c; col < m->cols; col++) {
            m->values[crnt_row][col] *= factor;
        }

        for (r = crnt_row + 1; r < m->rows; r++) {
            cml_matrix_add_mulitple_rows(m, r + 1, crnt_row + 1,
                                         -1 * m->values[r][c]);
        }

        crnt_row++;
    }
}

void cml_matrix_reduced_row_echelon_form(matrix* m) {
    cml_u32 crnt_row = 0;
    for (cml_u32 c = 0; c < m->cols; c++) {
        cml_u32 r = crnt_row;
        if (r >= m->rows) {
            break;
        }

        for (; r < m->rows; r++) {
            if (m->values[r][c] != 0.0f) {
                break;
            }
        }

        if (r == m->rows) {
            continue;
        }

        cml_matrix_swap_rows(m, crnt_row + 1, r + 1);

        float factor = 1 / m->values[crnt_row][c];
        for (cml_u32 col = c; col < m->cols; col++) {
            m->values[crnt_row][col] *= factor;
        }

        for (r = 0; r < m->rows; r++) {
            if (r == crnt_row) {
                continue;
            }
            cml_matrix_add_mulitple_rows(m, r + 1, crnt_row + 1,
                                         -1 * m->values[r][c]);
        }

        crnt_row++;
    }
}

matrix cml_augment_vector(matrix* m, vector* v) {
    assert(m->rows == v->dimension);

    matrix ret = cml_matrix_allocate(m->rows, m->cols + 1);

    for (cml_u32 r = 0; r < m->rows; r++) {
        cml_u32 c = 0;
        for (; c < m->cols; c++) {
            ret.values[r][c] = m->values[r][c];
        }

        // put vector values at end
        ret.values[r][c] = v->values[r];
    }

    return ret;
}

matrix cml_augment_matrix(matrix* m1, matrix* m2) {
    assert(m1->rows == m2->rows);

    matrix ret = cml_matrix_allocate(m1->rows, m1->cols + m2->cols);

    for (cml_u32 r = 0; r < m1->rows; r++) {
        cml_u32 c = 0;
        for (; c < m1->cols; c++) {
            ret.values[r][c] = m1->values[r][c];
        }
        for (; c < ret.cols; c++) {
            ret.values[r][c] = m2->values[r][c - m1->cols];
        }
    }

    return ret;
}

matrix cml_matrix_splice(matrix* m, cml_u32 ex_row, cml_u32 ex_col) {
    ex_row--;
    ex_col--;

    matrix ret = cml_matrix_allocate(m->rows - 1, m->cols - 1);

    unsigned int row_offset = 0;
    for (unsigned int r = 0; r < ret.rows; r++) {
        unsigned int colOffset = 0;

        if (r == ex_row) {
            row_offset++;
        }

        for (unsigned int c = 0; c < ret.cols; c++) {
            if (c == ex_col) {
                colOffset++;
            }

            ret.values[r][c] = m->values[r + row_offset][c + colOffset];
        }
    }

    return ret;
}

void cml_matrix_set_col(matrix* m, cml_u32 col, vector v) {
    col--;
    assert(col >= 0 && col < m->cols && v.dimension == m->rows);

    for (cml_u32 r = 0; r < m->rows; r++) {
        m->values[r][col] = v.values[r];
    }
}

void cml_matrix_set_row(matrix* m, cml_u32 row, vector v) {
    row--;
    assert(row >= 0 && row < m->rows && v.dimension == m->rows);

    for (cml_u32 c = 0; c < m->cols; c++) {
        m->values[row][c] = v.values[c];
    }
}