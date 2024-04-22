#pragma once
#include <stddef.h>

//int functions

void int_sum(const void* v1,const void* v2, void* res);
void int_mult(const void* v1,const void* v2, void* res);

//float functions

void real_sum(const void* v1,const void* v2, void* res);
void real_mult(const void* v1,const void* v2, void* res);

//complex functions

void complex_sum(const void* v1,const void* v2, void* res);
void complex_mult(const void* v1,const void* v2, void* res);

