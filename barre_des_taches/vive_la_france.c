
#include "graphiques.h"
#include "pixel_objet.h" 

void vive_la_France(pixels *fb)
{ rectangle r = { ((*fb).w - 30), 19, 12, 9 };
  dessin_objet(drapeau_francais, r, fb);
  phrase_bande("Vive la France!", 15, Blanc, Noir, ((*fb).w - 160), 17, fb);
  }

