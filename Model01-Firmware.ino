// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Mine
#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Escape-OneShot.h>
#include <Kaleidoscope-LED-ActiveModColor.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum
{
  MACRO_VERSION_INFO
};

/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum
{
  PRIMARY,
  MAC,
  GAMING,
  FUNCTION
}; // layers

/**
  * To change your keyboard's layout from QWERTY to DVORAK or COLEMAK, comment out the line
  *
  * #define PRIMARY_KEYMAP_QWERTY
  *
  * by changing it to
  *
  * // #define PRIMARY_KEYMAP_QWERTY
  *
  * Then uncomment the line corresponding to the layout you want to use.
  *
  */

#define PRIMARY_KEYMAP_CUSTOM

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

#elif defined(PRIMARY_KEYMAP_CUSTOM)
    // Edit this keymap to make a custom layout
    [PRIMARY] = KEYMAP_STACKED(Key_LeftGui, Key_1, Key_2, Key_3, Key_4, Key_5, LSHIFT(Key_9),
                               Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_LeftBracket,
                               Key_Backslash, Key_A, Key_S, Key_D, Key_F, Key_G,
                               OSM(LeftAlt), Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
                               OSM(LeftControl), Key_Tab, Key_Backspace, OSM(LeftShift),
                               ShiftToLayer(FUNCTION),

                               LSHIFT(Key_0), Key_6, Key_7, Key_8, Key_9, Key_0, LCTRL(Key_F5),
                               Key_RightBracket, Key_Y, Key_U, Key_I, Key_O, Key_P, Key_Equals,
                               Key_H, Key_J, Key_K, Key_L, Key_Semicolon, Key_Quote,
                               LSHIFT(LALT(LCTRL(Key_LeftGui))), Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_Minus,
                               OSM(LeftShift), OSM(LeftAlt), Key_Spacebar, OSM(LeftControl),
                               ShiftToLayer(FUNCTION)),

#else

#error "No default keymap defined. You should make sure that you have a line like '#define PRIMARY_KEYMAP_QWERTY' in your sketch"

#endif

    [MAC] = KEYMAP_STACKED(OSM(LeftControl), Key_1, Key_2, Key_3, Key_4, Key_5, LSHIFT(Key_9),
                           Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_LeftBracket,
                           Key_Backslash, Key_A, Key_S, Key_D, Key_F, Key_G,
                           OSM(LeftAlt), Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
                           OSM(LeftGui), Key_Tab, Key_Backspace, OSM(LeftShift),
                           ShiftToLayer(FUNCTION),

                           LSHIFT(Key_0), Key_6, Key_7, Key_8, Key_9, Key_0, LGUI(LSHIFT(Key_R)),
                           Key_RightBracket, Key_Y, Key_U, Key_I, Key_O, Key_P, Key_Equals,
                           Key_H, Key_J, Key_K, Key_L, Key_Semicolon, Key_Quote,
                           LSHIFT(LALT(LCTRL(Key_LeftGui))), Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_Minus,
                           OSM(LeftShift), OSM(LeftAlt), Key_Spacebar, OSM(LeftGui),
                           ShiftToLayer(FUNCTION)),

    [GAMING] = KEYMAP_STACKED(Key_LeftGui, Key_1, Key_2, Key_3, Key_4, Key_5, LCTRL(Key_9),
                              Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_LeftBracket,
                              Key_Backslash, Key_A, Key_S, Key_D, Key_F, Key_G,
                              Key_LeftAlt, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
                              Key_LeftControl, Key_Tab, Key_Backspace, Key_LeftShift,
                              ShiftToLayer(FUNCTION),

                              LSHIFT(Key_0), Key_6, Key_7, Key_8, Key_9, Key_0, LCTRL(Key_F5),
                              Key_RightBracket, Key_Y, Key_U, Key_I, Key_O, Key_P, Key_Equals,
                              Key_H, Key_J, Key_K, Key_L, Key_Semicolon, Key_Quote,
                              LSHIFT(LALT(LCTRL(Key_LeftGui))), Key_N, Key_M, Key_Comma, Key_Period, Key_Slash, Key_Minus,
                              Key_LeftShift, Key_LeftAlt, Key_Spacebar, Key_LeftControl,
                              ShiftToLayer(FUNCTION)),

    [FUNCTION] = KEYMAP_STACKED(LSHIFT(Key_Delete), Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, LCTRL(Key_Insert),
                                ___, ___, ___, ___, ___, ___, Key_Home,
                                ___, LockLayer(MAC), ___, ___, ___, LockLayer(GAMING),
                                Key_LEDEffectNext, ___, ___, ___, ___, ___, Key_PageUp,
                                ___, Key_Enter, Key_Delete, Key_Spacebar,
                                ___,

                                LSHIFT(Key_Insert), Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
                                Key_End, Consumer_ScanPreviousTrack, Consumer_Stop, Consumer_PlaySlashPause, Consumer_ScanNextTrack, ___, Key_F12,
                                Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, ___, ___,
                                Key_PageDown, Consumer_Mute, Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___, ___, System_Sleep,
                                Key_CapsLock, Key_PcApplication, Key_Enter, ___,
                                ___))

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState)
{
  if (keyToggledOn(keyState))
  {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState)
{
  switch (macroIndex)
  {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  }
  return MACRO_NONE;
}

static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event)
{
  switch (event)
  {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.paused = true;
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event)
{
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum
{
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index)
{
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index)
{
  HardwareTestMode.runTests();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
    // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
    // editable keymap in EEPROM.
    EEPROMSettings,
    EEPROMKeymap,

    // Focus allows bi-directional communication with the host, and is the
    // interface through which the keymap in EEPROM can be edited.
    Focus,

    // FocusSettingsCommand adds a few Focus commands, intended to aid in
    // changing some settings of the keyboard, such as the default layer (via the
    // `settings.defaultLayer` command)
    FocusSettingsCommand,

    // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
    // both debugging, and in backing up one's EEPROM contents.
    FocusEEPROMCommand,

    // The boot greeting effect pulses the LED button for 10 seconds after the
    // keyboard is first connected
    BootGreetingEffect,

    // The hardware test mode, which can be invoked by tapping Prog, LED and the
    // left Fn button at the same time.
    HardwareTestMode,

    // LEDControl provides support for other LED modes
    LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    solidBlue,
    LEDOff,

    // The LED Palette Theme plugin provides a shared palette for other plugins,
    // like Colormap below
    LEDPaletteTheme,

    // The Colormap effect makes it possible to set up per-layer colormaps
    ColormapEffect,

    // The macros plugin adds support for macros
    Macros,

    // The HostPowerManagement plugin allows us to turn LEDs off when then host
    // goes to sleep, and resume them when it wakes up.
    HostPowerManagement,

    // The MagicCombo plugin lets you use key combinations to trigger custom
    // actions - a bit like Macros, but triggered by pressing multiple keys at the
    // same time.
    MagicCombo,

    // The USBQuirks plugin lets you do some things with USB that we aren't
    // comfortable - or able - to do automatically, but can be useful
    // nevertheless. Such as toggling the key report protocol between Boot (used
    // by BIOSes) and Report (NKRO).
    USBQuirks,

    // Mine
    OneShot,
    EscapeOneShot,
    ActiveModColorEffect);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup()
{
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  solidBlue.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(5);

  // Mine
  ActiveModColorEffect.highlight_color = CRGB(0x00, 0xff, 0xff);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop()
{
  Kaleidoscope.loop();
}
