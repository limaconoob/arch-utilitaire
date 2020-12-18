
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

static void tache_cachee()
{ pixels fb = init_gui();
  u_char segmenteur = 4;
  while (42)
  { gestion_horloge(&fb);
    gestion_internet(&fb);
    segmenteur += 1;
    if (segmenteur == 5)
    { gestion_batterie(&fb);
      vive_la_France(&fb);
      segmenteur = 0;}
    usleep(800000); }}

static void pid_fantome()
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

