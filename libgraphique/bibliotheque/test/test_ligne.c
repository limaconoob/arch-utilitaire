
#include "../graphiques.h"

int main(void)
{ pixels fb = init_gui();
  int i = 0;
  ligne l = { 500, 300, 500, 100 };
  while (i <= 200)
  { l.x2 = i + 500;
    dessin_ligne(l, Rouge, &fb);
    i += 5; }
  i = 0;
  while (i <= 200)
  { l.y2 = i + 100;
    dessin_ligne(l, Vert, &fb);
    i += 5; }
  ligne k = { 500, 300, 500, 500 };
  i = 0;
  while (i <= 200)
  { k.x2 = i + 500;
    dessin_ligne(k, Cyan, &fb);
    i += 5; }
  i = 0;
  while (i <= 200)
  { k.y2 = i + 300;
    dessin_ligne(k, Jaune, &fb);
    i += 5; }
  ligne t = { 500, 300, 500, 500 };
  i = 0;
  while (i <= 200)
  { t.x2 = 500 - i;
    dessin_ligne(t, Violet, &fb);
    i += 5; }
  i = 0;
  while (i <= 200)
  { t.y2 = i + 300;
    dessin_ligne(t, Orange, &fb);
    i += 5; }
  ligne u = { 500, 300, 500, 100 };
  i = 0;
  while (i <= 200)
  { u.x2 = 500 - i;
    dessin_ligne(u, Magenta, &fb);
    i += 5; }
  i = 0;
  while (i <= 200)
  { u.y2 = i + 100;
    dessin_ligne(u, Gris, &fb);
    i += 5; }
 // ligne k = { 700, 200, 700, 400 };
 // dessin_ligne(k, Cyan, &fb);
 // ligne t = { 500, 200, 700, 400 };
 // dessin_ligne(t, Jaune, &fb);
/*
  ligne y = { 400, 300, 450, 302 };
  dessin_ligne(y, Bleu, &fb);
  ligne u = { 300, 300, 400, 400 };
  dessin_ligne(u, Jaune, &fb);
*/  
  }
