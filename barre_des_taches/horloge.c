
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>

#include "graphiques.h"
#include "types.h"

static void dessin_horloge(pixels *fb, char *the_time)
{ u_char cadran[14];
  cadran[0] = the_time[8];
  cadran[1] = the_time[9];
  cadran[2] = '/';
  cadran[3] = the_time[5];
  cadran[4] = the_time[6];
  cadran[5] = ' ';
  memcpy(&(cadran[6]), &(the_time[10]), 8);
  phrase_bande(cadran, 14, Blanc, Noir, (*fb).w - 154, 2, fb); }

void gestion_horloge(pixels *fb)
{ time_t t;
  static int fd_date = 0;
  static int fd_heure = 0;
  if (!fd_date)
  { fd_date = open("/sys/class/rtc/rtc0/date", O_RDONLY | O_SYNC);
    fd_heure = open("/sys/class/rtc/rtc0/time", O_RDONLY | O_SYNC); }
  lseek(fd_date, 0, SEEK_SET);
  lseek(fd_heure, 0, SEEK_SET);
  char boeuf[18];
  read(fd_date, boeuf, 10);
  read(fd_heure, &(boeuf[10]), 8);
  dessin_horloge(fb, boeuf); }


