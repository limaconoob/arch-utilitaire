#ifndef PERIPHERIQUES_H
  #define PERIPHERIQUES_H

  #include "graphiques.h"

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
    pthread_t canal;
  } clavier;

  typedef struct souris
  { u_int motion_x;
    u_int motion_y;
    extra_font icone_souris;
    couleurs pointeur;
    int fd;
    pthread_t canal;
  } souris;

  typedef struct peripherique
  { clavier clv;
    souris srs;
    pid_t pid; // PID du processus appelant
    pixels *fb;
  } peripherique;

  /// Gestion des périphériques
  peripherique init_periph(pid_t pid, pixels *fb);
  void init_souris(peripherique *periph);
  void init_clavier(peripherique *periph);

#endif

