
// https://github.com/qmk/qmk_firmware/blob/master/keyboards/xd75/keymaps/french/keymap.c

#include "keymap_french.c"
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

//Shortcuts on NAV Layer
#define KC_SEL LCTL(KC_A)
#define KC_REDO LCTL(KC_Z)
#define KC_UNDO LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_D)
#define KC_PASTE LCTL(KC_V)
#define KC_PRT LCTL(KC_V)

//One Shot Key 
#define M_SYM OSM(_SYM)
#define M_SFT OSM(MOD_LSFT)
#define M_CTR OSM(MOD_LCTR)
#define M_ALT OSM(MOD_LALT)

// Tap Dance keycodes
// Use TD(ALT_LP) in layout to use
enum td_keycodes {
    COPY // Our example key: `CTRL + C` when held, `D` when tapped. Add additional keycodes for each tapdance.
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
             ,FR_AMP  ,FR_EACU ,FR_QUOT ,FR_APOS ,FR_PERC ,                                           ,FR_UNDS ,FR_AT   ,FR_AGRV ,FR_EGRV ,FR_MINS ,FR_ASTR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     FR_TAB  ,FR_Q    ,FR_W    ,FR_F    ,FR_P    ,FR_B    ,FR_EQUA ,                          FR_PLUS ,FR_J    ,FR_L    ,FR_U    ,FR_Y    ,FR_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SYM   ,FR_A    ,FR_R    ,FR_S    ,FR_T    ,FR_G    ,FR_LPAR ,                          FR_RPAR ,FR_M    ,FR_N    ,FR_E    ,FR_I    ,FR_O    ,M_SYM  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SFT   ,FR_Z    ,FR_X    ,FR_C    ,TD(COPY),FR_V    ,FR_ESC  ,FR_LCMD ,                ,TT(_FN) ,FR_K,   ,FR_H    ,FR_COMM ,FR_DOT  ,FR_QUES ,M_SFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        ,        ,        ,        ,         ,M_ALT       ,NAV_SPC ,FR_ENTR ,        FR_DEL  ,NAV_BSPC    ,M_CTR        ,FR_UP   ,FR_LEFT ,FR_DOWN ,FR_RIGHT,
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


   [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
             ,FR_1    ,FR_2    ,FR_3    ,FR_4    ,FR_5    ,                                            FR_8    ,FR_9    ,FR_0    ,FR_GRV  ,FR_UNDS , ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                                                 ,FR_HASH ,FR_6    ,                          FR_7    ,        ,        ,FR_UGRV ,FR_DIAE ,FR_BSLS , ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                               ,FR_DLR  ,        ,FR_LCBR ,FR_LBRC ,                          FR_RBRC ,FR_RCBR ,        ,FR_EURO ,FR_CIRC ,FR_PIPE , ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            ,FR_LABK ,FR_RABK  ,FR_CCED ,        ,        ,        ,        ,                ,        ,        ,        ,FR_SCLN ,FR_COLN ,FR_EXLM , ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
             ,,        ,             ,        FR_LALT,                                                                  ,FR_UP   ,FR_LEFT ,FR_DOWN ,FR_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
     [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
             ,FR_1    ,FR_2    ,FR_3    ,FR_4    ,FR_5    ,                                            FR_8    ,FR_9    ,FR_0    ,FR_GRV  ,FR_UNDS , ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                                                 ,        ,        ,                                  ,        ,FR_PGUP ,FR_UP   ,FR_PGDN ,  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
              KC_SEL  ,R_TAB   ,FR_LSFT ,FR_LCTR ,FR_LALT          ,                                  ,        ,FR_LEFT ,FR_DOWN ,FR_RIGHT,  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
             ,KC_REDO ,KC_UNDO ,KC_CUT  ,KC_COPY ,KC_PASTE,        ,        ,                ,        ,        ,FR_HOME ,        ,FR_END  ,  ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
             ,        ,             ,    
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  
     [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     FR_EMPT ,FR_F1   ,FR_F2   ,FR_F3   ,FR_F4   ,FR_F5   ,		                                       ,FR_F8   ,FR_F9   ,FR_F10  ,FR_F11  ,FR_F12  ,FR_PSCR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                                                 ,        ,FR_F6   ,                          FR_F7   ,        ,FR_PGUP ,FR_UP   ,FR_PGDN ,  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
                      ,R_TAB   ,FR_LSFT ,FR_LCTR ,FR_LALT          ,                                  ,        ,FR_LEFT ,FR_DOWN ,FR_RIGHT,  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
             ,        ,        ,        ,        ,        ,        ,        ,                ,        ,        ,FR_HOME ,        ,FR_END  ,  ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
             ,        ,             ,    
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
            register_mods(MOD_BIT(KC_LCTR)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
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
            unregister_mods(MOD_BIT(KC_LCTR)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            unregister_code16(KC_C); 
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_D);
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_finished, copy_reset),
};