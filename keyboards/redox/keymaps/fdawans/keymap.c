
//for keymap
#include "keymap_belgian.h"
//for macros
//#include "sendstring_belgian.h"
#include QMK_KEYBOARD_H


// Layer shorthand
#define _COL 0
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
#define KC_REDO LCTL(KC_Y)
#define KC_UNDO LCTL(KC_Z)
#define KC_COPY LCTL(KC_C)
#define KC_CUT LCTL(KC_X)
#define KC_PASTE LCTL(KC_V)

//Already defined in keymap_french.h
//Copy that file to personal folder
//#define FR_CCIRC ALGR(KC_9)
//#define FR_UMLT LSFT(FR_CIRC)

/*
KC_ASDN = Lower the Auto Shift timeout variable (down)
KC_ASUP = Raise the Auto Shift timeout variable (up)
KC_ASRP = Report your current Auto Shift timeout value
*/

//One Shot Layers
#define M_SYM OSL(_SYM)
#define M_FN OSL(_FN)

//One Shot Modifiers
#define M_SFT OSM(MOD_LSFT)
#define M_CTR OSM(MOD_LCTL)
#define M_ALT OSM(MOD_LALT)

//Delay !
#define M_WIN OSM(MOD_LGUI)


// Tap Dance keycodes
// Use TD(ALT_LP) in layout to use
enum td_keycodes {
    COPY, // Our example key: `CTRL + C` when held, `D` when tapped. Add additional keycodes for each tapdance.
    QUOT,
    PGHM,
    PGND,
    CLR,
    SH_M
    };


enum custom_keycodes {
    USER = SAFE_RANGE,
    MAIL
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case USER:
        if (record->event.pressed) {
            SEND_STRING("u548868");
        } else {
        }
        break;

    case MAIL:
        if (record->event.pressed) {
            SEND_STRING("infofloriandawanscom");
        } else {
        }
        break;
    }
    return true;
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
void quot_finished(qk_tap_dance_state_t *state, void *user_data);
void quot_reset(qk_tap_dance_state_t *state, void *user_data);
void clear_finished(qk_tap_dance_state_t *state, void *user_data);
void clear_reset(qk_tap_dance_state_t *state, void *user_data);
void home_finished(qk_tap_dance_state_t *state, void *user_data);
void home_reset(qk_tap_dance_state_t *state, void *user_data);
void end_finished(qk_tap_dance_state_t *state, void *user_data);
void end_reset(qk_tap_dance_state_t *state, void *user_data);
void shiftm_finished(qk_tap_dance_state_t *state, void *user_data);
void shiftm_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COL] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,BE_AMP  ,BE_EACU ,TD(QUOT),BE_ASTR ,BE_PERC ,                                            BE_PLUS ,BE_AT   ,BE_AGRV ,BE_EGRV ,BE_UNDS ,TD(CLR) ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,BE_Q    ,BE_W    ,BE_F    ,BE_P    ,BE_B    ,BE_EQL  ,                          BE_MINS ,BE_J    ,BE_L    ,BE_U    ,BE_Y    ,BE_SLSH ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SYM   ,BE_A    ,BE_R    ,BE_S    ,BE_T    ,BE_G    ,BE_LPRN ,                          BE_RPRN ,TD(SH_M),BE_N    ,BE_E    ,BE_I    ,BE_O    ,KC_ESC  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SFT   ,BE_Z    ,BE_X    ,BE_C    ,BE_D    ,BE_V    ,KC_LGUI ,TD(PGND),        TD(PGHM),M_FN    ,BE_K    ,BE_H    ,BE_COMM ,BE_DOT  ,BE_QUES ,M_SFT   ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,M_ALT   ,    NAV_SPC  ,    KC_ENTER,M_ALT   ,        M_CTR   ,KC_DEL  ,    KC_BSPC ,     KC_UP   ,KC_LEFT ,KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


   [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,BE_1    ,BE_2    ,BE_3    ,BE_4    ,BE_5    ,                                            BE_6    ,BE_7    ,BE_8    ,BE_9    ,BE_0    ,XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,BE_HASH ,BE_DOT  ,                          BE_UNDS ,XXXXXXX ,XXXXXXX ,BE_UGRV ,XXXXXXX ,BE_BSLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BE_LABK ,BE_RABK ,BE_DLR  ,XXXXXXX ,XXXXXXX ,BE_LBRC ,                          BE_RBRC ,XXXXXXX ,XXXXXXX ,BE_EURO ,BE_DIAE ,BE_PIPE ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,BE_CCED ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,BE_SCLN ,BE_COLN ,BE_EXLM ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     KC_UP   ,KC_LEFT ,KC_DOWN ,KC_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,BE_1    ,BE_2    ,BE_3    ,BE_4    ,BE_5    ,                                            BE_6    ,BE_7    ,BE_8    ,BE_9    ,BE_0    ,BE_UNDS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_PGUP ,KC_UP   ,KC_PGDN ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_SEL  ,KC_TAB  ,KC_LSFT ,KC_LCTRL,KC_LALT ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_REDO ,KC_UNDO ,KC_CUT  ,KC_COPY ,KC_PASTE,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_HOME ,XXXXXXX ,KC_END  ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_VOLU ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLD ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,USER    ,XXXXXXX ,XXXXXXX ,KC_F12  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG ,KC_ASRP ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,BE_LCBR ,                          BE_RCBR ,MAIL    ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BRIU ,KC_ASUP ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_BRID ,KC_ASDN ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
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

void home_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_PGUP);
            break;
        case SINGLE_HOLD:
            //register_mods(MOD_BIT(KC_LCTL));
            register_code16(KC_HOME);
            break;
        case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_PGUP);
    }
}

