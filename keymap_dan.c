/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| Backsp|Ins|
     * |---------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Enter|Del|
     * |------------------------------------------------------`    |---|
     * |Fn5   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|    |PgU|
     * |---------------------------------------------------------------|
     * |Shif|  #|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
     * |---------------------------------------------------------------|
     * |Fn2  |  Gui|  Fn6|          Fn0        |Fn7|Fn8|Alt|Lef|Dow|Rig|
     * `---------------------------------------------------------------'
     */
    [0] = KEYMAP_ISO( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS, EQL, BSPC,    DEL, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,          END, \
        FN5, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,     ENT, PGUP,\
        LSFT,FN1, Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,     UP,  PGDN,\
        FN2, LGUI,FN6,                FN0,           FN7, FN8, RALT,     LEFT,DOWN,RGHT \
    ),
    /* Layer 1: HHKB mode (Space)
     * ,---------------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Backsp|Ins|
     * |---------------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus| Up|   |     |Del|
     * |------------------------------------------------------`    |---|
     * |      |VoD|VoU|Mut|   |   |   |Bsp|Del|Fn10|Lef|Rig|   |   |PgU|
     * |---------------------------------------------------------------|
     * |    |   |   |   |Fn9|   |   |   |   |   |   |Dow|      |PgU|PgD|
     * |---------------------------------------------------------------|
     * |     |  Fn4|     |                     |   |   |   |Hom|PgD|End|
     * `---------------------------------------------------------------'
     */
    [1] = KEYMAP_ISO( \
        GRV,   F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12, BSPC,    INS, \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,TRNS,PAUS,  UP,          DEL, \
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,BSPC,DEL,FN10,LEFT,RIGHT,TRNS,    PENT, PGUP,\
        TRNS,TRNS,TRNS,TRNS,FN9,TRNS,TRNS,TRNS,TRNS,TRNS,DOWN,TRNS,TRNS,      PGUP,PGDN,\
        TRNS,TRNS,LALT,               TRNS,          TRNS,TRNS,TRNS,     HOME,PGDN,END  \
    ),
};

enum macro_id {
    CMD_TAB,
    CMD_GRAVE,
    HASH_TILDE,
    CTRL_A,
    CMD_ALT_C,
    CMD_SHIFT_L,
};

enum function_id {
    CMD_TAB_ALT,
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const action_t fn_actions[] PROGMEM = {
#endif
    [0]  = ACTION_LAYER_TAP_KEY(1, KC_SPC),            // function layer with Space
    [1]  = ACTION_MACRO(HASH_TILDE),                   // hash / tilde
    [2]  = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_F18),      // notification centre
    [3]  = ACTION_LAYER_TAP_KEY(2, MOD_RCTL),          // wasd mouse mode
    [4]  = ACTION_MODS_KEY(MOD_LSFT, KC_GRV),          // tilde
    [5]  = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_F19),      // alfred
    [6]  = ACTION_FUNCTION_TAP(CMD_TAB_ALT),           // tap cmd tab or alt
    [7]  = ACTION_MACRO(CMD_GRAVE),                    // grave tab
    [8]  = ACTION_MACRO(CTRL_A),                       // ctrl a
    [9]  = ACTION_MACRO(CMD_ALT_C),                    // cmd alt c
    [10] = ACTION_MACRO(CMD_SHIFT_L),                  // cmd shift l
};

//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt);

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CMD_TAB:
            return (record->event.pressed ?
                    MACRO( D(LGUI), T(TAB), U(LGUI), END ) :
                    MACRO_NONE);
	case CMD_GRAVE:
            return (record->event.pressed ?
                    MACRO( D(LGUI), T(GRV), U(LGUI), END) :
                    MACRO_NONE);
        case HASH_TILDE:
            if (get_mods()&(MOD_LSFT|MOD_RSFT)) {
                return (record->event.pressed ?
                       MACRO( D(GRV), END ) :
                       MACRO( U(GRV), END ));
            } else {
                return (record->event.pressed ?
                       MACRO( D(LALT), D(3), U(LALT), END ) :
                       MACRO( U(LALT), U(3), END ));
            }
       case CTRL_A:
            return (record->event.pressed ?
                       MACRO( D(LCTL), T(A), U(LCTL), END ) :
                       MACRO_NONE);
       case CMD_ALT_C:
            return (record->event.pressed ?
                    MACRO( D(LGUI), D(LALT), T(C), U(LGUI),  U(LALT), END) :
                    MACRO_NONE);
       case CMD_SHIFT_L:
            return (record->event.pressed ?
                    MACRO( D(LGUI), D(LSFT), T(L), U(LGUI),  U(LSFT), END) :
                    MACRO_NONE);
    }
    return MACRO_NONE;
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case CMD_TAB_ALT:
            if (record->event.pressed) {
                if (record->tap.count > 0 && !record->tap.interrupted) {
                    if (record->tap.interrupted) {
                        register_mods(MOD_BIT(KC_LALT));
                    }
                } else {
                    register_mods(MOD_BIT(KC_LALT));
                }
            } else {
                if (record->tap.count > 0 && !(record->tap.interrupted)) {
                    action_macro_play(MACRO( D(LGUI), T(TAB), U(LGUI), END ));
                    record->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LALT));
                }
            }
            break;
    }
}
