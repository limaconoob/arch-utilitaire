
#include <stdlib.h>
#include <strings.h>

#include "fenetre.h"
#include "graphiques.h"

ascenceur init_asc(flags_fenetre info)
{ ascenceur asc;
  asc.reduit = info & Reduit;
  asc.vertical = info & Vertical >> 1;
  asc.position = info & Position >> 2;
  asc.navette = Violet;
  asc.tube = Gris;
  return (asc); }

fenetre init_fen(rectangle cadre, flags_fenetre info, pixels *fb)
{ fenetre fen;
  pixels couche;
  fen.reduit = info & Reduit;
  fen.plein_ecran = info & Plein_Ecran >> 1;
  fen.le_tty = info & Tty >> 2;
  fen.asc[0] = init_asc(Vertical | Droite);
  rectangle tube = { cadre.x + cadre.w - 11, cadre.y + 1, 10, cadre.h - 2 };
  dessin_pave(tube, Gris, fb);
  rectangle navette = { cadre.x + cadre.w - 11, cadre.y + 1, 10, 40 }; // Valeurs arbitraires
  dessin_pave(tube, Violet, fb);
  bzero(&(fen.asc[1]), sizeof(ascenceur));

  int y = 0;
  fen.tableau_pixels = (u_int**)malloc((*fb).h * sizeof(u_int*));
  while (y < (*fb).h)
  { fen.tableau_pixels[y] = (u_int*)malloc((*fb).w * sizeof(u_int));
    y += 1; }

  fen.x = cadre.x;
  fen.y = cadre.y;
  couche.pix = (*fb).pix;
  couche.shift = 0;
  couche.w = cadre.w;
  couche.h = cadre.h;
  fen.fb = couche;
  fen.bords = Blanc;
  fen.fond = Noir;
  toile_vierge(cadre, Blanc, Noir, fb);
  return (fen); }



