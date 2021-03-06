#ifndef PERIPHERIQUES_H
  #define PERIPHERIQUES_H

  #include "graphiques.h"

  #define SOCK_PATH "/home/arch-utilitaire/gestionnaire_de_fenetres/daemon/.sock/"

  enum Periph_ON
  { Souris_ON = 0b0001,
    Clavier_ON = 0b0010,
    Joystick_ON = 0b0100,
    UART_ON = 0b1000 };

  enum Evenement_Input
  { Bouton_Maintien = 0b00000000,
    Bouton_Appui = 0b00000001,
    Bouton_Relache = 0b00000010,
    Motion_Relatif = 0b00000100,
    Motion_Absolu = 0b00001000,
    Souris_Motion = 0b00001100,
    Bouton_Action = 0b00000011,
    Souris_PRET = 0b00010000,
    Clavier_PRET = 0b00100000,
    Joystick_PRET = 0b01000000,
    UART_PRET = 0b10000000 };

  enum Bouton_Souris
  { Bouton_Souris_Gauche = 0b00000001,
    Bouton_Souris_Droit = 0b00000010,
    Bouton_Souris_Molette = 0b00000100,
    Molette_Haut = 0b00001000,
    Molette_Bas = 0b00010000,
    Bouton_Souris_Annexe = 0b11100000 };

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
    u_char dernier_clic;
    extra_font icone_souris;
    couleurs pointeur;
    int fd;
    pthread_t canal;
  } souris;

  typedef struct peripherique
  { clavier clv;
    souris srs;
    u_char pret;
    pid_t pid; // PID du processus appelant
    pixels *fb;
  } peripherique;

  /// Gestion des périphériques
  peripherique init_periph(pid_t pid, pixels *fb);
  void init_souris(peripherique *periph);
  void init_clavier(peripherique *periph);

  int attache_entrees(int masque);
  void prochaine_entree(int fd);
  void debug(int fd);

#endif

