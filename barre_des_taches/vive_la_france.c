
#include "graphiques.h"
#include "pixel_objet.h" 

void vive_la_France(pixels *fb)
{ point_pix pix = { ((*fb).w - 30), 18, Noir };
  rectangle r = { pix, 12, 9 };
  dessin_objet(drapeau_francais, r, fb);
  phrase_bande("Vive la France!", 15, Blanc, Noir, ((*fb).w - 160), 17, fb);
  dessin7x9(limaconoob, Magenta, Noir, ((*fb).w - 30), 32, fb);
  phrase_bande("Limaconoob", 10, Cyan, Noir, ((*fb).w - 120), 32, fb);
  }

