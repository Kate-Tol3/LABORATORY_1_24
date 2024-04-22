#include "field_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void real_sum(const void* v1,const void* v2, void* res){
    double val;
    val = (*((double*) v1) + *((double*) v2));
    memcpy(res, &val, sizeof(double));
}

void real_mult(const void* v1,const void* v2, void* res){
    double val;
    val =  (*((double*) v1) *  *((double*) v2));
    memcpy(res, &val, sizeof(double));
}


void real_print(void* el){
    printf("%.3lf", *((double*) el));
}

void read_real_array(const size_t v,const size_t h, void* elems){
    double *arr;
    arr = (double*)elems;

    printf("type your matrix:\n");
    for (size_t i = 0; i < v;i++){
        for (size_t j = 0;j < h;j ++){
            scanf("%lf", (arr + i*h + j));

            //printf(" %lf\n", *(arr + i*h + j));
        }
    }
}

//static void* REAL_ZERO = NULL;

void real_set_zero(void* ptr){
    *(double*)ptr = 0.0;
}

void real_get_number(void* ptr){
    scanf("%lf", (double*)ptr);
}

static FieldInfo* REAL_FIELD_INFO= NULL;

FieldInfo* get_info_real(){
        if (REAL_FIELD_INFO==NULL){
                REAL_FIELD_INFO = (FieldInfo*) malloc(sizeof(FieldInfo));///
                REAL_FIELD_INFO->type = "real";
                REAL_FIELD_INFO->el_size = sizeof(double);
                REAL_FIELD_INFO->sum_el = real_sum;
                REAL_FIELD_INFO->mult_el = real_mult;
                REAL_FIELD_INFO->print_el = real_print;
                REAL_FIELD_INFO->read_array = read_real_array;
                REAL_FIELD_INFO->set_zero = real_set_zero;
                REAL_FIELD_INFO->get_number = real_get_number;
        }
        return REAL_FIELD_INFO;
}

