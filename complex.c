#include <string.h>
#include <math.h>
#include "field_info.h"
#include "complex.h"

void complex_sum(const void* v1, const void* v2, void* res){
    ((Complex*) res)->re = ((Complex*) v1)->re + ((Complex*) v2)->re;
    ((Complex*) res)->img = ((Complex*) v1)->img + ((Complex*) v2)->img;
}

void complex_mult(const void* v1,const void* v2, void* res){ 
    double re1 = ((Complex*) v1)->re, img1 = ((Complex*) v1)->img, re2 = ((Complex*) v2)->re, img2 = ((Complex*) v2)->img;
    ((Complex*) res)->re = (re1 * re2) - (img1*img2);
    ((Complex*) res)->img = re1*img2 + re2*img1;
}

void read_complex_array(const size_t v,const size_t h, void* elems){
    Complex *arr;
    arr = (Complex*) elems;
    printf("type your matrix:\n");
    for (size_t i = 0; i < v;i++){
        for (size_t j = 0;j < h;j ++){
            printf("real: ");
            scanf("%lf", &(arr + i*h + j)->re);
            printf("img: ");
            scanf("%lf", &(arr + i*h + j)->img);
            printf("\n");
            //printf(" %zu %zu\n", (arr + i*h + j)->re,(arr + i*h + j)->img);
        }
    }
}

void complex_print(const void* el){
    const Complex* elc = el;
    if ((elc->img) > 0){
        printf("%.3lf + %.3lfi", elc->re, elc->img);
    }
    else if (elc->img == 0){
        printf("%.3lf + 0i", elc->re);
    }
    else{
        printf("%.3lf - %.3lfi", elc->re, fabs(elc->img));
    }
    
}

void complex_set_zero(void* ptr){
    ((Complex*) ptr)->re = 0;
    ((Complex*) ptr)->img = 0;
}

void complex_get_number(void* ptr){
    printf("\nre: ");
    scanf("%lf", &(((Complex*)ptr)->re));
    printf("img: ");
    scanf("%lf", &(((Complex*)ptr)->img));
}

static FieldInfo* COMPLEX_FIELD_INFO= NULL;

FieldInfo* get_info_complex(){
        if (COMPLEX_FIELD_INFO==NULL){
            COMPLEX_FIELD_INFO = (FieldInfo*) malloc(sizeof(FieldInfo)); //!!!!!
            COMPLEX_FIELD_INFO->type = "complex";
            COMPLEX_FIELD_INFO->el_size = sizeof(Complex);
            COMPLEX_FIELD_INFO->sum_el = complex_sum;
            COMPLEX_FIELD_INFO->mult_el = complex_mult;
            COMPLEX_FIELD_INFO->print_el = complex_print;
            COMPLEX_FIELD_INFO->read_array = read_complex_array;
            COMPLEX_FIELD_INFO->set_zero = complex_set_zero;
            COMPLEX_FIELD_INFO->get_number = complex_get_number;

        }
        return COMPLEX_FIELD_INFO;
}