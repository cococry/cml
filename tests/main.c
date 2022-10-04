#include "../cml/cml.h"

int main() {
    matrix m = cml_mat_mat_mult(
        cml_translate(cml_matrix_identity(4), cml_vector(1.0f, 2.0f, 3.0f)),
        cml_rotate(cml_matrix_identity(4), cml_radians(45.0f),
                   cml_vector(0.0f, 0.0f, 1.0f)));

    matrix m2 =
        cml_perspective(cml_radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
    return 0;
}