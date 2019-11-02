
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

#include "graphiques.h"

static void icone_batterie(int puissance, couleurs bat, pixels *fb)
{ int y = 0;
  unsigned int bord[18];
  memset(bord, Blanc, 18 * sizeof(int));
  unsigned int ligne[20];
  *ligne = Blanc;
  int i = 1;
  lseek((*fb).pix, (((*fb).w - 29) + (4 * (*fb).w)) * sizeof(int), SEEK_SET);
  while (i < puissance + 1)
  { ligne[i] = puissance > 6 ? bat : Rouge;
    i += 1; }
  while (i < 17)
  { ligne[i] = Noir;
    i += 1; }
  while (i < 20)
  { ligne[i] = Blanc;
    i += 1; }
  while (y < 8)
  { if (y > 0 && y != 7)
    { write((*fb).pix, ligne, 20 * sizeof(int)); }
    else
    { write((*fb).pix, bord, 18 * sizeof(int));
      lseek((*fb).pix, 2 * sizeof(int), SEEK_CUR); }
    lseek((*fb).pix, ((*fb).w - 20) * sizeof(int), SEEK_CUR);
    y += 1; }}

static float energie_max()
{ char plein[4];
  read(open("/sys/class/power_supply/BAT1/energy_full", O_SYNC | O_RDONLY), &plein, 4);
  return ((float)atoi(plein)); }

void gestion_batterie(pixels *fb)
{ static float plein = 0;
  if (!plein)
  { plein = energie_max(); }
  static int capa = 0;
  if (!capa)
  { capa = open("/sys/class/power_supply/BAT1/status", O_SYNC | O_RDONLY); }
  lseek(capa, 0, SEEK_SET);
  char alim_cable;
  read(capa, &alim_cable, 1);
  static int fd = 0;
  if (!fd)
  { fd = open("/sys/class/power_supply/BAT1/energy_now", O_SYNC | O_RDONLY); }
  char courant[4];
  lseek(fd, 0, SEEK_SET);
  read(fd, &courant, 4);
  float pourcent = ((float)atoi(courant)) / plein;
  if (alim_cable & 0b10)
  { icone_batterie((int)(16.0 * pourcent), Cyan, fb); }
  else
  { icone_batterie((int)(16.0 * pourcent), Vert, fb); }}

// /sys/class/power_supply/BAT1/capacity
// /sys/class/power_supply/BAT1/energy_now
