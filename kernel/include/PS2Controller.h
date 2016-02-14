//
//  PS2Controller.h
//  OS
//
//  Created by Adam Kopeć on 2/12/16.
//  Copyright © 2016 Adam Kopeć. All rights reserved.
//


//  Totally unusable

#ifndef PS2Controller_h
#define PS2Controller_h

#include <sys/cdefs.h>

#define NULL_KEY    0x00
#define ESC_KEY     0x1B
#define LSHIFT_KEY  0x80
#define LCTRL_KEY   0x81
#define RCTRL_KEY   0x82
#define LALT_KEY    0x83
#define RALT_KEY    0x84
#define CAPS_KEY    0x85
#define NUM_KEY     0x86
#define SCROLL_KEY  0x87
#define PAUSE_KEY   0x88
#define F1_KEY      0x89
#define F2_KEY      0x8A
#define F3_KEY      0x8B
#define F4_KEY      0x8C
#define F5_KEY      0x8D
#define F6_KEY      0x8E
#define F7_KEY      0x8F
#define F8_KEY      0x90
#define F9_KEY      0x91
#define F10_KEY     0x92
#define F11_KEY     0x93
#define F12_KEY     0x94
#define RSHIFT_KEY  0x95

int pollchar();


#endif /* PS2Controller_h */