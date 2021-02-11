
#include <unistd.h>

#include "graphiques.h"
#include "couleurs.h"

int main()
{ pixels fb = init_gui();
  while (42)
  { nettoyage(Blanc, &fb);
    sleep(1);
    nettoyage(Noir, &fb);
    sleep(1); }}


