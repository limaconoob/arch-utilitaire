
#include <fcntl.h>
#include <sys/types.h>

#include "graphiques.h"

pixels init_gui(void)
{ pixels fb;
  fb.pix = open("/dev/fb0", O_WRONLY | O_SYNC);
  fb.w = 1024;
  fb.h = 600;
  fb.shift = 0;
  return (fb); }
