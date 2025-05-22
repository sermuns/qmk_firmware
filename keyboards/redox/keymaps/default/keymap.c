// DONE TAP 10x on a key to reset the board
// DONE Make a key shift to one layer when held down and toggle to another layer
// when presse twice
// DONE Test to use jkl as ctrl, shift and alt when held down. (Not implemented but same principle as for ctrl)
// DONE Tap toggle TT could be sufficent for layer switching as i want.
// DONE Arrow-keys?
// DONE One-shot ctrl and shift
// DONE Get mouse working
// DONE Navigation layer? WASD/HJKL/JKLI as arrowkeys?
// TODO Spacecadet shift and index finger for other open close tags?
// TODO Layer switching on thumb or elsewhere?
// TODO Media keys

// emoji selector? Unicode input?
//  What I use. Shortcuts with windows key. Easy acces ctrl, alt, shift.
//  Printscreen, arrowkeys on WASD, HJKL, JKIL, Volume up, Volume down,
//  brightness up, brightness down, wifi toggle, bluetoot toggle, mic/speaker
//  toggle.

#include QMK_KEYBOARD_H
#include "print.h"
#include "keymap_swedish.h"
#include "sendstring_swedish.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMB 1
#define _GAME 3
#define _SUDOKU 4
#define _NAV 5
#define _MEDIA 6

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    NUMB,
    GAME,
    SUDOKU,
    NAV,
    MEDIA,
};

enum {
    TD_F11,
    TD_F12,
    CT_RESET,
    OP_LAYER,
    TD1F1,
    TD2F2,
    TD3F3,
    TD4F4,
    TD5F5,
    TD6F6,
    TD7F7,
    TD8F8,
    TD9F9,
    TD0F10,
};

void dance_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 10) {
        print("Test");
        reset_keyboard();
        reset_tap_dance(state);
    }
}

bool op_layer_hold = false;
void op_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    // if state->count state->interupted state->pressed
    print("op_layer_finished");

    // Om nedtryckt i slutet av dance, använd som MO
    if (state->pressed) {
        op_layer_hold = true;
        layer_on(_NUMB);
        // How do i reset the layer after hold is finnished?
    }
    // Annars om vi har tryckt totalt 2 ggr på en knapp så skall vi toggla
    // lager. Kan bli lite fortare om vi sätter koden i den funktion som alltid
    // kallas på. För detta kommer att bara kallas på när vi har tryckt på en
    // annan knapp eller väntat TAPPING_TERM
    else if (state->count == 2) {
        // Toggles game layer. Only maked left thumb a space.
        // layer_state_is(_GAME) ? layer_off(_GAME) : layer_on(_GAME);
        if (layer_state_is(_GAME)) {
            print("turning off _GAME");
            layer_off(_GAME);
        } else {
            print("turning on _GAME");
            layer_off(_SUDOKU);
            layer_on(_GAME);
        }
    } else if (state->count == 3) {
        // Toggles game layer. Only maked left thumb a space.
        // layer_state_is(_GAME) ? layer_off(_GAME) : layer_on(_GAME);
        if (layer_state_is(_SUDOKU)) {
            print("turning off _GAME");
            layer_off(_SUDOKU);
        } else {
            print("turning on _GAME");
            layer_on(_SUDOKU);
            layer_off(_GAME);
        }
    }

    // Om nedtryckt i slutet av dance, använd som MO
    if (state->pressed) {
        op_layer_hold = true;
        layer_on(_SYMB);
        // How do i reset the layer after hold is finnished?
    }
    // Annars om vi har tryckt totalt 2 ggr på en knapp så skall vi toggla
    // lager. Kan bli lite fortare om vi sätter koden i den funktion som alltid
    // kallas på. För detta kommer att bara kallas på när vi har tryckt på en
    // annan knapp eller väntat TAPPING_TERM
    else if (state->count == 2) {
        // Toggles game layer. Only maked left thumb a space.
        // layer_state_is(_GAME) ? layer_off(_GAME) : layer_on(_GAME);
        if (layer_state_is(_GAME)) {
            print("turning off _GAME");
            layer_off(_GAME);
        } else {
            print("turning on _GAME");
            layer_on(_GAME);
        }
    }
}

