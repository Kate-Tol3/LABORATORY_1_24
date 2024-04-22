
#include "matrix.h"
#include "field_info.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//elemet setter and getter
void get_element(const Matrix* mat,const size_t i,const size_t j,  void* val){
    if ((mat->size_v >= i) && (mat->size_h >= j)){
        memcpy(val, (char*)(mat->elements) + i*(mat->size_h)*(mat->typeInfo->el_size) + j*(mat->typeInfo->el_size), (mat->typeInfo->el_size));
    }
    else{"\nERROR\n";}
}

void set_element(Matrix* mat,const size_t i,const size_t j,const void* val){
    if ((mat->size_v >= i) && (mat->size_h >= j)){
    memcpy((char*)(mat->elements) + i*(mat->size_h)*(mat->typeInfo->el_size) + j*(mat->typeInfo->el_size), val, (mat->typeInfo->el_size));
    }
    else{"\nERROR\n";}
}

void* get_element_pointer(const Matrix* mat,const size_t i,const size_t j){
    if ((mat->size_v >= i) && (mat->size_h >= j)){
    void* ptr;
    ptr = (char*)(mat->elements) + i*(mat->size_h)*(mat->typeInfo->el_size) + j*(mat->typeInfo->el_size);
    return ptr;
    }
    else{"\nERROR\n";}
}


// compare functions
int match_matrix_types(const Matrix* mat1, const Matrix* mat2){
    if ((strcmp(mat1->typeInfo->type, mat2->typeInfo->type)) == 0  && (mat1->typeInfo->el_size == mat2->typeInfo->el_size)){
        return 1;
    }
    else{
        return 0;
    }
}

int match_matrix_size(const Matrix* mat1, const Matrix* mat2){
    if (mat1->size_h == mat2->size_h && mat1->size_v == mat2->size_v){
        return 1;
    }
    else{
        return 0;
    }
}

int match_matrix_size_opposite(const Matrix* mat1, const Matrix* mat2){
    if (mat1->size_v == mat2->size_h && mat1->size_h == mat2->size_v){
        return 1;
    }
    else{
        return 0;
    }
}


// matrix making and printing functions
Matrix* new_matrix(const size_t nsize_v, const size_t nsize_h, FieldInfo* info){ 
    
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->size_v = nsize_v;
    matrix->size_h = nsize_h;
    matrix->typeInfo = info;
    
    size_t nel_size = matrix->typeInfo->el_size;
    matrix->elements = (void*) malloc(nsize_v*nsize_h*nel_size); 
    return matrix;
}

void fill_matrix(Matrix* matrix, const void* elems){
    if (matrix->typeInfo->type != NULL){
        size_t el_size = matrix->typeInfo->el_size, size_h = matrix->size_h, size_v = matrix->size_v;
        void* val = malloc(el_size);
        for (size_t i = 0; i < size_v; i++){
            for (size_t j = 0; j < size_h; j++){
                memcpy(val, (char*)(elems) + i*size_h*el_size + j*el_size, el_size);
                set_element(matrix, i, j,  val);
            }
        }
        free(val);
    }
    else {
        printf("\nERROR\n");
    }
}

void fill_zeros_matrix(Matrix* matrix){
    if (matrix->typeInfo->type != NULL){
        size_t el_size = matrix->typeInfo->el_size, size_h = matrix->size_h, size_v = matrix->size_v;
        void* zero = malloc (el_size);
        matrix->typeInfo->set_zero(zero);
        for (size_t i = 0; i < size_v; i++){
            for (size_t j = 0; j < size_h; j++){
                set_element(matrix, i, j,  zero);
            }
        }
        free(zero);
    }
    else {
        printf("\nERROR\n");
    }
}

void print_matrix (Matrix* matrix){
    void* val = malloc (matrix->typeInfo->el_size);
    size_t v = matrix->size_v, h = matrix->size_h;
    //printf("\n");
    for (size_t i = 0; i < v;i++){
        for (size_t j = 0;j < h;j ++){
            get_element(matrix, i, j, val);
            matrix->typeInfo->print_el(val);
            printf(" ");
        }
        printf("\n");
    }
}

