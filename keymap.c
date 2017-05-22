#include <stdarg.h>
#include "atreus62.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"

/*
 *WINDOWS SWEDISH
 */
 /*
  *WINDOWS SWEDISH
  */
 #define KN_HALF KC_GRV          // 1/2
 #define KN_PLUS KC_MINS         // +
 #define KN_ACUT KC_EQL          // ´
 #define KN_QUOT KC_NUHS         // '
 #define KN_LABK KC_NUBS         // <
 #define KN_MINS KC_SLSH         // -
 #define KN_EXLM LSFT(KC_1)      // !
 #define KN_DQT  LSFT(KC_2)      // "
 #define KN_AT   RALT(KC_2)      // @
 #define KN_HASH LSFT(KC_3)      // #
 #define KN_DLR  RALT(KC_4)      // $
 #define KN_PERC LSFT(KC_5)      // %
 #define KN_AMPR LSFT(KC_6)      // &
 #define KN_SLSH LSFT(KC_7)      // /
 #define KN_LPRN LSFT(KC_8)      // (
 #define KN_RPRN LSFT(KC_9)      // )
 #define KN_EQL  LSFT(KC_0)      // =
 #define KN_UNDS LSFT(KN_MINS)   // _
 #define KN_QUES LSFT(KN_PLUS)   // ?
 #define KN_GRAV LSFT(KN_ACUT)   // `
 #define KN_LCBR RALT(KC_7)      // {
 #define KN_RCBR RALT(KC_0)      // }
 #define KN_LBRC RALT(KC_8)      // [
 #define KN_RBRC RALT(KC_9)      // ]
 #define KN_RABK LSFT(KN_LABK)   // <
 #define KN_COLN LSFT(KC_DOT)    // :
 #define KN_SCLN LSFT(KC_COMM)   // :
 #define KN_PIPE RALT(KN_LABK)   // |
 #define KN_QUES LSFT(KN_PLUS)   // ?
 #define KN_CIRC LSFT(KN_UMLA)   // ^
 #define KN_ASTR LSFT(KN_QUOT)   // *
 #define KN_TILD RALT(KN_UMLA)   // ~
 #define KN_BSLS RALT(KN_PLUS)   //

#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#define KC_HYP LSFT(LALT(LCTL(KC_LGUI)))

#define _______ KC_TRNS

#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(LSFT(KC_Z))

// Layers
enum {
  BASE = 0,
  NAV,
  SYM
};

//Macros
enum {
  KF_1 = 0, // 1, F1
  KF_2, // ...
  KF_3,
  KF_4,
  KF_5,
  KF_6,
  KF_7,
  KF_8,
  KF_9,
  KF_10,
  KF_11,
  KF_12
};

// Tapdance
enum {
  TD_FUN = 0,
  TD_EQ
};

