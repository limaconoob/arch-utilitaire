#ifndef PERIPHERIQUES_H
  #define PERIPHERIQUES_H

  #include "couleurs.h"
  #include "graphiques.h"
  #include "types.h"

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

  typedef enum bool_sauvegarde
  { Sauve,
    Charge,
  } bool_sauvegarde;

  typedef enum Etat_Clavier
  { Shift_Droit = 0b10000000,
    Shift_Gauche = 0b01000000,
    Shift = 0b11000000,
    AltGr = 0b00100000,
    Alt = 0b00010000,
    Controle_Droit = 0b00001000,
    Controle_Gauche = 0b00000100,
    Controle = 0b00001100,
    Verrou_Majuscule = 0b00000010,
    Verrou_Pave_Numerique = 0b00000001,
  } Etat_Clavier;

  typedef struct clavier
  { u_char flag_persistant; //0b shift_drt shift_gch altgr alt ctrl_drt ctrl_gch ver_maj ver_num
    u_int derniere_touche;
    u_int queue[42]; //il faut inclure les accents
    int fd;
  } clavier;

  typedef struct souris
  { u_int motion_x;
    u_int motion_y;
    extra_font icone_souris;
    couleurs pointeur;
    int fd;
  } souris;

  typedef struct peripherique
  { clavier clv;
    souris srs;
    pthread_t canaux[2];
    pixels *fb;
  } peripherique;

  /// Gestion des périphériques entrants
  peripherique init_periph(pixels *fb);

#endif

