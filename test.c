#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "Complex.h"
#include "matrix.h"
#include "types_func.h"

#define FLT_EPSILON 1.19209e-07

// TESTING TYPES

void test_int_sum() {
    int v1 = 15;
    int v2 = -200;
    int expected_result = v1 + v2;

    int* v1_ptr = &v1;
    int* v2_ptr = &v2;
    void* result = malloc(sizeof(int));

    int_sum((const void*) v1_ptr, (const void*) v2_ptr, result);
    
    assert(*(int*)result ==  expected_result);
    //printf("The function \"int_sum\" passed the test\n");
    free(result);
}

void test_int_mult() {
    int v1 = 400;
    int v2 = -6;
    int expected_result = v1 * v2;

    int* v1_ptr = &v1;
    int* v2_ptr = &v2;
    void* result = malloc(sizeof(int));

    int_mult((const void*) v1_ptr, (const void*) v2_ptr, result);
    
    assert(*(int*)result ==  expected_result);
    //printf("The function \"mult_sum\" passed the test\n");
    free(result);
}

void test_real_sum() {
    double v1 = 7.6;
    double v2 = -100.4;
    double expected_result = v1 + v2;

    double* v1_ptr = &v1;
    double* v2_ptr = &v2;
    double dval;
    void* result = malloc(sizeof(double));

    real_sum((const void*) v1_ptr, (const void*) v2_ptr, result);

    dval = *(double*)result -  expected_result;
    assert(dval < FLT_EPSILON);
 //   printf("The function \"real_sum\" passed the test\n");
    free(result);
}

void test_real_mult() {
    double v1 = 50.0;
    double v2 = -80.5;
    double expected_result = v1 * v2;

    double* v1_ptr = &v1;
    double* v2_ptr = &v2;
    void* result = malloc(sizeof(double));
    double dval;

    real_mult((const void*) v1_ptr, (const void*) v2_ptr, result);
    dval = *(double*)result -  expected_result;
    assert(dval < FLT_EPSILON);
   // printf("The function \"real_mult\" passed the test\n");
    free(result);
}

void test_complex_sum() {
    Complex v1 = {-1000.4628, 568.2478};
    Complex v2 = {329.47843, -2164.0475};
    Complex expected_result = {v1.re + v2.re, v1.img + v2.img};

    Complex* v1_ptr = &v1;
    Complex* v2_ptr = &v2;
    void* result = malloc(sizeof(Complex));

    complex_sum((const void*) v1_ptr, (const void*) v2_ptr, result);
    
    assert(((Complex*)result)->re == expected_result.re && ((Complex*)result)->img == expected_result.img);
    //printf("The function \"complex_sum\" passed the test\n");
    free(result);
}

void test_complex_mult() {
    Complex v1 = {-10.9325, 462.3628};
    Complex v2 = {-21.506, 342.0986};
    Complex expected_result = {v1.re * v2.re - v1.img * v2.img, v1.re * v2.img + v1.img * v2.re};

    Complex* v1_ptr = &v1;
    Complex* v2_ptr = &v2;
    void* result = malloc(sizeof(Complex));

    complex_mult((const void*) v1_ptr, (const void*) v2_ptr, result);
    assert(((Complex*)result)->re == expected_result.re && ((Complex*)result)->img == expected_result.img);
   // printf("The function \"complex_mult\" passed the test\n");
    free(result);
}

void test_int_functions(){
    test_int_sum();
    test_int_mult();
}

void test_real_functions(){
    test_real_sum();
    test_real_mult();
}

void test_complex_functions(){
    test_complex_sum();
    test_complex_mult();
}


/// Testing matrix functions

