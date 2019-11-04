
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "couleurs.h"

int main()
{ int w = 1024, h = 600;
  int fd = open("/dev/fb0", O_RDWR);
  lseek(fd, (990 + (5 * w)) * sizeof(int), SEEK_SET);
  int y = 0;
  unsigned int bord[18];
  memset(bord, Blanc, 18 * sizeof(int));
  unsigned int ligne[20];
  int i = 1;
  *ligne = Blanc;
  while (i < 17)
  { ligne[i] = Vert;
    i += 1; }
  while (i < 20)
  { ligne[i] = Blanc;
    i += 1; }
  while (y < 8)
  { if (y > 0 && y != 7)
    { write(fd, ligne, 20 * sizeof(int)); }
    else
    { write(fd, bord, 18 * sizeof(int));
      lseek(fd, 2 * sizeof(int), SEEK_CUR); }
    lseek(fd, (w - 20) * sizeof(int), SEEK_CUR);
    y += 1; }}
