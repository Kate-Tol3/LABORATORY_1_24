#pragma once
#include <stddef.h>

typedef void (*binary_op)(const void* v1,const void* v2, void* res);
typedef void (*print_el)(const void* el);
typedef void (*read_array)(const size_t v,const size_t h, void* elems);
typedef void (*set_zero)(void* ptr);
typedef void (*get_number)(void* ptr);

typedef struct {
    const char* type;
    size_t el_size;
    binary_op sum_el;
    binary_op mult_el;
    print_el print_el;
    read_array read_array;
    set_zero set_zero;
    get_number get_number;

} FieldInfo;

FieldInfo* get_info_int();
FieldInfo* get_info_real();
FieldInfo* get_info_complex();