void test_sum_matrix_int(){
    //int
    FieldInfo* info = get_info_int();
    Matrix* mat1 = new_matrix(2, 2, info);
    Matrix* mat2 = new_matrix(2, 2, info);
    int elems1[2][2] = {{1, 2}, {3, 4}};
    int elems2[2][2] = {{-1, -2}, {-3, -4}};
    int expected_result[2][2] = {{0, 0}, {0, 0}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    sum_matrix((const Matrix*) mat1,(const Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(int));
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            assert(*(int*)val == expected_result[i][j]);
        }
    }
    free(val);
    
  //  printf("The function \"sum_matrix_int\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}

void test_sum_matrix_real(){
    //real
    FieldInfo* info = get_info_real();
    Matrix* mat1 = new_matrix(2, 2, info);
    Matrix* mat2 = new_matrix(2, 2, info);
    double elems1[2][2] = {{1.0, 2.7}, {3.4, 4.8}};
    double elems2[2][2] = {{-1.0, -2.7}, {-3.4, -4.8}};
    double expected_result[2][2] = {{0.0, 0.0}, {0.0, 0.0}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    sum_matrix((const Matrix*) mat1,(const Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(double));
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            assert(*(double*)val == expected_result[i][j]);
        }
    }
    free(val);
    
  //  printf("The function \"sum_matrix_real\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}

void test_sum_matrix_complex(){
    //complex
    FieldInfo* info = get_info_complex();
    Matrix* mat1 = new_matrix(2, 2, info);
    Matrix* mat2 = new_matrix(2, 2, info);

    Complex x1 = {1.1, 2.2}, x2 = {3.3, 4.4}, x3 = {1.2, 4.5}, x4 = {5.6, 6.5};
    Complex y1 = {-1.1, 0.0}, y2 = {-3.2, 2.2}, y3 = {2.3, -6.0}, y4 = {-4.5, -7.8};
    Complex z1 = {0.0, 2.2}, z2 = {0.1, 6.6}, z3 = {3.5, -1.5}, z4 = {1.1, -1.3};
    Complex elems1[2][2] = {{x1, x2}, {x3, x4}};
    Complex elems2[2][2] = {{y1, y2}, {y3, y4}};
    Complex expected_result[2][2] = {{z1, z2}, {z3, z4}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    sum_matrix((const Matrix*) mat1,(const Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(Complex));
    double dval;
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            dval = fabs((((Complex*)val)->re) - (expected_result[i][j].re));
            assert(dval < FLT_EPSILON);
            dval = fabs((((Complex*)val)->img) - (expected_result[i][j].img));
            assert(dval < FLT_EPSILON);
        }
    }
    free(val);
    
   // printf("The function \"sum_matrix_complex\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}


void test_mult_matrix_int(){
    //int
    FieldInfo* info = get_info_int();
    Matrix* mat1 = new_matrix(2, 2, info);
    Matrix* mat2 = new_matrix(2, 2, info);
    int elems1[2][2] = {{1, 2}, {3, 4}};
    int elems2[2][2] = {{-1, -2}, {-3, -4}};
    int expected_result[2][2] = {{-7, -10}, {-15, -22}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    mult_matrix((Matrix*) mat1,(Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(int));
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            assert(*(int*)val == expected_result[i][j]);
        }
    }
    free(val);
    
   // printf("The function \"mult_matrix_int\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}

void test_mult_matrix_real(){
    //real
    FieldInfo* info = get_info_real();
    Matrix* mat1 = new_matrix(2, 1, info);
    Matrix* mat2 = new_matrix(1, 2, info);
    double elems1[1][2] = {1.3, 4.6};
    double elems2[2][1] = {7.4, -8.9};
    double expected_result[2][2] = {{9.62, -11.57}, {34.04, -40.94}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    mult_matrix((Matrix*) mat1,(Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(double));
    double dval;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            dval = fabs(*((double*)val) - expected_result[i][j]);
            assert(dval < FLT_EPSILON);
            dval = fabs(*((double*)val) - expected_result[i][j]);
            assert(dval < FLT_EPSILON);
        }
    }
    free(val);
    
  //  printf("The function \"mult_matrix_real\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}

void test_mult_matrix_complex(){
    //complex
    FieldInfo* info = get_info_int();
    Matrix* mat1 = new_matrix(2, 2, info);
    Matrix* mat2 = new_matrix(2, 2, info);
    int elems1[2][2] = {{1, 2}, {3, 4}};
    int elems2[2][2] = {{-1, -2}, {-3, -4}};
    int expected_result[2][2] = {{-7, -10}, {-15, -22}};
    mat1->elements = elems1;
    mat2->elements = elems2;

    Matrix* result = new_matrix(2, 2, info);
    mult_matrix((Matrix*) mat1,(Matrix*) mat2,(Matrix*) result);
    void* val = malloc (sizeof(int));
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            assert(*(int*)val == expected_result[i][j]);
        }
    }
    free(val);
    
   // printf("The function \"mult_matrix_complex\" passed the test\n");
    free(mat1);
    free(mat2);
    free(result);
}


void test_mult_on_number_matrix_int(){
    //int
    FieldInfo* info = get_info_int();
    Matrix* result = new_matrix(2, 2, info);
    int elems[2][2] = {{1, 2}, {3, 4}};
    int number = 5;
    int expected_result[2][2] = {{5, 10}, {15, 20}};

    result->elements = elems; 

    mult_on_number_matrix((Matrix*) result, (void*) &number);
    void* val = malloc (sizeof(int));
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            assert(*(int*)val == expected_result[i][j]);
        }
    }
    free(val);
    
   // printf("The function \"mult_on_number_matrix_int\" passed the test\n");
    free(result);
}

void test_mult_on_number_matrix_real(){
    //real
    FieldInfo* info = get_info_real();
    Matrix* result = new_matrix(2, 2, info);
    double elems[2][2] = {{4673.827, 95.34286}, {281.32486, 59.32896}};
    double number = 8.2;
    double expected_result[2][2] = {{38352.3814, 781.811452}, {2306.863852, 486.497472}};

    result->elements = elems; 

    mult_on_number_matrix((Matrix*) result, (void*) &number);
    void* val = malloc (sizeof(double));
    double dval;
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            dval = *(double*)val - expected_result[i][j];
            assert(dval<FLT_EPSILON);
        }
    }
    free(val);
    
    //printf("The function \"mult_on_number_matrix_real\" passed the test\n");
    free(result);
}

