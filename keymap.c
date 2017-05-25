#include <stdarg.h>
#include "atreus62.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"

#define _______ KC_TRNS

#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_UNDO LCTL(KC_Z)
#define KC_REDO LCTL(KC_Y)

#define _WRKMN 0
#define _QWERTY 1
#define _CODE 2
#define _UTIL 3
#define _RAISE 4
#define _ADJUST 5
// Layers
enum preonic_keycodes {
  WRKMN = 0,
  QWERTY,
  CODE,
  UTIL,
  RAISE,
  ADJUST
};

// Tapdance
enum {
  TD_FUN = 0,
  TD_3EQ,
  TD_2EQ
};
#define ALTTAB 1
#define CTRLWIN 2

//State and timers
uint16_t kf_timers[12];


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap 0: Base Workman layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |  Esc   |   1  |   2  |   3  |   4  |   5  |                 |   6  |   7  |   8  |   9  |   0  |  RAISE |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |  Tab   |   Q  |   D  |   R  |   W  |   B  |                 |   J  |   F  |   U  |   P  |   ;  |   \    |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |  CODE  |   A  |   S  |   H  |   T  |   G  |                 |   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |   |      |   K  |   L  |   ,  |   .  |   /  | RShift |
 * |--------+------+------+------+------+------|Back  |   |Enter |-------------+------+------+------+--------|
 * | LCtrl  |AltTab| LGui |  Alt |crl/Wn| UTIL |Space |   |      |Space | Left | Down |  Up  |Right |TT(Rai) |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [_WRKMN] = {

   { KC_ESC,   KC_1,     KC_2,    KC_3,    KC_4,       KC_5,   KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0 ,    RAISE },
   { KC_TAB,   KC_Q,     KC_D,    KC_R,    KC_W,       KC_B,   KC_NO,   KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,  KC_BSLS },
   { CODE,     KC_A,     KC_S,    KC_H,    KC_T,       KC_G,   KC_NO,   KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,     KC_QUOT },
   { KC_LSFT,  KC_Z,     KC_X,    KC_M,    KC_C,       KC_V,   KC_BSPC, KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT },
   { KC_LCTL,  M(ALTTAB),KC_LGUI, KC_LALT, M(CTRLWIN), UTIL,   KC_ENT,  KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  TT(_RAISE) }

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
  [_QWERTY] = {

   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ },
   { _______  ,KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     _______ ,KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS },
   { _______  ,KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     _______ ,KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT },
   { _______  ,KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     _______ ,KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  _______ },
   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ }

  },

   /* Keymap 2: Code layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   +  |   =  |   {  |   }  |   |  |                 |      |      |TD_2EQ|      |      |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |   &  |   -  |   (  |   )  |   `  |                 |      |      |TD_3EQ|TD_FUN|      |        |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |   <  |   >  |   [  |   ]  |   ~  |      |   |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |  F8  |  F9  |  F10 |  F11 |      |      |   |      |      |      |      |      |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */

  [_CODE] = {

   { _______  ,_______      ,_______      ,_______  ,_______  ,_______  ,_______ , _______  ,_______  ,  _______,    _______  ,_______  ,_______ },
   { _______  ,LSFT(KC_EQL), KC_EQL,       KC_LCBR,  KC_RCBR,  KC_PIPE,  _______ , _______  ,TD(TD_2EQ), _______,    _______  ,_______  ,_______ },
   { _______  ,LSFT(KC_7),   KC_MINS,      KC_LPRN,  KC_RPRN,  KC_GRV,   _______ , _______  ,TD(TD_3EQ),  TD(TD_FUN),_______  ,_______  ,_______ },
   { _______  ,LSFT(KC_COMM),LSFT(KC_DOT), KC_LBRC,  KC_RBRC,  KC_TILD,  _______ , _______  ,_______  ,  _______,    _______  ,_______  ,_______ },
   { _______  ,KC_F8,        KC_F9,        KC_F10,   KC_F11,   _______  ,_______ , _______  ,_______  ,  _______,    _______  ,_______  ,_______ }

  },

   /* Keymap 3: UTIL (Lower) layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |    `   |  F1  |  F2  |  F3  |  F4  |  F5  |                 |  F6  |  F7  |  F8  |  F9  |  F10 |  F11   |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |Ctrl+Tab|      |      |Ctrl+W|      |Delete|                 |      |      |      |      |      |  F12   |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |  All | Save |      |      |   _  |                 |      | Home |PgDown| PgUp | End  | Insert |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |      | Cut  |      | Copy |Paste |      |   |      | Prev | Next | Vol- | Vol+ | Play |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |CtrAltDl|      |      | Undo | Redo |      |      |   |      |      |Ctrl+<|Ctrl+^|Ctrl+v|Ctrl+>|        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [_UTIL] = {

   { KC_GRV,              KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     _______, KC_F6,      KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11 },
   { LCTL(KC_TAB),        _______,   _______  , LCTL(KC_W),_______  , KC_DELT   ,_______, _______    ,_______  ,_______  ,_______  ,_______  ,KC_F12 },
   { _______,             LCTL(KC_A),LCTL(KC_S),_______,   _______  , KC_UNDS   ,_______, _______    ,KC_HOME  ,KC_PGDN  ,KC_PGUP  ,KC_END,   KC_INS },
   { _______,             _______,   LCTL(KC_X),_______,   KC_COPY,   KC_PASTE,  _______ ,KC_MPRV    ,KC_MNXT  ,KC_VOLD  ,KC_VOLU  ,KC_MPLY  ,_______ },
   { LCTL(LALT(KC_DELT)), _______,   _______,   KC_UNDO,   KC_REDO,    _______  ,_______ ,_______    ,_______  ,_______  ,_______  ,_______  ,_______ }

  },

    /* Keymap 4: Raise/Num layer
 *
 * ,-------------------------------------------.                 ,-------------------------------------------.
 * |        |      |      |      |      |      |                 |      |      |   /  |   *  |   -  |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |                 |      |   7  |   8  |   9  |   +  |        |
 * |--------+------+------+------+------+------|                 |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |                 |      |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|------.   .------|------+------+------+------+------+--------|
 * |        |      |      |      | App  |      |      |   |      |      |   1  |   2  |   3  |Enter |        |
 * |--------+------+------+------+------+------|      |   |      |-------------+------+------+------+--------|
 * |        |      |      |      |      | UTIL |      |   |      |      |   0  |   0  |   .  |      |        |
 * `--------------------------------------------------'   '--------------------------------------------------'
  */
  [_RAISE] = {

   { _______  ,_______  ,_______  ,_______  ,_______  ,_______  ,_______ ,_______  ,_______, KC_PSLS, KC_PAST, KC_PMNS,  _______ },
   { _______  ,_______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______ ,_______,  KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,  _______ },
   { _______  ,_______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______ ,_______,  KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,  _______ },
   { _______  ,_______,  _______,  _______,  KC_APP,   _______,  _______ ,_______,  KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,  _______ },
   { _______  ,_______  ,_______  ,_______  ,_______ , UTIL,     _______, _______,  KC_KP_0, KC_KP_0, KC_PDOT, _______,  _______ }

  },

  /* Keymap 5: Adjust layer
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
  [_ADJUST] = {

   { _______  ,_______,  _______,  _______,  _______,  _______,  _______ ,_______,  _______,  _______,  _______,  AG_NORM,  AG_SWAP },
   { _______  ,_______,  _______,  _______,  _______,  _______,  _______ ,_______,  _______,  _______,  _______,  _______,  _______ },
   { _______  ,_______,  _______,  _______,  _______,  _______,  _______ ,_______,  WRKMN,    QWERTY,   _______,  _______,  _______ },
   { _______  ,_______,  _______,  _______,  _______,  _______,  _______ ,_______,  _______,  _______,  _______,  _______,  _______ },
   { _______  ,_______,  _______,  _______,  _______,  _______,  _______ ,_______,  _______,  _______,  _______,  _______,  _______ }

  }
};

// TAP DANCE SETTINGS
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

void dance_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ===
      m_tapn(KC_EQL, KC_EQL, KC_EQL, 0);
      break;
    case 2: // !==
      register_code(KC_LSHIFT);
      m_tapn(KC_1, 0);
      unregister_code(KC_LSHIFT);
      m_tapn(KC_EQL, KC_EQL, 0);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_two_eq (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // ==
      m_tapn(KC_EQL, KC_EQL, 0);
      break;
    case 2: // !=
      register_code(KC_LSHIFT);
      m_tapn(KC_1, 0);
      unregister_code(KC_LSHIFT);
      m_tapn(KC_EQL, 0);
      break;
    default:
      reset_tap_dance(state);
  }
}

void dance_fun (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: // =>    
      m_tapn(KC_EQL, 0);
      register_code(KC_LSFT);
      m_tapn(KC_DOT, 0);
      unregister_code(KC_LSFT);
      break;
    case 2: // () => {}
      register_code(KC_LSFT);
      m_tapn(KC_9, KC_0, KC_SPC, 0);
      unregister_code(KC_LSFT);
      m_tapn(KC_EQL, 0);
      register_code(KC_LSFT);
      m_tapn(KC_DOT, KC_SPC, KC_LBRC, KC_RBRC, 0);
      unregister_code(KC_LSFT);
      break;
    default:
      reset_tap_dance(state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_FUN] = ACTION_TAP_DANCE_FN (dance_fun)
 ,[TD_3EQ] = ACTION_TAP_DANCE_FN (dance_eq)
 ,[TD_2EQ] = ACTION_TAP_DANCE_FN (dance_two_eq)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case ALTTAB: 
    if (record->event.pressed) {
      return MACRO( D(LALT), D(TAB), W(200), U(TAB), END );
    } else {
      return MACRO( U(LALT), END );
    }
    break;
  }
  return MACRO_NONE;
};

// Custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  //Cancle one-shot mods.
  switch (keycode) {
        case WRKMN:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_WRKMN);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case CODE:
          if (record->event.pressed) {
            layer_on(_CODE);
          } else {
            layer_off(_CODE);
          }
          return false;
          break;
        case UTIL:
          if (record->event.pressed) {
            layer_on(_UTIL);
            update_tri_layer(_UTIL, _RAISE, _ADJUST);
          } else {
            layer_off(_UTIL);
            update_tri_layer(_UTIL, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_UTIL, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_UTIL, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

const uint16_t PROGMEM fn_actions[] = {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
