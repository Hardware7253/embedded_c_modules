#include "math_helpers.h"
#include <math.h>

// Maps a number with range [num_low, num_high] to a new output with range [out_low, out_high]
// This works fine with negative numbers
// The full int32 range can't be used because a multiply by 1000 is performed to keep precision
// The output range should be less than 2 million to avoid integer overflow errors
int32_t map(int32_t num, int32_t num_low, int32_t num_high, int32_t out_low, int32_t out_high) {
    int32_t out = ((1000 * (num - num_low) / (num_high - num_low)) * (out_high - out_low) / 1000 + out_low);

    // Clamp output
    if (out > out_high) {
        return out_high;
    } else if (out < out_low) {
        return out_low;
    }
    return out;
}

#define TOP_PREFIX_POWER 12
#define BOTTOM_PREFIX_POWER -15 
const char UNIT_PREFIXES[] = {'T', 'G', 'M', 'k', ' ', 'm', 'u', 'n', 'p', 'f'};

// Converts a float to a value with an engineering unit suffix
// E.g. 5e-8 > 50n
//
// This should only be used for displaying a number to a user
// because the function is too slow to be called frequently
eng_float_t convert_to_eng_notation(float num) {
    eng_float_t result = {
        .unit_prefix = ' ',
        .val = num
    };

    float test_num = powf(10, TOP_PREFIX_POWER);
    uint8_t iterations = 1 + ((TOP_PREFIX_POWER - BOTTOM_PREFIX_POWER) / 3);

    float abs_num = fabsf(num);
    for (uint8_t i = 0; i < iterations; i++) {
        test_num /= 1000.0;
        if (abs_num >= test_num) {
            result.unit_prefix = UNIT_PREFIXES[i];
            result.val = num / test_num;
            return result;
        }
    }

    return result;
}