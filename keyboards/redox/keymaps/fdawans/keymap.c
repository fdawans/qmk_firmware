
// https://github.com/qmk/qmk_firmware/blob/master/keyboards/xd75/keymaps/french/keymap.c

#include "keymap_french.h"
#include QMK_KEYBOARD_H


// Layer shorthand
#define _COLEMAK 0
#define _SYM 1 //One Shot Key (Layer for next keypress only)
#define _NAV 2 // Layer (keep it pressed)
#define _FN 3

//Tap once to lock layer, hold to activate layer - use TT(layer)
//Used for _SYM Layer (Lock Numbers) & _FN Layer (Lock Function Keys)
#define TAPPING_TOGGLE 1
//Activate Layer on Hold, Press Space on Tap //Backspace: KC_BSPC
#define NAV_SPC LT(_NAV, KC_SPC)
#define NAV_BSPC LT(_NAV, KC_BSPC)

//Shortcuts on NAV Layer or on Hold/Double Tap
#define KC_SEL LCTL(KC_A)
#define KC_REDO LCTL(KC_Z)
#define KC_UNDO LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_D)
#define KC_PASTE LCTL(KC_V)

/*
KC_ASDN = Lower the Auto Shift timeout variable (down)
KC_ASUP = Raise the Auto Shift timeout variable (up)
KC_ASRP = Report your current Auto Shift timeout value
*/

//One Shot Keys
#define M_SYM OSM(_SYM)
#define M_SFT OSM(MOD_LSFT)
#define M_CTR OSM(MOD_LCTL)
#define M_ALT OSM(MOD_LALT)
#define M_WIN OSM(MOD_LGUI)

// Tap Dance keycodes
// Use TD(ALT_LP) in layout to use
enum td_keycodes {
    COPY, // Our example key: `CTRL + C` when held, `D` when tapped. Add additional keycodes for each tapdance.
    TABLK,
    QUOT,
    PHOM,
    PEND
    };

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
uint8_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void copy_finished(qk_tap_dance_state_t *state, void *user_data);
void copy_reset(qk_tap_dance_state_t *state, void *user_data);
void tablk_finished(qk_tap_dance_state_t *state, void *user_data);
void tablk_reset(qk_tap_dance_state_t *state, void *user_data);
void quot_finished(qk_tap_dance_state_t *state, void *user_data);
void quot_reset(qk_tap_dance_state_t *state, void *user_data);
//void phom_finished(qk_tap_dance_state_t *state, void *user_data);
//void phom_reset(qk_tap_dance_state_t *state, void *user_data);
//void pend_finished(qk_tap_dance_state_t *state, void *user_data);
//void pend_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_VOLU ,FR_AMP  ,FR_EACU ,FR_QUOT ,FR_ASTR ,FR_PERC ,                                            FR_MINS ,FR_AT   ,FR_AGRV ,FR_EGRV ,FR_UNDS ,TD(PHOM),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLD ,FR_Q    ,FR_W    ,FR_F    ,FR_P    ,FR_B    ,KC_EQL ,                           FR_PLUS ,FR_J    ,FR_L    ,FR_U    ,FR_Y    ,FR_SLSH ,TD(PEND),
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SYM   ,FR_A    ,FR_R    ,FR_S    ,FR_T    ,FR_G    ,KC_LPRN ,                          KC_RPRN ,FR_M    ,FR_N    ,FR_E    ,FR_I    ,FR_O    ,M_SYM   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SFT   ,FR_Z    ,FR_X    ,FR_C    ,TD(COPY),FR_V    ,KC_ESC  ,M_WIN   ,       TD(TABLK),TT(_FN) ,FR_K    ,FR_H    ,FR_COMM ,FR_DOT  ,FR_QUES ,M_SFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_ASUP ,KC_ASDN ,KC_ASRP ,XXXXXXX ,     M_ALT   ,    NAV_SPC ,KC_ENTER,        KC_DEL  ,NAV_BSPC,    M_CTR   ,     KC_UP   ,KC_LEFT ,KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


   [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_BRIU ,FR_1    ,FR_2    ,FR_3    ,FR_4    ,FR_5    ,                                            FR_8    ,FR_9    ,FR_0    ,FR_GRV  ,FR_UNDS ,XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BRID ,XXXXXXX ,XXXXXXX ,FR_APOS ,XXXXXXX ,FR_HASH ,FR_6    ,                          FR_7    ,XXXXXXX ,XXXXXXX ,FR_UGRV ,FR_CCIRC,FR_BSLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,FR_DLR  ,XXXXXXX ,FR_LCBR ,FR_LBRC ,                          FR_RBRC ,FR_RCBR ,XXXXXXX ,FR_EURO ,FR_UMLT ,FR_PIPE ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,FR_LABK ,FR_RABK ,FR_CCED ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,FR_SCLN ,FR_COLN ,FR_EXLM ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    _______ ,     KC_UP   ,KC_LEFT ,KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,FR_1    ,FR_2    ,FR_3    ,FR_4    ,FR_5    ,                                            FR_8    ,FR_9    ,FR_0    ,FR_GRV  ,FR_UNDS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_PGUP ,KC_UP   ,KC_PGDN ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_SEL  ,KC_TAB  ,KC_LSFT ,KC_LCTRL,KC_LALT ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_REDO ,KC_UNDO ,KC_CUT  ,KC_COPY ,KC_PASTE,XXXXXXX ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,KC_HOME ,XXXXXXX ,KC_END  ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_F6   ,                          KC_F7   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    _______ ,XXXXXXX ,        XXXXXXX ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

};


// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    }

    if (state->count == 2) return DOUBLE_SINGLE_TAP;
    else return 3; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void copy_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_D);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTRL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_code16(KC_C);
            break;
        case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            tap_code16(KC_D);
            register_code16(KC_D);
    }
}

void copy_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_D);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTRL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            unregister_code16(KC_C);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_D);
    }
}

void tablk_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_TAB);
            break;
        case SINGLE_HOLD:
            register_code16(KC_CAPS);
            break;
        case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_TAB);
    }
}

void tablk_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_TAB);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_CAPS);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_TAB);
    }
}

void quot_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_TAB);
            break;
        case SINGLE_HOLD:
            register_code16(KC_CAPS);
            break;
        case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_TAB);
    }
}

void quot_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_TAB);
            break;
        case SINGLE_HOLD:
            unregister_code16(KC_CAPS);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_TAB);
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_finished, copy_reset),
    [TABLK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tablk_finished, tablk_reset),
    [QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
    [PHOM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
    [PEND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset)

};
