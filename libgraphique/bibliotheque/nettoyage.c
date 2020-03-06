
#include <string.h>
#include <unistd.h>

#include "graphiques.h"
#include "types.h"

void nettoyage(couleurs couleur, pixels *fb)
{ u_short i = 0;
  if (couleur == Noir)
  { bzero((*fb).remplisseur, 1024 * sizeof(u_int));
    while (i < (*fb).h)
    { write((*fb).pix, (*fb).remplisseur, 1024 * sizeof(u_int));
      i += 1; }}
  else
  { point_pix pix = { 0, 0, couleur };
    rectangle r = { pix, (*fb).w, (*fb).h };
    dessin_pave(r, fb); }}

void toile_vierge(rectangle cadre, couleurs bords, couleurs fond, pixels *fb)
{ cadre.xy.c = fond;
  dessin_pave(cadre, fb);
  cadre.xy.c = bords;
  dessin_rect(cadre, fb); }

// cat /sys/class/graphics/fb0/virtual_size
