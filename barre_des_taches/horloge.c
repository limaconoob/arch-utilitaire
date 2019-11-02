
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>

#include "graphiques.h"
#include "types.h"

static void dessin_horloge(pixels *fb, struct tm the_time)
{ u_char cadran[14];
  cadran[0] = (the_time.tm_mday / 10) + '0';
  cadran[1] = (the_time.tm_mday % 10) + '0';
  cadran[2] = '/';
  cadran[3] = ((the_time.tm_mon + 1) / 10) + '0';
  cadran[4] = ((the_time.tm_mon + 1) % 10) + '0';
  cadran[5] = ' ';
  cadran[6] = (the_time.tm_hour / 10) + '0';
  cadran[7] = (the_time.tm_hour % 10) + '0';
  cadran[8] = ':';
  cadran[9] = (the_time.tm_min / 10) + '0';
  cadran[10] = (the_time.tm_min % 10) + '0';
  cadran[11] = ':';
  cadran[12] = (the_time.tm_sec / 10) + '0';
  cadran[13] = (the_time.tm_sec % 10) + '0';
  (*fb).shift = (((*fb).w - 154) + ((*fb).w * 2)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  phrase_bande(cadran, 14, Blanc, Noir, fb); }

void gestion_horloge(pixels *fb)
{ time_t t;
  time(&t);
  struct tm *the_time = localtime(&t);
  dessin_horloge(fb, *the_time); }

