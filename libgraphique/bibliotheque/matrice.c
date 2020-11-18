
#include "graphiques.h"

void sauver_matrice(pixels *fb)
{ lseek((*fb).pix, 0, SEEK_SET);
  int i = 0;
  while (read((*fb).pix, (*fb).matrice[i], LARGEUR_PIXELS_FENETRE))
  { i += 1; }}

void charger_matrice(pixels *fb)
{ lseek((*fb).pix, 0, SEEK_SET);
  int i = 0;
  while (i < HAUTEUR_PIXELS_FENETRE)
  { write((*fb).pix, (*fb).matrice[i], LARGEUR_PIXELS_FENETRE);
    i += 1; }}


