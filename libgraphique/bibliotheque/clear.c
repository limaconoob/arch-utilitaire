
#include <string.h>
#include <unistd.h>

#include "graphiques.h"
#include "types.h"

void clear(pixels *fb)
{ u_short i = 0;
  u_int ligne[1024];
  bzero(ligne, 1024 * sizeof(u_int));
  while (i < (*fb).h)
  { write((*fb).pix, ligne, 1024 * sizeof(u_int));
    i += 1; }}

// cat /sys/class/graphics/fb0/virtual_size