void home_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_PGUP);
            break;
        case SINGLE_HOLD:
            //unregister_mods(MOD_BIT(KC_LCTL));
            unregister_code16(KC_HOME);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_PGUP);
    }
}

void end_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_PGDN);
            break;
        case SINGLE_HOLD:
            //register_mods(MOD_BIT(KC_LCTL));
            register_code16(KC_END);
            break;
        case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_PGDN);
    }
}

void end_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_PGDN);
            break;
        case SINGLE_HOLD:
            //unregister_mods(MOD_BIT(KC_LCTL));
            unregister_code16(KC_END);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_PGDN);
    }
}

void quot_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP: // KC_4 = ' on Windows BE
            register_code16(KC_4);
            break;
        case SINGLE_HOLD: // Shift + KC_3 = 3 on Windows BE
            register_mods(MOD_BIT(KC_LSFT));
            register_code16(KC_3);
            break;
        case DOUBLE_SINGLE_TAP: // KC_3 = " on Windows BE
            register_code16(KC_3);
    }
}

void quot_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_4);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code16(KC_3);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_3);
    }
}

void clear_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            register_code16(KC_CAPS);
            break;
        case SINGLE_HOLD:
            clear_keyboard();
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_CAPS);
    }
}

void clear_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        case SINGLE_HOLD:
            clear_keyboard();
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_CAPS);
    }
}

void shiftm_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP: // KC_4 = ' on Windows BE
            register_code16(KC_SCLN);
            break;
        case SINGLE_HOLD: // Shift + KC_3 = 3 on Windows BE
            register_mods(MOD_BIT(KC_LSFT));
            register_code16(KC_SCLN);
            break;
        case DOUBLE_SINGLE_TAP: // KC_3 = " on Windows BE
            register_code16(KC_SCLN);
    }
}

void shiftm_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_SCLN);
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code16(KC_SCLN);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SCLN);
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copy_finished, copy_reset),
    [QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
    [PGHM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, home_finished, home_reset),
    [PGND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, end_finished, end_reset),
    [CLR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, clear_finished, clear_reset),
    [SH_M] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shiftm_finished, shiftm_reset)
};

// Common LED indicator
void update_led(void) {
  // Capslock priority
  if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_WHITE);
  } else {
    // look layer...
    switch (biton32(layer_state)) {
      case _NAV:
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
      case _FN:
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
      case _SYM:
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
      case _COL:
        default:
            rgblight_disable_noeeprom();
            break;
    }
  }
}

void led_set_user(uint8_t usb_led) {
  // must be trigger to
  // - activate capslock color
  // - go back to the proper layer color if needed when quitting capslock
  update_led();
}

uint32_t layer_state_set_user(uint32_t state) {
  // must be trigger to
  // - activate a layer color
  // - de-activate a layer color
  update_led();
  return state;
}