// Called when tap_dance is ended (key is released after hold)
void op_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    // How do i tell the difference if i got there from a hold or a double
    // press? I could look if state is two, but i could still double press and
    // hold. Store in a variable if you need that information. But since i do
    // want to do the same thing every time, I do not need that. But I still
    // include it for future reference.
    print("op_layer_reset");
    op_layer_hold = false;
    layer_off(_NUMB);
    /*
    if(op_layer_hold)
    {
        layer_on();
    }
    */
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_F11]   = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F11),
    [TD_F12]   = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F12),
    [TD1F1]    = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1),
    [TD2F2]    = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_F2),
    [TD3F3]    = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),
    [TD4F4]    = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_F4),
    [TD5F5]    = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
    [TD6F6]    = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_F6),
    [TD7F7]    = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_F7),
    [TD8F8]    = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_F8),
    [TD9F9]    = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_F9),
    [TD0F10]   = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_F10),
    [CT_RESET] = ACTION_TAP_DANCE_FN(dance_reset),
    // The first function in the argument gets called on every keydown-press of
    // the specified key. The secound one is called when it is finished (timeout
    // or interrupted). The last one is called when the tapdance is reset (After
    // key is released after timeout (or interrupt)?)
    [OP_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, op_layer_finished, op_layer_reset),
};

// Shortcut to make keymap more readable
// #define SYM_L   MO(_SYMB)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_N_BSPC LT(_NUMB, KC_BSPC)
// #define KC_S_DEL LT(_SYMB, KC_DEL)
// #define KC_S_ENT LT(_SYMB, KC_ENT)

