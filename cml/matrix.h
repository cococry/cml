#ifndef CML_MATRIX_INCLUDED
#define CML_MATRIX_INCLUDED

#include <stdarg.h>
#include <stdio.h>

#include "internal/cml_core.h"
#include "vector.h"

/*
    Defines the structe of a matrix.
    (rows, columns and values)
*/
typedef struct {
    cml_u32 rows, cols;
    float** values;
} matrix;

/*
    Allocates a empty matrix with space to
    hold rows * cols values and returns it.
*/
matrix cml_matrix_allocate(cml_u32 rows, cml_u32 cols);

/*
    Returns an identity matrix with a given
    dimension.
*/
matrix cml_matrix_identity(cml_u32 dimension);

/*
    Returns a empty matrix (all zeros) with
    a size of given parameters rows * cols.
*/
matrix cml_matrix_empty(cml_u32 rows, cml_u32 cols);

/*
    NOTE: Use cml_matrix() macro in client code istead
          of this function. This function is internal.

    Constructs a matrix with size of given parameters
    rows * cols. The given values (variadic arguments)
    are then stored in order in the matrix. This matrix
    will be returned.
*/
matrix cml_matrix_construct(cml_u32 rows, cml_u32 cols, cml_u32 num_values, ...);

/*
    Copies a given matrix "m" and returns it.
*/
matrix cml_matrix_copy_mem(matrix* m);

/*
    Prints all values of a given matrix "m" to the
    console in a specific layout.
    LAYOUT:
    | 1 0 0|
    | 0 1 0|
    | 0 0 1|
*/
void cml_matrix_print(matrix m);

/*
    Returns if the given matrices m1 and m2 are equal.
*/
BOOL cml_matrix_compare(matrix m1, matrix m2);

/*
    Returns the row from a given matrix "m" at a
    given index "row".
*/
vector cml_matrix_get_row(matrix* m, cml_u32 row);

/*
    Returns the colomn from a given matrix "m" at a
    given index "col".
*/
vector cml_matrix_get_col(matrix* m, cml_u32 col);

/*
    Returns a matrix with one row whose values are
    assigned to the values of the given vector "v".
*/
matrix cml_matrix_to_row_vec(vector* v);

/*
    Returns a matrix with one column whose values are
    assigned to the values of the given vector "v".
*/
matrix cml_matrix_to_col_vec(vector* v);

void cml_matrix_set_col(matrix* m, cml_u32 col, vector v);

void cml_matrix_set_row(matrix* m, cml_u32 row, vector v);

/*
    Adds the given scaler to every value of a matrix that
    corresponds to the given matrix "m" and returns the
    resulting matrix.
*/
matrix cml_matrix_scaler_addition(matrix m, float scaler);

/*
    Adds a given scaler to all values of a given matrix "m".
*/
void cml_matrix_add_scaler(matrix* m, float scaler);

/*
    Substracts the given scaler from every value of a matrix that
    corresponds to the given matrix "m" and returns the
    resulting matrix.
*/
matrix cml_matrix_scaler_subst(matrix m, float scaler);

/*
    Substracts a given scaler from all values of a given matrix "m".
*/
void cml_matrix_subst_scaler(matrix* m, float scaler);

/*
    Multiplies every value of a matrix that
    corresponds to the given matrix "m" with the
    given scaler and returns the resulting matrix.
*/
matrix cml_matrix_scaler_mult(matrix m, float scaler);

/*
    Multiplies all values of a given matrix "m" with the given scaler.
*/
void cml_matrix_mult_by_scaler(matrix* m, float scaler);

/*
    Divides every value of a matrix that
    corresponds to the given matrix "m" by the
    given scaler and returns the resulting matrix.
*/
matrix cml_matrix_scaler_div(matrix m, float scaler);

/*
    Divides all values of a given matrix "m" by the given scaler.
*/
void cml_matrix_div_by_scaler(matrix* m, float scaler);

/*
    NOTE: Dimension (rows, cols) of matrix m1 and m2
    have to be the same in order to run this function.

    Returns the matrix that is the result of adding
    the given matrices m1 and m2.
*/
matrix cml_mat_mat_addition(matrix m1, matrix m2);

/*
    NOTE: Dimension (rows, cols) of matrix m1 and m2
    have to be the same in order to run this function.

    Adds a given matrix m2 to the given matrix m1.
*/
void cml_add_mat_to_mat(matrix* m1, matrix m2);

/*
    NOTE: Dimension (rows, cols) of matrix m1 and m2
    have to be the same in order to run this function.

    Returns the matrix that is the result of substracting
    the given matrix m2 from the given matrix m1.
*/
matrix cml_mat_mat_subst(matrix m1, matrix m2);

/*
    NOTE: Dimension (rows, cols) of matrix m1 and m2
    have to be the same in order to run this function.

    Substracts a given matrix m2 from the given matrix m1.
*/
void cml_subst_mat_from_mat(matrix* m1, matrix m2);

/*
    NOTE: Dimension (rows, cols) of matrix m1 and m2
    have to be the same in order to run this function.

    Returns the matrix that is the result of multiplying
    the given matrices m1 and m2.
*/
matrix cml_mat_mat_mult(matrix m1, matrix m2);

/*
    Multiplies all values of a given matrix m1 with all
    values of a given matrix m2.
*/

/*
    Multiplies a given vector "v" with a given matrix "m" and returns
    the result.
*/
vector cml_matrix_vec_mult(matrix m, vector v);

/*
    Returns the transpose of the given matrix "m".
*/
matrix cml_matrix_transpose(matrix* m);

/*
    Swaps the two given rows "row_1" and "row_2" in the given
    matrix "m".
*/
void cml_matrix_swap_rows(matrix* m, cml_u32 row_1, cml_u32 row_2);

/*
    Adds all values of the the given row "row_2" of the given
    matrix "m" to the given row "row_1" of the same matrix.
*/
void cml_matrix_add_rows(matrix* m, cml_u32 row_1, cml_u32 row_2);

/*
    Multiplies a given row "r" of a given matrix "m" by
    a given scaler.
*/
void cml_matrix_mulitply_row(matrix* m, cml_u32 r, float scaler);

/*
    Adds the given row "row_2" of a given matrix "m" multiplied
    with the given scaler to the given row "row_1".
*/
void cml_matrix_add_mulitple_rows(matrix* m, cml_u32 row_1, cml_u32 row_2,
                                  float scaler);

/*
    Turns a given matrix "m" into row echelon form.
*/
void cml_matrix_row_echelon_form(matrix* m);

/*
    Turns a given matrix "m" into reduced row echolon
    form.
*/
void cml_matrix_reduced_row_echelon_form(matrix* m);

/*
    Augments a given vector "v" to the end of
    a given matrix "m" and returns the resulting
    matrix.
*/
matrix cml_augment_vector(matrix* m, vector* v);

/*
    Augments a given matrix "m1" to the end of
    a given matrix "m2" and returns the resulting
    matrix.
*/
matrix cml_augment_matrix(matrix* m1, matrix* m2);

/*
    Returns a matrix that is a copy of the given
    matrix "m" with the given column "ex_col" and
    the given row "ex_row" excluded.
*/
matrix cml_matrix_splice(matrix* m, cml_u32 ex_row, cml_u32 ex_col);

#define cml_matrix(rows, cols, ...)                                   \
    cml_matrix_construct(rows, cols, NUM_OF_ARGS(float, __VA_ARGS__), \
                         ##__VA_ARGS__)

#endif