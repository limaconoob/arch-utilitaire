
#include "../graphiques.h"

int main(void)
{ pixels fb = init_gui();
  cercle c = { 300, 150, Violet, 100 };
  dessin_cercle(c, &fb);
  c.xy.c = Rose;
  dessin_disque(c, &fb);
  c.xy.c = Cyan;
  c.rayon = 16;
  dessin_cercle(c, &fb);
  c.xy.c = Bleu;
  dessin_disque(c, &fb);
  c.xy.c = Rouge;
  c.xy.x = 400;
  c.rayon = 90;
  dessin_cercle(c, &fb);
  c.xy.c = Jaune;
  dessin_disque(c, &fb);
  }

