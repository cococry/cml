# CML - C Math Library
<image src="git-assets/logo.png" alt="logo" width=515px></image>

## Overview
CML ( C Math Library ) is a linear algebra library for c and developed mainly for graphics development. 
The main purpose of the creation of CML was to improve on [cglm](https://github.com/recp/cglm) in the way i needed it. 
Of cglm is a very good library in a lot of ways and they have my full respect. 
CML is a lightweight, easy to use and to compile library. The library only constists of .c and .h files which makes compilation a lot easier. 
The library does not build a lib or a dll file and runns on any C compiler (gcc, clang, mingw etc.). 

***

## 🛬 Building

To correctly build the library, just compile all .c files in the repository (folder [cml](https://github.com/cococry/cml/tree/main/cml)). And of course, include
all the .h files in order to use the library. 

That's it! 

##💥Features

- Full vector support (operations, scalers, cross, dot, normalize etc.)
- Full matrices support (operations, scalers, identity, transpose, etc.)
- Radians implementation
- Matrix transformations (translate, rotate, scale)
- Camera function (look_at)
- Projections perspective, ortho ect.)
- Accessing matrcies by rows and columns
- Row echelon form & Reduces row echelon form (matrices)

As you can see, features like quanternions and euler angles are not featured in this list. This is because the library is still a 
work in progress and its being improved on.

## Notes

This library is not a highly optimised bleeding edge library like glm or something. I am developing this library mostly for personal use and did not try to
replace any other library on the market. The main reason for the library is, that C does not have a lot of linear algebra libraries with whom i can work
unhindered.

## Brief documentation

- **Vectors**

In CML, vectors are defined by a dimension and a array of values. There is no such thing as vec2, vec3, vec4 like in other libraries like glm.
Vectors can have any dimension, in CML. The values of the vector are assigned with variadic arguments in a macro function. The dimension is being
calculated internally by another macro "NUM_OF_ARGS". 

**WARNING**:
All values of the vector that is being intialized have to be float values. Internally, the macro function does only accept float values. This
has to be statet explicitly (4 is not valid, 4.0f is valid).

```C
 vector v = cml_vector(4.0f, -2.0f, 1.0f);
 cml_vec_mult_with_vec(&v, cml_vector(2.0f, 10.0f, 10.0f);
 
 cml_vector_print(v);
```

Functions return vectors that can be assigned:

```C
  vector v1 = cml_vector(2.0f, 3.0f, 4.0f);
  
  vector v2 = cml_vector_normalized(cml_vector_scaler_addition(v1, 4.0f));
  
  v2 = cml_cross(v1, cml_vector(10.0f, 20.0f, 30.0f);
```

Other functions access and modify the vector itself:

```C
  vector v1 = cml_vector(2.0f, 3.0f, 4.0f);
  cml_vector_print(v1);
  
  cml_vector_normalize(&v1);
  cml_vector_print(v1);
```

- **Matrices**

Matrices are defined by a number of columns, a number of rows and their values. Again, their is no such thing like mat3 or mat4, instead the dimension
(rows and columns) are specified at creation.

Assigning the values of the matrix yourself:

```C
  matrix m = cml_matrix(2, 2, 
                        5.0f, 10.0f,
                        7.0f, 3.0f);
                        
  cml_matrix_print(m);
```

Or the common way, letting the library create the matrices:

```C
  matrix m = cml_identity(4);
  
  matrix m2 = cml_translate(m, cml_vector(2.0f, 3.0f, 5.0f));
  
  cml_matrix_print(m);
```

- **Projections and camera**

Dealing with projection, view and model matrix is a very importent task when working with computer graphics. Translation, rotation projection etc. is internally
and API-wise handled pretty much the same way as its handled by [glm](https://github.com/g-truc/glm).

```C
  matrix m = cml_mat_mat_mult(
                          cml_translate(cml_matrix_identity(4), cml_vector(1.0f, 2.0f, 3.0f)), 
                          cml_rotate(cml_matrix_identity(4), cml_radians(45.0f), cml_vector(0.0f, 0.0f, 1.0f)));
  
  matrix m2 = cml_scale(cml_matrix_identity(4), cml_vector(0.0f, 2.0f, 0.0f));
  
  matrix m2 = cml_perspective(cml_radians(45.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
  
  matrix m3 = cml_ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
```

***