void read_matrix (Matrix* mat){
    void* elems;
    elems = (void*) malloc ((mat->typeInfo->el_size) * (mat->size_h) * (mat->size_v));
    mat->typeInfo->read_array(mat->size_v, mat->size_h, elems);
    fill_matrix(mat, elems);
}


// matrix operation fumctions
void sum_matrix (const Matrix* mat1, const Matrix* mat2, Matrix* res){
    // if  (match_matrix_types(mat1, mat2)&& match_matrix_types(mat2, res) && \
    //   match_matrix_size(mat1, mat2) && match_matrix_size(mat2, res)){
    
    if  (match_matrix_types(mat1, mat2)&& match_matrix_types(mat2, res) && \
      match_matrix_size(mat1, mat2) && match_matrix_size(mat2, res)){

        size_t h = mat1->size_h, v = mat1->size_v;
        size_t el_size = mat1->typeInfo->el_size;
        void *val = malloc(el_size);
        void *val1 = malloc(el_size);
        void *val2= malloc(el_size);
        for (size_t i = 0; i < v; i ++){
            for (size_t j = 0; j < h; j++){
               
                get_element(mat1, i, j, val1);
                get_element(mat2, i, j, val2);
                //mat2->typeInfo->print_el(val1);//!!!! - если раскомментить то работает почему не понятно
                mat1->typeInfo->sum_el(val1, val2, val);
                set_element(res, i, j, val);
            }
        }
        free(val); 
        free(val1);
        free(val2);

    } 
    else{
        res->elements = NULL;
        printf("\nsomething went wrong...\n");
    }
}

void mult_on_number_matrix (Matrix* res, void* val){
        size_t h = res->size_h, v = res->size_v;
        size_t el_size = res->typeInfo->el_size;
        
        void *comp = malloc(el_size);
        void *el = malloc(el_size);
        for (size_t i = 0; i < v; i ++){
            for (size_t j = 0; j < h; j++){
                get_element(res, i, j, el);
                res->typeInfo->mult_el(el, val, comp);
                set_element(res, i, j, comp);
            }
        }
        free(el); 
        free(comp);
}

void transpose_matrix(const Matrix* mat, Matrix* res){
    if (match_matrix_size_opposite(mat, res)){
        size_t h = mat->size_h, v = mat->size_v;
        size_t el_size = mat->typeInfo->el_size;
        
        void *val = malloc(el_size);
        for (size_t i = 0; i < v; i ++){
            for (size_t j = 0; j < h; j++){  
                get_element(mat, i, j, val);
                set_element(res, j, i, val);
            }
        }

        free(val); 
    }
    
}

void mult_matrix (Matrix* mat1, Matrix* mat2, Matrix* res){
    if (mat1->size_h == mat2->size_v && match_matrix_types(mat1, mat2) && match_matrix_types(mat2, res)\
     && (res->size_v == mat1->size_v) && res->size_h == mat2->size_h){

        size_t h1 = mat1->size_h, v1 = mat1->size_v, h2 = mat2->size_h, v2 = mat2->size_v;
        size_t el_size = mat1->typeInfo->el_size;
        
        void *comp = malloc(el_size);
        void *val = malloc(el_size);
        void *val1 = malloc(el_size);
        void *val2= malloc(el_size);
        void *zero = malloc(el_size);
        mat1->typeInfo->set_zero(zero);

        for (size_t i = 0; i < v1; i ++){
            for (size_t j = 0; j < h2; j++){
                set_element(res, i, j, zero);
                for (size_t k = 0; k < h1; k++){
                    get_element(mat1, i, k, val1);
                    get_element(mat2, k, j, val2);
                    get_element(res, i, j, val);
                    mat1->typeInfo->mult_el(val1, val2, comp);
                    mat1->typeInfo->sum_el(val, comp, val);
                    set_element(res, i, j, val);
                }
            }
        }

        free(val); 
        free(val1);
        free(val2);
        free(comp);
        free(zero);


    }
    else {
        res->elements = NULL;
        printf("\nERROR\n");
    }
}

