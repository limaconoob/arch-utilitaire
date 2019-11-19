
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
  { rectangle r = { 0, 0, (*fb).w, (*fb).h };
    dessin_pave(r, couleur, fb); }}

void toile_vierge(rectangle cadre, couleurs bords, couleurs fond, pixels *fb)
{ dessin_pave(cadre, fond, fb);
  dessin_rect(cadre, bords, fb); }

// cat /sys/class/graphics/fb0/virtual_size
