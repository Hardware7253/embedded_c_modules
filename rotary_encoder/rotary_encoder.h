#pragma once

#include <stdbool.h>

typedef enum {
   RENC_NONE = 0,
   RENC_LEFT,
   RENC_RIGHT, 
} renc_dir_t;

typedef struct {
    bool last_p1_state;
    bool p2_rise_state; // p2 state captured on p1 rising edge
    renc_dir_t dir; 
} renc_t;

void update_renc(renc_t* renc, bool p1_state, bool p2_state);
bool is_renc_left(renc_t* renc);
bool is_renc_right(renc_t* renc);
