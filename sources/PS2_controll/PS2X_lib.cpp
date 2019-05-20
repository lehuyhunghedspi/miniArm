#include "PS2X_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#if ARDUINO > 22
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
#endif

static byte enter_config[]={0x01,0x43,0x00,0x01,0x00};
static byte set_mode[]={0x01,0x44,0x00,0x01,0x03,0x00,0x00,0x00,0x00};
static byte set_bytes_large[]={0x01,0x4F,0x00,0xFF,0xFF,0x03,0x00,0x00,0x00};
static byte exit_config[]={0x01,0x43,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A};
static byte enable_rumble[]={0x01,0x4D,0x00,0x00,0x01};
static byte type_read[]={0x01,0x45,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};

/****************************************************************************************/
boolean PS2X::NewButtonState() {
  return ((last_buttons ^ buttons) > 0);
}

/****************************************************************************************/
boolean PS2X::NewButtonState(unsigned int button) {
  return (((last_buttons ^ buttons) & button) > 0);
}

/****************************************************************************************/
boolean PS2X::ButtonPressed(unsigned int button) {
  return(NewButtonState(button) & Button(button));
}

/****************************************************************************************/
boolean PS2X::ButtonReleased(unsigned int button) {
  return((NewButtonState(button)) & ((~last_buttons & button) > 0));
}

/****************************************************************************************/
boolean PS2X::Button(uint16_t button) {
  return ((~buttons & button) > 0);
}

/****************************************************************************************/
unsigned int PS2X::ButtonDataByte() {
   return (~buttons);
}

/****************************************************************************************/
byte PS2X::Analog(byte button) {
   return PS2data[button];
}

/****************************************************************************************/


inline bool PS2X::DAT_CHK(void) {
  return (*_dat_ireg & _dat_mask) ? true : false;
}

#else
// On pic32, use the set/clr registers to make them atomic...
inline void  PS2X::CLK_SET(void) {
  *_clk_lport_set |= _clk_mask;
}

inline void  PS2X::CLK_CLR(void) {
  *_clk_lport_clr |= _clk_mask;
}

inline void  PS2X::CMD_SET(void) {
  *_cmd_lport_set |= _cmd_mask;
}

inline void  PS2X::CMD_CLR(void) {
  *_cmd_lport_clr |= _cmd_mask;
}

inline void  PS2X::ATT_SET(void) {
  *_att_lport_set |= _att_mask;
}

inline void PS2X::ATT_CLR(void) {
  *_att_lport_clr |= _att_mask;
}

inline bool PS2X::DAT_CHK(void) {
  return (*_dat_lport & _dat_mask) ? true : false;
}

#endif
