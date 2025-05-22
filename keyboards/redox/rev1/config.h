/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

#pragma once


#define MOUSEKEY_INTERVAL 16

#define MOUSEKEY_DELAY 0

#define MOUSEKEY_TIME_TO_MAX 60

#define MOUSEKEY_MAX_SPEED 5

#define MOUSEKEY_WHEEL_DELAY 0

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4D44  // "MD"
#define PRODUCT_ID 0x5244 // "RD"
#define DEVICE_VER 0x0100
#define MANUFACTURER Oskar Corperation
#define PRODUCT The Redox Keyboard
#define DESCRIPTION Split Ergodox - like 5x7 custom keyboard
#define SPLIT_HAND_PIN F4
#define TAPPING_TERM 200

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

// wiring of each half
#define MATRIX_COL_PINS_RIGHT \
    { B5, B4, E6, D7, C6, D4, F6 }
#define MATRIX_ROW_PINS_RIGHT \
    { F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS \
    { F6, D4, C6, D7, B4, E6, B5 }
#define MATRIX_ROW_PINS \
    { B2, B6, B3, B1, F7 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
// #define SOFT_SERIAL_PIN D0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
// #define RGB_DI_PIN D3

// #define RGBLED_NUM 14    // Number of LEDs

// #define RGBLIGHT_SPLIT   // sync LEDs between RIGHT and LEFT hand

#define USE_I2C
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION

#define ONESHOT_TAP_TOGGLE 50 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
