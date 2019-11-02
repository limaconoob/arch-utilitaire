
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "graphiques.h"
#include "taches.h"

pixels init_gui()
{ pixels fb;
  fb.pix = open("/dev/fb0", O_WRONLY | O_SYNC);
  fb.w = 1024;
  fb.h = 600;
  fb.shift = 0;
  return (fb); }

void tache_cachee()
{ pixels fb = init_gui();
  while (42)
  { gestion_batterie(&fb);
    gestion_horloge(&fb);
    gestion_internet(&fb);
    usleep(100000); }}

void pid_fantome()
{ pid_t pere;
  while (42)
  { pere = fork();
    if (pere > 0)
    { exit(0); }
    if (pere == 0)
    { setsid();
      tache_cachee(); }}
  wait((void*)0); }

int main(void)
{ pid_fantome();
  return (42); }

