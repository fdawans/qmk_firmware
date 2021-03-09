#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define PREVENT_STUCK_MODIFIERS
#undef ONESHOT_TIMEOUT

//No timeout to chain modifiers (to test)
//#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */


//For Tap Dance
#define TAPPING_TERM 200

//Auto Shift
#pragma once

#define AUTO_SHIFT_TIMEOUT 250
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_NUMERIC
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define DISABLE_LEADER
#define NO_MUSIC_MODE
