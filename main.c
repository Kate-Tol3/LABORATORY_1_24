#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "matrix.h"
#include "test.h"


void matrix_filling(Matrix *matrix){
    int fill;
    printf("\nHow do you want to fill the matrix?\n");
    printf("1: with zeros\n2: from input\n");//3: random numbers\n");
    printf("the action is: ");
    scanf("%d", &fill);
    switch (fill){
        case 1:
            fill_zeros_matrix(matrix);
            break;
        case 2:
            read_matrix(matrix);
            break;
            // case 3:
                //     fill_random_matrix(matrix1);
                //     break;   
        default:
            printf("\nno such action! try again...\n");
            break;
                
    }
    printf("\nmatrix is:\n");
            print_matrix(matrix);   
}

void menu (){
    size_t v, h;
    int action, flag = 1, type;
    FieldInfo* info;
    Matrix *matrix1, *matrix2, *matrix3, *matrix;
    printf("Hello! This programm allows you to operate matrixes\n");
    while(flag){
        printf("\nSelect the action:\n1: Summarise two matrixes\n2: Multiply two matrixes\n3: Multiply matrix on number\n4: Transpose matrix\n5: stop\n");
        printf("\nyour action is: ");
        scanf("%d", &action);
        switch (action){
                case 1: // sum
                    printf("Choose the type of matrix:\n1: int\n2: real\n3:complex\n\n");
                    printf("matrix type is:\n");
                    scanf("%d", &type);
                    printf("vertical size:\n");
                    scanf("%zu", &v);
                    printf("horizontal size:\n");
                    scanf("%zu", &h);
                    switch(type){
                        case 1:
                            info = get_info_int();
                            break;
                        case 2:
                            info = get_info_real();
                            break;
                        case 3:
                            info = get_info_complex();
                            break;
                        default:
                            printf("\nno such type! try again...\n");
                            break;
                    }
                    matrix1 = new_matrix(v, h, info);
                    matrix2 = new_matrix(v, h, info);
                    matrix3 = new_matrix(v, h, info);
                    printf("FILLING THE 1st MATRIX:");
                    matrix_filling(matrix1);
                    printf("FILLING THE 2nd MATRIX:");
                    matrix_filling(matrix2);
                    sum_matrix(matrix1, matrix2, matrix3);
                    if (matrix3->elements != NULL){
                        printf("\nAfter summarising the final result is:\n");
                        print_matrix(matrix3); 
                    }
                    break;
                case 2: // mult
                    size_t v1, h1, v2, h2;
                    printf("Choose the type of matrix:\n1: int\n2: real\n3:complex\n\n");
                    printf("matrix type is:\n");
                    scanf("%d", &type);
                    printf("vertical size 1st matrix:\n");
                    scanf("%zu", &v1);
                    printf("horizontal size 1st matrix:\n");
                    scanf("%zu", &h1);
                    printf("vertical size 2nd matrix:\n");
                    scanf("%zu", &v2);
                    printf("horizontal size 2nd matrix:\n");
                    scanf("%zu", &h2);
                    switch(type){
                        case 1:
                            info = get_info_int();
                            break;
                        case 2:
                            info = get_info_real();
                            break;
                        case 3:
                            info = get_info_complex();
                            break;
                        default:
                            printf("\nno such type! try again...\n");
                            break;
                    }
                    matrix1 = new_matrix(v1, h1, info);
                    matrix2 = new_matrix(v2, h2, info);
                    matrix3 = new_matrix(v1, h2, info);
                    printf("FILLING THE 1st MATRIX:");
                    matrix_filling(matrix1);
                    printf("FILLING THE 2nd MATRIX:");
                    matrix_filling(matrix2);
                    mult_matrix(matrix1, matrix2, matrix3);
                    if (matrix3->elements != NULL){
                        printf("\nAfter multiplying the final result is:\n");
                        print_matrix(matrix3); 
                    }
                    break;
                case 3: // mult on number
                    printf("Choose the type of matrix:\n1: int\n2: real\n3:complex\n\n");
                    printf("matrix type is:\n");
                    scanf("%d", &type);
                    printf("vertical size matrix:\n");
                    scanf("%zu", &v);
                    printf("horizontal size matrix:\n");
                    scanf("%zu", &h);
                    switch(type){
                        case 1:
                            info = get_info_int();
                            break;
                        case 2:
                            info = get_info_real();
                            break;
                        case 3:
                            info = get_info_complex();
                            break;
                        default:
                            printf("\nno such type! try again...\n");
                            break;
                    }
                    matrix = new_matrix(v, h, info);
                    printf("FILLING THE MATRIX:");
                    matrix_filling(matrix);

                    void* number = malloc (matrix->typeInfo->el_size);
                    printf("Write your number(must be the same type as matrix): ");
                    matrix->typeInfo->get_number(number);
                    mult_on_number_matrix(matrix, number);
                    printf("\nAfter multiplying the final result is:\n");
                    print_matrix(matrix); 
                    break;
                case 4://transpose
                    printf("Choose the type of matrix:\n1: int\n2: real\n3:complex\n\n");
                    printf("matrix type is:\n");
                    scanf("%d", &type);
                    printf("vertical size:\n");
                    scanf("%zu", &v);
                    printf("horizontal size:\n");
                    scanf("%zu", &h);
                    switch(type){
                        case 1:
                            info = get_info_int();
                            break;
                        case 2:
                            info = get_info_real();
                            break;
                        case 3:
                            info = get_info_complex();
                            break;
                        default:
                            printf("\nno such type! try again...\n");
                            break;
                    }
                    matrix1 = new_matrix(v, h, info);
                    matrix2 = new_matrix(h, v, info);
                    printf("FILLING THE MATRIX:");
                    matrix_filling(matrix1);
                    transpose_matrix(matrix1, matrix2);
                    printf("\nAfter transposing the final result is:\n");
                    print_matrix(matrix2); 
                    break;
                case 5:
                    flag = 0;
                    break;
                default:
                    printf("\nno such action! try again...\n");
                    break;
            }
            

        
    }
    
    free(matrix->elements);
    free(matrix1->elements);
    free(matrix2->elements);
    free(matrix3->elements);
    free(matrix);
    free(matrix1);
    free(matrix2);
    free(matrix3);
}

int main(){
    test_int_functions();
    test_real_functions();
    test_complex_functions();
    
    test_sum_matrix();
    test_mult_matrix();
    test_mult_on_number_matrix();
}