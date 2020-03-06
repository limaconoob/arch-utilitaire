#ifndef GRAPHIQUES_H
  #define GRAPHIQUES_H

  #include <sys/types.h>

  #include "couleurs.h"
  #include "types.h"

  typedef struct point_pix
  { u_int x;
    u_int y;
    couleurs c;
  } point_pix;

  typedef struct rectangle
  { point_pix xy; // Coordonnées du coin en haut à gauche
    u_int w;
    u_int h;
  } rectangle;

  typedef struct cercle
  { point_pix xy; // Coordonnées du centre 
    u_int rayon;
  } cercle;

  typedef struct ligne
  { point_pix xy;
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
    Croix,
    Lune_Gauche,
    Lune_Droite,
    Lune_Haute,
    Lune_Basse,
    Coin_Bas_Gauche,
    Coin_Bas_Droite,
    Coin_Haut_Gauche,
    Coin_Haut_Droite,
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
  void dessin_rect(rectangle rect, pixels *fb);
  void dessin_pave(rectangle rect, pixels *fb);
  void dessin_ligne(ligne l, pixels *fb);
  void dessin_cercle(cercle c, pixels *fb);
  void dessin_disque(cercle c, pixels *fb);

  /// Ecriture de texte (voir display.h > font 7x9)
  void dessin7x9(extra_font c, couleurs fg, couleurs bg, u_int mx, u_int my, pixels *fb);
  void verre7x9(extra_font c, couleurs fg, u_int mx, u_int my, pixels *fb);
  void phrase_bande(u_char *str, u_int taille, couleurs fg, couleurs bg, u_int mx, u_int my, pixels *fb);
  draw depuis_icones7x9(extra_font c);

  /// Dessin indépendant
  void dessin_objet(u_int *objet, rectangle rect, pixels *fb);

#endif
