
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Complex.h"
#include "matrix.h"
#include "types_func.h"

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
    printf("The function \"int_sum\" passed the test\n");
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
    printf("The function \"mult_sum\" passed the test\n");
    free(result);
}

void test_real_sum() {
    int v1 = 7.6;
    int v2 = -100.4;
    int expected_result = v1 + v2;

    int* v1_ptr = &v1;
    int* v2_ptr = &v2;
    void* result = malloc(sizeof(double));

    int_sum((const void*) v1_ptr, (const void*) v2_ptr, result);
    
    assert(*(int*)result ==  expected_result);
    printf("The function \"real_sum\" passed the test\n");
    free(result);
}

void test_real_mult() {
    double v1 = 50.0;
    double v2 = -80.5;
    double expected_result = v1 * v2;

    double* v1_ptr = &v1;
    double* v2_ptr = &v2;
    void* result = malloc(sizeof(double));

    real_mult((const void*) v1_ptr, (const void*) v2_ptr, result);
    
    assert(*(double*)result ==  expected_result);
    printf("The function \"real_mult\" passed the test\n");
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
    printf("The function \"complex_sum\" passed the test\n");
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
    //printf("The function \"complex_mult\" passed the test\n");
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


// TESTING MATRIX FUNCTIONS

typedef struct Node* NodePtr;

typedef struct{
    char* lexem;
    Node* leftNode;
    Node* rightNode;
} Node;

//Node functions

Node* newNode(void){
    void* p = malloc(sizeof(Node));
    assert(p != NULL);
    return (Node*) p;
}

Node* NodeCopy(const Node* source){
    Node* res = newNode();
    assert(res != NULL);
    memcopy(source, res, sizeof(Node));
    return res;
}

void operation(const char* lexem, const void* leftNode, const void* rightNode, void* result) {
    ((Node*)result) -> lexem = lexem;
    ((Node*)((Node*)result))-> leftNode = NodeCopy((Node*)leftNode);
    ((Node*)((Node*)result))-> rightNode = NodeCopy((Node*)rightNode);
}

// Node operation lexem conctructor

void sum_node(const void* leftNode, const void* rightNode, void* result) {
    operation("+", leftNode, rightNode, result);
}

void mult_node(const void* leftNode, const void* rightNode, void* result) {
    operation("*", leftNode, rightNode, result);
}



static const FieldInfo NODE_FIELD_INFO = {&sum_node, &mult_node, NULL, NULL, NULL, NULL};

void printToBuff(char **buff, const char separator, int *remainingSize, Node* node) {
    assert(node);
    assert(node -> lexem);

    int step = 1 + strlen(node -> lexem);
	assert((*remainingSize) > 1 + step);
    **buff = separator;
    strcpy((*buff) + 1, node -> lexem);
    *buff += step;
    *remainingSize -= step;

    if (node -> leftNode != NULL) {
        printToBuff(buff, ',', remainingSize, (NodePtr)(node -> leftNode));
    }
    if (node -> rightNode != NULL) {
        printToBuff(buff, ',', remainingSize, (NodePtr)(node -> rightNode));
    }
}


//test SumMatrix
void testSumMatrix(void){
    Node* node = (Node*) malloc(sizeof(Node));
    assert(node != NULL);
    node->leftNode = NULL;
    node->rightNode = NULL;

    Matrix* matrix1 = new_matrix(2, 2, &NODE_FIELD_INFO);
    node->lexem = "X11";
    set_element(matrix1, 0, 0, (void*) node);
    node->lexem = "X12";
    set_element(matrix1, 0, 1,(void*) node);
    node->lexem = "X21";
    set_element(matrix1, 1, 0,(void*) node);
    node->lexem = "X22";
    set_element(matrix1, 0, 1,(void*) node);

    Matrix* matrix2 = new_matrix(2, 2, &NODE_FIELD_INFO);
    node->lexem = "Y11";
    set_element(matrix2, 0, 0,(void*) node);
    node->lexem = "Y12";
    set_element(matrix2, 0, 1,(void*) node);
    node->lexem = "Y21";
    set_element(matrix2, 1, 0,(void*) node);
    node->lexem = "Y22";
    set_element(matrix2, 0, 1, (void*)node);
    
    free(node);

    Matrix* sum_poduct = new_matrix(2, 2, &NODE_FIELD_INFO);
    


}

//test Mult_Matrix

//test Mult_on_scalar_matrix

//test transpose_Matrix