// #define KC_ADEN LT(_ADJUST, KC_END)
// #define KC_ADPU LT(_ADJUST, KC_PGUP)
#define OP_F1 TD(TD_F11)
#define OP_F2 TD(TD_F12)
#define OP_RESET TD(CT_RESET)
#define OP_LAY TD(OP_LAYER)
#define OP_SPC LT(_NUMB, KC_SPC)
#define OP_LCTRL OSM(MOD_LCTL)
#define OP_LSFT OSM(MOD_LSFT)
#define OP_RSFT OSM(MOD_RSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
      [_QWERTY] = LAYOUT(
      //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
         KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_K   ,                           KC_A   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,SE_ARNG  ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,SE_ODIA ,SE_ADIA ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
      //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
         KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_ALAS ,     KC_CTPL ,    KC_BSPC ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
      //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
      ),
    */

    // LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F),

    // RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN)

    [_QWERTY] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, SE_1, SE_2, SE_3, SE_4, SE_5, SE_6, SE_7, SE_8, SE_9, SE_0, SE_PLUS,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB, SE_Q, SE_W, SE_E, SE_R, SE_T, _______, KC_PSCREEN, SE_Y, SE_U, SE_I, SE_O, SE_P, SE_ARNG,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_ESC, LCTL_T(KC_A), LSFT_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F), SE_G, OP_LAY, OP_LAY, SE_H, RGUI_T(KC_J), RALT_T(KC_K), LSFT_T(KC_L), RCTL_T(SE_ODIA), SE_ADIA,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT, SE_Z, SE_X, SE_C, SE_V, SE_B, KC_LGUI, _______, DM_REC1, KC_LGUI, SE_N, SE_M, SE_COMM, SE_DOT, SE_MINS, KC_RSFT,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        KC_LCTRL, MO(_MEDIA), KC_LGUI, _______, KC_LALT, KC_BSPC, KC_DEL, KC_ENT, OP_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_QWERTY] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        //_______ ,SE_1    ,SE_2    ,SE_3    ,SE_4    ,SE_5    ,                                            SE_6    ,SE_7    ,SE_8    ,SE_9    ,SE_0    ,SE_PLUS ,
        _______, SE_EXLM, SE_DQUO, SE_HASH, SE_DLR, SE_PERC, SE_AMPR, SE_SLSH, SE_BSLS, SE_QUOT, SE_EQL, SE_QUES,
        //_______ ,_______ ,_______ ,_______ ,_______ ,_______    ,                                          _______ ,_______ ,_______ ,_______ ,_______ ,_______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB, SE_Q, SE_W, SE_E, SE_R, SE_T, _______, KC_PSCREEN, SE_Y, SE_U, SE_I, SE_O, SE_P, SE_ARNG,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        // KC_ESC,LCTL_T(KC_A),LSFT_T(KC_S),LALT_T(KC_D),LGUI_T(KC_F) ,SE_G    ,OP_LAY,OP_LAY,  SE_H,RGUI_T(KC_J), RALT_T(KC_K), LSFT_T(KC_L), RCTL_T(SE_ODIA),SE_ADIA ,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, SE_G, OP_LAY, OP_LAY, SE_H, KC_J, KC_K, KC_L, SE_ODIA, SE_ADIA,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT, SE_Z, SE_X, SE_C, SE_V, SE_B, KC_LGUI, _______, DM_REC1, KC_LGUI, SE_N, SE_M, SE_COMM, SE_DOT, SE_MINS, KC_RSFT,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        // KC_LCTRL,MO(_MEDIA),KC_LGUI,_______,     KC_LALT ,    KC_N_BSPC,KC_S_DEL,      KC_S_ENT  ,OP_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
        KC_LCTRL, MO(_MEDIA), KC_LGUI, _______, KC_LALT, KC_N_BSPC, KC_DEL, KC_ENT, OP_SPC, KC_RALT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    //&/()=@${[]}\+  \/?#!"'%&
    // tilde och hat och hubsh punkter
    /*
    [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,OP_F1   ,OP_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼──┐                               ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,SE_AT  ,SE_LBRC ,SE_RBRC ,SE_CIRC ,OP_RESET ,                         _______ ,_______ ,SE_QUOT, SE_DQUO,SE_CIRC, SE_TILD,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,SE_LABK ,SE_RABK ,SE_LPRN ,SE_RPRN ,SE_PIPE ,_______ ,                          _______ ,_______ ,SE_BSLS ,SE_SLSH ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ , _______,SE_LCBR ,SE_RCBR ,SE_AT ,_______ ,_______ ,        _______ ,_______ ,_______ ,SE_GRV , SE_ACUT ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
*/
    [_NUMB] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, OP_F1, OP_F2, KC_F3, KC_F4, KC_F5, KC_F6, SE_ACUT, SE_GRV, KC_F9, KC_F10, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼──┐                               ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, SE_AT, SE_LBRC, SE_RBRC, SE_CIRC, OP_RESET, KC_NUMLOCK, SE_TILD, KC_7, KC_8, KC_9, SE_PLUS, SE_MINS,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, SE_LABK, SE_RABK, SE_LPRN, SE_RPRN, SE_PIPE, _______, _______, _______, KC_4, KC_5, KC_6, SE_ASTR, SE_SLSH,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, SE_LCBR, SE_RCBR, _______, _______, _______, DM_PLY1, _______, _______, KC_1, KC_2, KC_3, SE_EQL, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_GAME] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_ESC, TD(TD1F1), TD(TD2F2), TD(TD3F3), TD(TD4F4), TD(TD5F5), TD(TD6F6), TD(TD7F7), TD(TD8F8), TD(TD9F9), TD(TD0F10), _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_A, KC_S, KC_D, KC_F, _______, _______, _______, _______, KC_J, KC_K, KC_L, SE_ODIA, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        KC_LCTRL, _______, _______, _______, KC_SPC, KC_SPC, KC_LALT, KC_ENT, _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    //&/()=@${[]}\+  \/?#!"'%&
    // tilde och hat och hubsh punkter
    [_SYMB] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, OP_F1, OP_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼──┐                               ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, SE_AT, SE_LBRC, SE_RBRC, SE_CIRC, OP_RESET, _______, _______, SE_QUOT, SE_DQUO, SE_CIRC, SE_TILD, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, SE_LABK, SE_RABK, SE_LPRN, SE_RPRN, SE_PIPE, _______, _______, _______, SE_BSLS, SE_SLSH, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, SE_LCBR, SE_RCBR, SE_AT, _______, _______, _______, _______, _______, SE_GRV, SE_ACUT, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_SUDOKU] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, KC_Z, KC_X, KC_C, KC_V, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_1, KC_2, KC_3, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_7, KC_8, KC_9, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, KC_0, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_NAV] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_MS_U, _______, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_GAME] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_ESC, TD(TD1F1), TD(TD2F2), TD(TD3F3), TD(TD4F4), TD(TD5F5), TD(TD6F6), TD(TD7F7), TD(TD8F8), TD(TD9F9), TD(TD0F10), _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_A, KC_S, KC_D, KC_F, _______, _______, _______, _______, KC_J, KC_K, KC_L, SE_ODIA, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        KC_LCTRL, _______, _______, _______, KC_SPC, KC_SPC, KC_LALT, KC_ENT, _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        ),

    [_MEDIA] = LAYOUT(
        // ┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // ├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // └────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
        )

    /*
      [_SYMB] = LAYOUT(
      //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
         _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                          _______ ,KC_PSLS ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PMNS ,XXXXXXX ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,_______ ,                          _______ ,KC_PAST ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,XXXXXXX ,
      //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
         _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,XXXXXXX ,
      //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
         _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_P0 ,     KC_P0 ,KC_PDOT ,KC_PENT ,XXXXXXX
      //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
      ),
    */
    /*
  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,KC_WH_U ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,XXXXXXX ,_______ ,                          _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_BTN1 ,    KC_BTN2 ,_______ ,        _______ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),
  */

    /*[_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
    )*/
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    return true;
}
