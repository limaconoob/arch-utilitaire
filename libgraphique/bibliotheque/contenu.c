
#include "graphiques.h"
#include <stdio.h>

void contenu_ligne(ligne l)
{ printf("LIGNE! XY1(%lu, %lu), XY2(%lu, %lu), COULEUR::", l.xy.x, l.xy.y, l.x2, l.y2);
  quelle_couleur(l.xy.c);
  printf("\n"); }

void contenu_rectangle(rectangle r)
{ printf("RECTANGLE! COIN_HG(%lu, %lu), LH(%lu, %lu), COULEUR::", r.xy.x, r.xy.y, r.w, r.h);
  quelle_couleur(r.xy.c);
  printf("\n"); }

void contenu_cercle(cercle c)
{ printf("CERCLE! CEN_XY(%lu, %lu), RAYON::%lu, COULEUR::", c.xy.x, c.xy.y, c.rayon);
  quelle_couleur(c.xy.c);
  printf("\n"); }

void quelle_couleur(couleurs c)
{ if (c == 0x00009F00)
  { printf("Vert"); }
  else if (c == 0x00009F9F)
  { printf("Cyan"); }
  else if (c == 0x0000009F)
  { printf("Bleu"); }
  else if (c == 0x00000000)
  { printf("Noir"); }
  else if (c == 0x009F9F00)
  { printf("Jaune"); }
  else if (c == 0x009F5F2F)
  { printf("Orange"); }
  else if (c == 0x009F0000)
  { printf("Rouge"); }
  else if (c == 0x009F009F)
  { printf("Magenta"); }
  else if (c == 0x005F5F5F)
  { printf("Gris"); }
  else if (c == 0x005F2F9F)
  { printf("Violet"); }
  else if (c == 0x00F183B4)
  { printf("Rose"); }
  else if (c == 0x009F9F9F)
  { printf("Blanc"); }
  else if (c == 0xFF000000)
  { printf("Transparent"); }
}

