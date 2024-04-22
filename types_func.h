#pragma once
#include <stddef.h>

//int functions

void int_sum(const void* v1,const void* v2, void* res);
void int_mult(const void* v1,const void* v2, void* res);
void int_print(void* el);
void read_int_array(const size_t v,const size_t h, void* elems);
void int_set_zero(void* ptr);
void int_get_number(void* ptr);

//float functions

void real_sum(const void* v1,const void* v2, void* res);
void real_mult(const void* v1,const void* v2, void* res);
void real_print(void* el);
void read_real_array(const size_t v,const size_t h, void* elems);
void real_set_zero(void* ptr);
void real_get_number(void* ptr);

//complex functions

void complex_sum(const void* v1,const void* v2, void* res);
void complex_mult(const void* v1,const void* v2, void* res);
void complex_print(void* el);
void read_complex_array(const size_t v,const size_t h, void* elems);
void complex_set_zero(void* ptr);
void complex_get_number(void* ptr);
