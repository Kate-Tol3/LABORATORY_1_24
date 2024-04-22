#pragma once
#include <stddef.h>
#include "field_info.h"

typedef struct {
    size_t size_v;
    size_t size_h;
    void* elements;
    FieldInfo* typeInfo;
 
} Matrix;


//make_new_matrix
Matrix* new_matrix(const size_t, const size_t, FieldInfo*);

//elemet setter and getter
void get_element(const Matrix*,const size_t,const size_t, void*);
void* get_element_pointer(const Matrix*,const size_t,const size_t);
void set_element(Matrix*,const size_t i,const size_t j, const void* val);

// compare functions
int match_matrix_types(const Matrix*, const Matrix* );
int match_matrix_size(const Matrix*, const Matrix* );
int match_matrix_size_opposite(const Matrix*, const Matrix* );

// matrix making and printing functions
void fill_matrix(Matrix*, const void*);
void fill_zeros_matrix(Matrix*);
void print_matrix(Matrix*);
void read_matrix(Matrix*);

// matrix operation functions
void sum_matrix (const Matrix* , const Matrix*, Matrix*);
void transpose_matrix(const Matrix*, Matrix*);
void mult_matrix(Matrix*, Matrix*, Matrix*);
void mult_on_number_matrix(Matrix*, void*);



