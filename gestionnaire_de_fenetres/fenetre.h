#ifndef FENETRE_H
  #define FENETRE_H

  #include "graphiques.h"

  typedef enum flags_fenetre
  { Plein_Ecran = 0x01,
    Vertical = 0x01,
    Reduit = 0x02,
    Position = 0x0C,
    Tty = 0xFC,
  } flags_fenetre;

  typedef enum position
  { Droite = 0b0000,
    Gauche = 0b0100,
    Bas = 0b1000,
    Haut = 0b1100,
  } position;

  typedef struct __attribute__((__packed__)) ascenceur
  { unsigned reduit :1;
    unsigned vertical :1; // 0:horizontal 1:vertical
    unsigned position :2;
    couleurs navette;
    couleurs tube;
  } ascenceur;

  typedef struct __attribute__((__packed__)) fenetre
  { unsigned reduit :1;
    unsigned plein_ecran :1; // Dépend fortement de x.y.w.h
    unsigned le_tty :6; // des tty de 2 jusqu'à 64
    ascenceur asc[2];
    u_char queue; // Position dans la liste de fenêtres
    pixels fb; // Taille modulable
    u_int **tableau_pixels;
    u_int x; //-,
    u_int y; //-'-> Coordonnées dans fb0 (en pixel)
    couleurs bords;
    couleurs fond;
    struct fenetre *suivante;
    struct fenetre *precedente;
  } fenetre;

  /// Initialisation des fenêtres
  fenetre init_fen(rectangle cadre, flags_fenetre info, pixels *fb);
  ascenceur init_asc(flags_fenetre info);

#endif

