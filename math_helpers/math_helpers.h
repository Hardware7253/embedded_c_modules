#pragma once

#include <stdint.h>

typedef struct {
    float val;
    char unit_prefix;
} eng_float_t;

int32_t map(int32_t num, int32_t num_low, int32_t num_high, int32_t out_low, int32_t out_high);
eng_float_t convert_to_eng_notation(float num);