void test_mult_on_number_matrix_complex(){
    FieldInfo* info = get_info_complex();
    Matrix* result = new_matrix(2, 2, info);
    Complex x1 = {4.5, 3.4}, x2 = {2.0, 7.7}, x3 = {9.12, 56.48}, x4 = {3.1, 22.0};
    Complex number = {7.3, 2.3};
    Complex z1 = {25.03, 35.17}, z2 = {-3.11,  60.81}, z3 = {-63.328, 433.28}, z4 = {-27.97, 167.73};

    Complex elems[2][2] = {{x1, x2}, {x3, x4}};
    Complex expected_result[2][2] = {{z1, z2}, {z3, z4}};

    result->elements = elems; 

    mult_on_number_matrix((Matrix*) result, (void*) &number);
    void* val = malloc (sizeof(Complex));
    double dval;
    for (int i = 0; i< 2; i++){
        for (int j = 0; j < 2 ; j++){
            get_element(result, i, j, val);
            dval = ((Complex*)val)->re - expected_result[i][j].re;
            assert(dval<FLT_EPSILON);
            dval = ((Complex*)val)->img - expected_result[i][j].img;
            assert(dval<FLT_EPSILON);
        }
    }
    free(val);
    
   // printf("The function \"mult_on_number_matrix_complex\" passed the test\n");
    free(result);
}


void test_transpose_matrix_int(){
    //int
    FieldInfo* info = get_info_int();
    Matrix* matrix = new_matrix(3, 2, info);
    Matrix* result = new_matrix(2, 3, info);
    int elems[3][2] = {{34, 67}, {12, 80}, {45, 23}};
    int expected_result[2][3] = {{34, 12, 45}, {67, 80, 23}};

    matrix->elements = elems; 

    transpose_matrix((Matrix*) matrix, (Matrix*) result);
    void* val = malloc (sizeof(int));
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3 ; j++){
            get_element(result, i, j, val);
            assert(*(int*)val == expected_result[i][j]);
        }
    }
    free(val);
    
   // printf("The function \"transpose_matrix_int\" passed the test\n");
    free(matrix);
    free(result);
}

void test_transpose_matrix_real(){
    //real
    FieldInfo* info = get_info_real();
    Matrix* matrix = new_matrix(3, 2, info);
    Matrix* result = new_matrix(2, 3, info);
    double elems[3][2] = {{45.6, 23.1}, {9.0123, 75.05}, {10.1, 2.0927}};
    double expected_result[2][3] = {{45.6, 9.0123, 10.1}, {23.1,75.05, 2.0927}};

    matrix->elements = elems; 

    transpose_matrix((Matrix*) matrix, (Matrix*) result);
    void* val = malloc (sizeof(double));
    double dval;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3 ; j++){
            get_element(result, i, j, val);
            dval = *(double*)val - expected_result[i][j];
            assert(dval < FLT_EPSILON);
        }
    }
    free(val);
    
   // printf("The function \"transpose_matrix_real\" passed the test\n");
    free(matrix);
    free(result);
}

void test_transpose_matrix_complex(){
    //complex
    FieldInfo* info = get_info_complex();
    Matrix* matrix = new_matrix(3, 2, info);
    Matrix* result = new_matrix(2, 3, info);

    Complex x1 = {4.5, 3.4}, x2 = {-2.0, 7.7}, x3 = {9.12, 56.48}, x4 = {-3.1, 22.0}, x5 = {-341.2, 34.0}, x6 = {91.012, 23.33};
    Complex z1 = {4.5, 3.4}, z2 = {9.12,  56.48}, z3 = {-341.2, 34.0}, z4 = {-2.0, 7.7}, z5 = {-3.1, 22.0}, z6 = {91.012, 23.33};

    Complex elems[3][2] = {{x1, x2}, {x3, x4}, {x5, x6}};
    Complex expected_result[2][3] = {{z1, z2, z3}, {z4, z5, z6}};

    matrix->elements = elems; 

    transpose_matrix((Matrix*) matrix, (Matrix*) result);
    void* val = malloc (sizeof(Complex));
    double dval;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3 ; j++){
            get_element(result, i, j, val);
            dval = ((Complex*)val)->re - expected_result[i][j].re;
            assert(dval < FLT_EPSILON);
            dval = ((Complex*)val)->img - expected_result[i][j].img;
            assert(dval < FLT_EPSILON);
        }
    }
    free(val);
    
   // printf("The function \"transpose_matrix_complex\" passed the test\n");
    free(matrix);
    free(result);
}


void test_sum_matrix(){
    test_sum_matrix_int();
    test_sum_matrix_real();
    test_sum_matrix_complex();
}

void test_mult_matrix(){
    test_mult_matrix_int();
    test_mult_matrix_real();
    test_mult_matrix_complex();

}

void test_mult_on_number_matrix(){
    test_mult_on_number_matrix_int();
    test_mult_on_number_matrix_real();
    test_mult_on_number_matrix_complex();
}

void test_transpose_matrix(){
    test_transpose_matrix_int();
    test_transpose_matrix_real();
    test_transpose_matrix_complex();
}
