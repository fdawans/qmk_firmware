
#include QMK_KEYBOARD_H
//for keymap
#include "keymap_belgian.h"
//for macros
#include "sendstring_belgian.h"

// Layers
#define _COL 0
#define _LOCK 1
#define _SYM 2
#define _NAV 3
#define _FN 4

//Used for _SYM Layer (Lock Numbers) & _FN Layer (Lock Function Keys)
#define TAPPING_TOGGLE 1

//Activate Layer on Hold, Press Space on Tap //Backspace: KC_BSPC
#define NAV_SPC LT(_NAV, KC_SPC)
#define FN_DEL LT(_FN, KC_DEL)

//Mod-tap
#define WIN_ENT RWIN_T(KC_ENTER) //Win on Hold, Enter on Tap
#define ALT_WOX ALT_T(KC_PAST) //Alt on Hold, Numpad * on Tap (Wox)

//Shortcuts on NAV Layer or on Double Tap
#define _SEL LCTL(KC_Q) // Ctrl + A in AZERTY
#define _REDO LCTL(KC_Y)
#define _UNDO LCTL(KC_W) //Ctrl + Z in AZERTY
#define _COPY LCTL(KC_C)
#define _CUT LCTL(KC_X)
#define _PASTE LCTL(KC_V)

//One Shot Layers / Sticky Keys
//Press to switch layer for the next key
//Hold to keep layer on
#define M_SYM OSL(_SYM)
#define M_FN OSL(_FN)

//Switch to layer and stay on it until key is press again
#define M_LOCK TG(_LOCK)

//One Shot Modifiers / Sticky Keys
//Press to apply modifier for the next key
//Hold to keep modifier on
#define M_SFT OSM(MOD_LSFT)
#define M_CTR OSM(MOD_LCTL)
#define M_ALT OSM(MOD_LALT)

//Own programs
#define DITTO KC_PSLS // Numpad '/' to start Ditto
#define CHEAT KC_INS // Insert to start Cheat

//Change Virtual Desktops
#define DESK_R LCTL(LWIN(KC_RIGHT))
#define DESK_L LCTL(LWIN(KC_LEFT))

//Task Manager - Control Shift Esc
#define TASK RCTL(RSFT(KC_ESC))

//Delay on Windows Key
//#define M_WIN OSM(MOD_LGUI)

// Tap Dance keycodes - Use TD(code) in layout to use
enum td_keycodes {
    COPY,
    QUOT,
    PGHM,
    PGND,
    CLR,
    SH_M
    };

//Variables for Auto Key Press
static uint32_t key_timer = 0;
static bool key_trigger = false;

// Custom keycodes - Macros
enum custom_keycodes {
    USER = SAFE_RANGE,
    MAILP,
    MAILB,
    ETREM,
    UCIRC,
    ECIRC,
    PASS,
    ALTF4,
    PHONE,
    LOGIN,
    AUTO_KEY
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case USER:
        if (record->event.pressed) {
             SEND_STRING("u548868");
        } else {
        }
        break;
    case MAILP:
        if (record->event.pressed) {
            // press alt then key 2 on qwerty then release alt to get @ on azerty BE
            SEND_STRING("info"SS_DOWN(X_RALT)SS_TAP(X_2)SS_UP(X_RALT)"floriandawans.com");
        } else {
        }
        break;
    case MAILB:
        if (record->event.pressed) {
            SEND_STRING("florian.dawans"SS_DOWN(X_RALT)SS_TAP(X_2)SS_UP(X_RALT)"bpost.be");
        } else {
        }
        break;
    case PASS:
        if (record->event.pressed) {
            SEND_STRING("Bpost01");
        } else {
        }
        break;
    case LOGIN:
        if (record->event.pressed) {
            SEND_STRING("u548868"SS_TAP(X_TAB)"Bpost01"SS_TAP(X_ENTER));
        } else {
        }
        break;
    case PHONE:
        if (record->event.pressed) {
            SEND_STRING("0494781375");
        } else {
        }
        break;
     case ETREM:
        if (record->event.pressed) {
            register_mods(MOD_BIT(KC_LSFT));
            register_code(BE_DCIR);
            unregister_mods(MOD_BIT(KC_LSFT));
            unregister_code(BE_DCIR);
            register_code(BE_E);
            unregister_code(BE_E);
        } else {
        }
        break;
    case UCIRC:
        if (record->event.pressed) {
            register_code(BE_DCIR);
            unregister_code(BE_DCIR);
            register_code(BE_U);
            unregister_code(BE_U);
        } else {
        }
        break;

    case ECIRC:
        if (record->event.pressed) {
            register_code(BE_DCIR);
            unregister_code(BE_DCIR);
            register_code(BE_E);
            unregister_code(BE_E);
        } else {
        }
        break;

    case ALTF4:
        if (record->event.pressed) {
            register_mods(MOD_BIT(KC_LALT));
            register_code(KC_F4);
            unregister_mods(MOD_BIT(KC_LALT));
            unregister_code(KC_F4);
        } else {
        }
        break;

