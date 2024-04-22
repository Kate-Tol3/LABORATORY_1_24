#include "field_info.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void int_sum(const void* v1,const void* v2, void* res){ 
    int val;
    val = (*((int*) v1) + *((int*) v2));
    memcpy(res, &val, sizeof(int));
    //free((void*)&val);
}

void int_mult(const void* v1,const  void* v2, void* res){
    int val;
    val = (*((int*) v1) * *((int*) v2));
    memcpy(res, &val, sizeof(int));
    //free((void*)&val);
}

void read_int_array(const size_t v,const size_t h, void* elems){
    int *arr;
    arr = (int*)elems;

    printf("type your matrix:\n");
    for (size_t i = 0; i < v;i++){
        for (size_t j = 0;j < h;j ++){
            scanf("%d", (arr + i*h + j));

            //printf(" %d\n", *(arr + i*h + j));
        }
    }
}

void int_print(const void* el){
    printf("%7d", *((const int*) el));
}

void int_set_zero(void* ptr){
    *(int*)ptr = 0;
}

void int_get_number(void* ptr){
    scanf("%d", (int*)ptr);
}

static FieldInfo* INT_FIELD_INFO= NULL;

FieldInfo* get_info_int(){
        if (INT_FIELD_INFO==NULL){
                INT_FIELD_INFO = (FieldInfo*) malloc(sizeof(FieldInfo)); //!!!!!
                INT_FIELD_INFO->type = "int";
                INT_FIELD_INFO->el_size = sizeof(int);
                INT_FIELD_INFO->sum_el = int_sum;
                INT_FIELD_INFO->mult_el = int_mult;
                INT_FIELD_INFO->print_el = int_print;
                INT_FIELD_INFO->read_array = read_int_array;
                INT_FIELD_INFO->set_zero = int_set_zero;
                INT_FIELD_INFO->get_number = int_get_number;

        }
        return INT_FIELD_INFO;
}


