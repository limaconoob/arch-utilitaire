
#include <fcntl.h>
#include <sys/types.h>

#include "graphiques.h"

pixels init_gui(void)
{ pixels fb;
  fb.pix = open("/dev/fb0", O_RDWR | O_SYNC);
  fb.w = 1024;
  fb.h = 600;
  fb.shift = 0;
  return (fb); }

void avec_taille(pixels *fb, u_int w, u_int h)
{ (*fb).w = w;
  (*fb).h = h;
  (*fb).shift = 0; }
