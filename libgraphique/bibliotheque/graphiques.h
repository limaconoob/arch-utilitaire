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

  typedef
  enum Inputs
  { ///Fra Inputs essentiels
    Faineant = 0,
    Fl_Haut = 1,
    Fl_Bas = 2,
    Fl_Gauche = 3,
    Fl_Droite = 4,
    MoletteHaut = 5,
    MoletteBas = 6,
    ClicGauche = 7,
    ClicDroit = 8,
    ClicMolette = 9,
    Controle = 10,
    Shift = 11,
    Alt = 12,
    AltGr = 13,
    OptWin = 14,
    Fn = 15,
    RelGauche = 16,
    RelDroit = 17,
    RelMolette = 18,
    RelControle = 19,
    RelShift = 20,
    RelAlt = 21,
    RelAltGr = 22,
    RelOptWin = 23,
    RelFn = 24,
    Motion = 65533,
    Echap = 65534,
  } Inputs;

  /// Initialisation de la surface graphique
  pixels init_gui(void);
  void avec_taille(pixels *fb, u_int w, u_int h);

  /// Nettoyage de l'interface
  void nettoyage(couleurs couleur, pixels *fb);
  void toile_vierge(rectangle cadre, couleurs bords, couleurs fond, pixels *fb);

  /// Dessin de formes et surfaces
  void dessin_rect(rectangle rect, couleurs couleur, pixels *fb);
  void dessin_pave(rectangle rect, couleurs couleur, pixels *fb);
  void dessin_ligne(ligne l, couleurs couleur, pixels *fb);
  void dessin_cercle(cercle c, couleurs couleur, pixels *fb);

  /// Ecriture de texte (voir display.h > font 7x9)
  void dessin7x9(extra_font c, couleurs fg, couleurs bg, pixels *fb);
  void verre7x9(extra_font c, couleurs fg, pixels *fb);
  void phrase_bande(u_char *str, u_int taille, couleurs fg, couleurs bg, pixels *fb);

#endif
