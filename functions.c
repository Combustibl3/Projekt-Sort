#include "functions.h"

void swapValue(uint32_t * a, uint32_t * b){
    uint32_t aold;
    aold= *a;
    *a = *b;
    *b = aold;
}
