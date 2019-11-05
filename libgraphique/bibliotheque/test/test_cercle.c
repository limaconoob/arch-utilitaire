
#include "../graphiques.h"

int main(void)
{ pixels fb = init_gui();
  cercle c = { 300, 150, 100 };
  dessin_cercle(c, Violet, &fb);
  c.rayon = 10;
  dessin_cercle(c, Cyan, &fb);
  c.x = 400;
  c.rayon = 90;
  dessin_cercle(c, Rouge, &fb);
  }

