#ifndef NOYAU_CLAVIER_H
  #define NOYAU_CLAVIER_H

  u_char noyau_clavier[54] =
  { '\0', '\0', '&', '\0', '"', '\'', '(', '-', '\0', '_', '\0', '\0', ')', '=', '\0', '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$', '\n', '\0', 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '\0', '\0', '\0', '*', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!' };

  u_char noyau_shift_clavier[54] =
  { '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0', '+', '\0', '\t', 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '"', '\0', '\n', '\0', 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', '\0', '\0', '\0', 'W', 'X', 'C', 'V', 'B', 'N', '?', '.', '/', '\0' };

  u_char noyau_altgr_clavier[14] =
  { '\0', '\0', '\0', '~', '#', '{', '[', '|', '`', '\\', '^', '@', ']', '}' };

/*
#define KEY_SPACE		57
#define KEY_CAPSLOCK		58
#define KEY_NUMLOCK		69

// KeyPad
#define KEY_KP7			71
#define KEY_KP8			72
#define KEY_KP9			73
#define KEY_KPMINUS		74
#define KEY_KP4			75
#define KEY_KP5			76
#define KEY_KP6			77
#define KEY_KPPLUS		78
#define KEY_KP1			79
#define KEY_KP2			80
#define KEY_KP3			81
#define KEY_KP0			82
#define KEY_KPDOT		83
#define KEY_KPJPCOMMA		95
#define KEY_KPENTER		96
#define KEY_KPSLASH		98

// Flèches
#define KEY_UP			103
#define KEY_LEFT		105
#define KEY_RIGHT		106
#define KEY_DOWN		108

// ++
#define KEY_HOME		102
#define KEY_END			107
#define KEY_PAGEUP		104
#define KEY_PAGEDOWN		109
#define KEY_INSERT		110
#define KEY_DELETE		111
*/


#endif

