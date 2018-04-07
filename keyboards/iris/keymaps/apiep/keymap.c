#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_ENTS MT(MOD_RSFT, KC_ENT)
#define KC_ATAB LALT(KC_TAB)
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RSET RESET
#define KC_BL_S BL_STEP
#define KC_ADJS ADJUST

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = KC_KEYMAP(
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     GRV , 1  , 2  , 3  , 4  , 5  ,               6  , 7  , 8  , 9  , 0  ,PIPE,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     TAB , Q  , W  , E  , R  , T  ,               Y  , U  , I  , O  , P  ,BSPC,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     ESCC, A  , S  , D  , F  , G  ,               H  , J  , K  , L  ,SCLN,QUOT,
  //+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+
     LSFT, Z  , X  , C  , V  , B  ,ADJS,    LGUI, N  , M  ,COMM, DOT,SLSH,ENTS,
  //+----+----+----+----+----+----+----/   \----+----+----+----+----+----+----+
                        LALT,LOWR,SPC ,      BSPC,RASE,RCTL
  //                  +----+----+----'       '----+----+----+
),
[_LOWER] = KC_KEYMAP(
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     TILD,EXLM, AT ,HASH,DLR ,PERC,              CIRC,AMPR,ASTR,LPRN,RPRN,BSLS,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     ATAB,    , UP ,    ,    ,    ,                  , P7 , P8 , P9 ,    ,BSPC,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
         ,LEFT,DOWN,RGHT,    ,LBRC,              RBRC, P4 , P5 , P6 ,PLUS,QUOT,
  //+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+
         ,    ,    ,    ,    ,LCBR,    ,        ,RCBR, P1 , P2 , P3 ,MINS,ENTS,
  //+----+----+----+----+----+----+----/   \----+----+----+----+----+----+----+
                            ,    ,    ,          ,    , P0
  //                  +----+----+----'       '----+----+----+
),
[_RAISE] = KC_KEYMAP(
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     F12 , F1 , F2 , F3 , F4 , F5 ,               F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     WH_U,BTN1,MS_U,BTN2,    ,    ,                  ,MPRV,MPLY,MNXT,    ,    ,
  //+----+----+----+----+----+----+             +----+----+----+----+----+----+
     WH_D,MS_L,MS_D,MS_R,    ,UNDS,              EQL ,HOME,VOLU,MUTE,    ,    ,
  //+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+
         ,    ,    ,    ,    ,MINS,    ,        ,PLUS,END ,VOLD,    ,    ,ENTS,
  //+----+----+----+----+----+----+----/   \----+----+----+----+----+----+----+
                            ,    ,    ,          ,    ,
  //                  +----+----+----'       '----+----+----+
),
[_ADJUST] = KEYMAP(
//,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
    RESET  , DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                            _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                    _______, _______, _______,                  _______, _______, _______
//                                `--------+--------+--------'                `--------+--------+--------'
)
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2] = SONG(QWERTY_SONG);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
    if (record->event.pressed) {
      #ifdef AUDIO_ENABLE
        PLAY_SONG(tone_qwerty);
      #endif
      persistent_default_layer_set(1UL << _QWERTY);
    }
    return false;
    break;

    case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;

    case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    } else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;

    case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    } else {
      layer_off(_ADJUST);
    }
    break;
  }
  return true;
}
