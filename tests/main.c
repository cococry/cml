#include "../cml/cml.h"

int main() {
    matrix m = cml_ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
    cml_matrix_print(m);

    return 0;
}
