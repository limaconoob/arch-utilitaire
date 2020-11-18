
#include "../graphiques.h"
#include <stdio.h>

int main(void)
{ pixels fb = init_gui();
  cercle c = { 700, 250, Rouge, 110 };
  contenu_cercle(c);
  printf("ARC::(20, 120)\n\n");
  dessin_arc(c, 20.0, 120.0, &fb);
  c.xy.c = Rose;
  c.rayon = 100;
  contenu_cercle(c);
  printf("ARC::(120, 180)\n\n");
  dessin_arc(c, 120.0, 180.0, &fb);
  c.xy.c = Bleu;
  c.rayon = 90;
  contenu_cercle(c);
  printf("ARC::(5, 15)\n\n");
  dessin_arc(c, 5.0, 15.0, &fb);
  c.xy.c = Gris;
  c.rayon = 80;
  contenu_cercle(c);
  printf("ARC::(120, 240)\n\n");
  dessin_arc(c, 120.0, 240.0, &fb);
  c.xy.c = Blanc;
  c.rayon = 70;
  contenu_cercle(c);
  printf("ARC::(50, 340)\n\n");
  dessin_arc(c, 50.0, 340.0, &fb);
  c.xy.c = Rouge;
  c.rayon = 60;
  dessin_arc(c, 0.0, 90.0, &fb);
  c.xy.c = Bleu;
  dessin_arc(c, 90.0, 180.0, &fb);
  c.xy.c = Vert;
  dessin_arc(c, 180.0, 270.0, &fb);
  c.xy.c = Jaune;
  dessin_arc(c, 270.0, 360.0, &fb);
  ligne l = { 550, 250, Vert, 850, 250 };
  ligne k = { 700, 100, Cyan, 700, 400 };
  dessin_ligne(l, &fb);
  dessin_ligne(k, &fb);
  cercle ext = { 700, 250, Jaune, 120 };
  dessin_cercle(ext, &fb);
  }
