
#include "graphiques.h"

void init_prog()
{ pixels fb = init_gui();
  rectangle cadre = { 600, 200, 300, 100 };
  fenetre fen = init_fen(cadre, 0, &fb);
  
  }