//State and timers
uint16_t kf_timers[12];


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Workman layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  |                 |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |  Tab   |   Q  |   D  |   R  |   W  |   B  |                 |   J  |   F  |   U  |   P  |   ;  |   \    |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |  CODE  |   A  |   S  |   H  |   T  |   G  |                 |   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |   |      |   K  |   L  |   ,  |   .  |/ ~L3 | RShift |
 * |--------+------+------+------+------+------|Back  |   |Enter |-------------+------+------+------+--------|
 * | LCtrl  |AltTab| LGui |  Alt |      | UTIL |Space |   |      |Space | Left | Down |  Up  |Right | UPPER  |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [BASE] = {

   { KC_ESC   ,KC_1     ,KC_2     ,KC_3     ,KC_4    ,KC_5     ,_______ ,M(KF_6) ,M(KF_7) ,M(KF_8) ,M(KF_9) ,M(KF_10) ,M(KF_12) },
   { KC_TAB   ,KC_Q     ,KC_D     ,KC_R     ,KC_W    ,KC_B     ,_______ ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P     ,KN_AO },
   { OSM_LCTL ,KC_A     ,KC_S     ,KC_D     ,KC_F    ,KC_G     ,_______ ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KN_OE    ,KN_AE },
   { OSM_LSFT ,KC_Z     ,KC_X     ,KC_C     ,KC_V    ,KC_B     ,KC_BSPC ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KN_MINS  ,OSM_LSFT },
   { MO(NAV)  ,OSM_LCTL ,OSM_LALT ,KC_LGUI  ,MO(SYM) ,UTIL     ,KC_ENT  ,KC_SPC  ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT  ,KC_HYP }

 },

 /* Keymap 1: QUERTY layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |                 |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                 |   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |   |      |   N  |   M  |   ,  |   .  |   /  |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |      |      |      |      |      |      |   |      |      |      |      |      |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [NAV] = {

   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ },
   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,KC_NO   ,KC_HOME  ,KC_PGDN  ,KC_PGUP  ,KC_END   ,_______  ,_______ },
   { _______  ,KC_LSFT  ,KC_LCTL  ,KC_LALT  ,KC_L     ,_______  ,KC_NO   ,KC_LEFT  ,KC_DOWN  ,KC_UP    ,KC_RIGHT ,_______  ,_______ },
   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ },
   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______  ,_______  ,_______  ,KC_VOLD  ,KC_VOLU }

  },

   /* Keymap 1: Code layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |                 |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |                 |   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |   |      |   N  |   M  |   ,  |   .  |   /  |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |      |      |      |      |      |      |   |      |      |      |      |      |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */

   /* Keymap 2: UTIL (Lower) layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |    `   |  F1  |  F2  |  F3  |  F4  |  F5  |                 |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      |      |Ctrl+W|      |Delete|                 |      |      |      |      |      |  F12   |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |  All | Save |      |      |   _  |                 |      | Home |PgDown| PgUp | End  |        |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |      | Cut  |      | Copy |Paste |      |   |      | Prev | Next | Vol- | Vol+ | Play |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |CtrAltDl|      |      | Undo | Redo |      |      |   |      |      |Ctrl+<|Ctrl+^|Ctrl+v|Ctrl+>|        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [SYM] = {

   { _______  ,_______  ,_______  ,_______  ,_______  ,TD(TD_EQ) ,KC_NO   ,TD(TD_FUN) ,_______  ,_______  ,_______  ,_______  ,_______ },
   { _______  ,KN_LABK  ,KN_RABK  ,KN_LCBR  ,KN_RCBR  ,KN_PLUS   ,KC_NO   ,KN_AT      ,KN_DQT   ,KN_QUOT  ,KN_GRAV  ,KN_SLSH  ,_______ },
   { _______  ,KN_EXLM  ,KN_EQL   ,KN_LPRN  ,KN_RPRN  ,KN_MINS   ,KC_NO   ,KN_UNDS    ,KN_CIRC  ,KN_DLR   ,KN_AMPR  ,KN_PIPE  ,_______ },
   { _______  ,KN_EUR   ,KN_PERC  ,KN_LBRC  ,KN_RBRC  ,KN_ASTR   ,_______ ,KN_HASH    ,KN_SCLN  ,KN_COLN  ,KN_QUES  ,KN_BSLS  ,_______ },
   { _______  ,_______  ,_______  ,_______  ,_______  ,_______   ,_______ ,_______    ,_______  ,_______  ,_______  ,_______  ,_______ }

  }

    /* Keymap 3: Raise/Num layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |                 |      |   7  |   8  |   9  |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |                 |      |   4  |   5  |   6  |      |        |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |      |      |      | App  |      |      |   |      |      |   1  |   2  |   3  |      |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |      |      |      | UTIL |      |      |   |      |      |   0  |   0  |   .  |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */

  /* Keymap 4: Config layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |      |      |AGnorm| AGswap | 
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                 |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                 |      |      |WRKMN |QWERTY|      |        |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |   |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |      |      |      |      |      |      |   |      |      |      |      |      |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
};

#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)

static void m_tapn (uint8_t code, ...) {
  uint8_t kc = code;
  va_list ap;

  va_start(ap, code);
  do {
    register_code(kc);
    unregister_code(kc);
    wait_ms(50);
    kc = va_arg(ap, int);
  } while (kc != 0);
  va_end(ap);
}

static void m_handle_kf (keyrecord_t *record, uint8_t id) {
  uint8_t code = id - KF_1;

  if (record->event.pressed) {
    kf_timers[code] = timer_read ();
  } else {
    uint8_t kc_base;
    uint8_t long_press = (kf_timers[code] && timer_elapsed (kf_timers[code]) > TAPPING_TERM);

    kf_timers[code] = 0;

    switch(id){
      case KF_1 ... KF_10:
        if (long_press) {
          // Long press
          kc_base = KC_F1;
        } else {
          kc_base = KC_1;
        }
        code += kc_base;
        break;
      case KF_11:
        code = long_press ? KC_F11 : KC_ESC;
        break;
      case KF_12:
        code = long_press ? KC_F12 : KN_PLUS;
        break;
    }
    register_code (code);
    unregister_code (code);
  }
}

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch (id) {
    case KF_1 ... KF_12:
      m_handle_kf(record, id);
      break;
  }
  return MACRO_NONE;
};

// Custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool queue = true;

  //Cancle one-shot mods.
  switch (keycode) {
    case KC_ESC:
      if (record->event.pressed && get_oneshot_mods() && !has_oneshot_mods_timed_out()) {
        clear_oneshot_mods();
        queue = false;
      }
      break;
  }
  return queue;
}

// TAP DANCE SETTINGS
void dance_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ===
      register_code(KC_LSHIFT);
      m_tapn(KC_0, KC_0, KC_0, 0);
      unregister_code(KC_LSHIFT);
      break;
    case 2:
      register_code(KC_LSHIFT);
      m_tapn(KC_1, KC_0, KC_0, 0);
      unregister_code(KC_LSHIFT);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_fun (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // =>
      register_code(KC_LSHIFT);
      m_tapn(KC_0, KN_LABK, 0);
      unregister_code(KC_LSHIFT);
      break;
    case 2: // () => {}
      register_code(KC_LSHIFT);
      m_tapn(KC_8, KC_9, KC_SPC, KC_0, KN_LABK, KC_SPC, 0);
      unregister_code(KC_LSHIFT);
      register_code(KC_RALT);
      m_tapn(KC_7, 0);
      unregister_code(KC_RALT);
      TAP_ONCE(KC_ENT);
      break;
    default:
      reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_FUN] = ACTION_TAP_DANCE_FN (dance_fun)
 ,[TD_EQ] = ACTION_TAP_DANCE_FN (dance_eq)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  set_unicode_input_mode(UC_WINC);
};

LEADER_EXTERNS();
// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