    case AUTO_KEY:
            if (record->event.pressed) {
                key_trigger ^= true;
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
     KC_ESC  ,XXXXXXX ,XXXXXXX ,TD(QUOT),BE_UNDS ,BE_PERC ,                                            BE_ASTR ,BE_MINS ,BE_SLSH ,XXXXXXX ,XXXXXXX ,KC_BTN2 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,BE_Q    ,BE_W    ,BE_F    ,BE_P    ,BE_B    ,BE_EQL  ,                          BE_PLUS ,BE_J    ,BE_L    ,BE_U    ,BE_Y    ,BE_EGRV ,KC_BTN1 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SYM   ,BE_A    ,BE_R    ,BE_S    ,BE_T    ,BE_G    ,BE_LPRN ,                          BE_RPRN ,TD(SH_M),BE_N    ,BE_E    ,BE_I    ,BE_O    ,_COPY   ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     M_SFT   ,BE_Z    ,BE_X    ,BE_C    ,BE_D    ,BE_V    ,CHEAT   ,DESK_L  ,        DESK_R  ,DITTO   ,BE_K    ,BE_H    ,BE_COMM ,BE_DOT  ,BE_EACU ,_PASTE  ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     ALTF4   ,TASK    ,M_LOCK  ,ALT_WOX ,    NAV_SPC  ,    WIN_ENT ,M_ALT   ,        M_CTR   ,FN_DEL  ,    KC_BSPC ,     BE_QUES ,TD(CLR) ,_SEL    ,_CUT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),



     [_LOCK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,XXXXXXX ,XXXXXXX ,TD(QUOT),BE_UNDS ,BE_PERC ,                                            BE_ASTR ,BE_MINS ,BE_SLSH ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(BE_Q) ,S(BE_W) ,S(BE_F) ,S(BE_P) ,S(BE_B) ,BE_EQL  ,                          BE_PLUS ,S(BE_J) ,S(BE_L) ,S(BE_U) ,S(BE_Y) ,BE_EGRV ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(BE_A) ,S(BE_R) ,S(BE_S) ,S(BE_T) ,S(BE_G) ,BE_LPRN ,                          BE_RPRN ,S(BE_M) ,S(BE_N)  ,S(BE_E),S(BE_I) ,S(BE_O) ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,S(BE_Z) ,S(BE_X) ,S(BE_C) ,S(BE_D) ,S(BE_V) ,_______ ,_______,         _______ ,_______ ,S(BE_K) ,S(BE_H) ,BE_COMM ,BE_DOT  ,BE_EACU ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     BE_QUES ,TD(CLR) ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

   [_SYM] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                                             ,XXXXXXX ,XXXXXXX ,BE_BSLS ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,BE_AMP  ,BE_7    ,BE_8    ,BE_9    ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,BE_CIRC ,BE_HASH ,BE_UGRV ,UCIRC   ,ETREM   ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,BE_AGRV ,BE_4    ,BE_5    ,BE_6    ,XXXXXXX ,BE_LBRC ,                          BE_RBRC ,BE_CCED ,BE_DLR  ,BE_EURO ,BE_PIPE ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,BE_AT   ,BE_1    ,BE_2    ,BE_3    ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,BE_LABK ,BE_RABK ,BE_SCLN ,BE_COLN ,ECIRC   ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,BE_DOT  ,BE_0    ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     BE_EXLM ,XXXXXXX ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                                             ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_RWIN ,KC_ESC  ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,KC_PGUP ,KC_UP   ,KC_PGDN ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_SEL    ,KC_TAB  ,KC_LSFT ,KC_LCTRL,KC_LALT ,BE_LCBR ,                          BE_RCBR ,XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,_UNDO   ,_REDO   ,_CUT    ,_COPY   ,_PASTE   ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_HOME ,XXXXXXX ,KC_END  ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     XXXXXXX ,XXXXXXX ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

     [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_VOLU ,XXXXXXX ,KC_F10  ,KC_F11  ,KC_F12  ,XXXXXXX ,                                            AUTO_KEY,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_VOLD ,XXXXXXX ,KC_F7   ,KC_F8   ,KC_F9   ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,USER    ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG ,KC_ASRP ,KC_F4   ,KC_F5   ,KC_F6   ,XXXXXXX ,BE_LCBR ,                          BE_RCBR ,MAILP   ,MAILB   ,PASS    ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BRIU ,KC_ASUP ,KC_F1   ,KC_F2   ,KC_F3   ,XXXXXXX ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,LOGIN   ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_BRID ,KC_ASDN ,XXXXXXX ,XXXXXXX ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     PHONE   ,XXXXXXX ,_______ ,_______
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
            register_code16(KC_INS);
            break;
        case SINGLE_HOLD:
            clear_keyboard();
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_INS);
    }
}

void clear_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            unregister_code16(KC_INS);
            break;
        case SINGLE_HOLD:
            clear_keyboard();
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code16(KC_INS);
    }
}

void shiftm_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP: // m
            register_code16(KC_SCLN);
            break;
        case SINGLE_HOLD: // M
            register_mods(MOD_BIT(KC_LSFT));
            register_code16(KC_SCLN);
            break;
        case DOUBLE_SINGLE_TAP: // mm
            register_code16(KC_SCLN);
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
    //[M] =  ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, shiftm_finished, shiftm_reset,)
     //[ETC] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(cycleEtc, NULL, NULL, 800),
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
    case _LOCK:
        rgblight_enable_noeeprom();
        rgblight_sethsv_noeeprom(HSV_WHITE);
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

void matrix_scan_user(void) {
    if (timer_elapsed32(key_timer) > 29900) { // 30000 = 30 seconds
        key_timer = timer_read32();  // resets timer
        if (key_trigger) tap_code(KC_NO); // tap if enabled
    }
}
