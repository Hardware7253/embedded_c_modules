#include "rotary_encoder.h"

// Updates the rotary encoder
// This should be called in an update loop constantly
// get_renc_dir is used to access the information this function gathers
void update_renc(renc_t* renc, bool p1_state, bool p2_state) {
    if (p1_state != renc->last_p1_state) {
        if (p1_state) { // Rise
            renc-> p2_rise_state = p2_state;
        } else { // Fall
            if (p2_state != renc->p2_rise_state) {
                renc->dir = p2_state ? RENC_LEFT : RENC_RIGHT;
            }
        }
    }

    renc->last_p1_state = p1_state;
}

// Returns true everytime the rotary encoder clicks left
bool is_renc_left(renc_t* renc) {
    if (renc->dir == RENC_LEFT) {
        renc->dir = RENC_NONE;
        return true;
    }
    return false;
}

// Returns true everytime the rotary encoder clicks right 
bool is_renc_right(renc_t* renc) {
    if (renc->dir == RENC_RIGHT) {
        renc->dir = RENC_NONE;
        return true;
    }
    return false;
}