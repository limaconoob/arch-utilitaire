#ifndef GRAPHIQUES_H
  #define GRAPHIQUES_H

  #include <sys/types.h>

  #include "couleurs.h"
  #include "types.h"

  typedef struct rectangle
  { u_int x;
    u_int y;
    u_int w;
    u_int h;
  } rectangle;

  typedef struct cercle
  { u_int x;  // -,
    u_int y;  // -'-> Coordonnées du centre 
    u_int rayon;
  } cercle;

  typedef struct ligne
  { u_int x1;
    u_int y1;
    u_int x2;
    u_int y2;
  } ligne;

  typedef enum extra_font
  { smiley_chat,
    smiley_content,
    smiley_deception,
    smiley_surpris,
    smiley_neutre,
    limaconoob,
    usb_logo,
    wifi_logo,
    ethernet,
    Souris_Plus,
    Souris_Marqueur,
    Souris_Fleche,
    Souris_Doigt,
    gomme,
  } extra_font;

  typedef struct pixels
  { int pix; // descripteur de fichier
    off_t shift; // curseur au sein du tampon
    u_int w; // 1024
    u_int h; // 600
    u_int remplisseur[1024];
  } pixels;
  // u_int buf_copy[600][1024]; // copie de la matrice de pixels

  typedef enum Etat_Clavier
  { Shift_Droit = 0x01,
    Shift_Gauche = 0x02,
    AltGr = 0x04,
    Alt = 0x08,
    Controle_Droit = 0x10,
    Controle_Gauche = 0x20,
    Verrou_Majuscule = 0x40,
    Verrou_Pave_Numerique = 0x80,
  } Etat_Clavier;

  typedef struct peripherique
  { int clv; //1 seul clavier
    int srs; //1 seule souris
    u_int motion_x;
    u_int motion_y;
    extra_font icone_souris;
    couleurs pointeur;
    u_char etat_clavier;
    pthread_t canaux[2];
    pixels *fb;
  } peripherique;

  typedef enum bool_sauvegarde
  { Sauve,
    Charge,
  } bool_sauvegarde;

  typedef struct maitre_interface
  { pixels fb;
    peripherique periph;
  } maitre_interface;

  typedef struct point_pix
  { u_int x;
    u_int y;
    couleurs c;
  } point_pix;

  /// Initialisation de la surface graphique
  pixels init_gui(void);
  void avec_taille(pixels *fb, u_int w, u_int h);

  /// Création d'éléments
  point_pix creation_pixel(u_int x, u_int y, couleurs c);

  /// Nettoyage de l'interface
  void nettoyage(couleurs couleur, pixels *fb);
  void toile_vierge(rectangle cadre, couleurs bords, couleurs fond, pixels *fb);

  /// Dessin de formes et surfaces
  void dessin_pixel(point_pix p, pixels *fb);
  void dessin_rect(rectangle rect, couleurs couleur, pixels *fb);
  void dessin_pave(rectangle rect, couleurs couleur, pixels *fb);
  void dessin_ligne(ligne l, couleurs couleur, pixels *fb);
  void dessin_cercle(cercle c, couleurs couleur, pixels *fb);

  /// Ecriture de texte (voir display.h > font 7x9)
  void dessin7x9(extra_font c, couleurs fg, couleurs bg, u_int mx, u_int my, pixels *fb);
  void verre7x9(extra_font c, couleurs fg, u_int mx, u_int my, pixels *fb);
  void phrase_bande(u_char *str, u_int taille, couleurs fg, couleurs bg, u_int mx, u_int my, pixels *fb);

  /// Dessin indépendant
  void dessin_objet(u_int *objet, rectangle rect, pixels *fb);

  /// Gestion des périphériques entrants
  peripherique init_periph(pixels *fb);

#endif
