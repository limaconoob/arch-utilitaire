
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <linux/input.h>

#include "graphiques.h"

typedef struct peripherique
{ int clv; //1 seul clavier
  int srs; //1 seule souris
  u_int motion_x;
  u_int motion_y;
  extra_font icone_souris;
  couleurs pointeur;
  } peripherique;

void clavier_interne()
{ 
  }

typedef enum bool_sauvegarde
{ Sauve,
  Charge,
  } bool_sauvegarde;

void dessous_icone(bool_sauvegarde s, pixels *fb)
{ static u_int sauvegarde[9][7];
  u_int y = 0, x;
  if (s == Sauve)
  { (*fb).shift += sizeof(u_int);
    while (y < 9)
    { x = 0;
      while (x < 7)
      { lseek((*fb).pix, (*fb).shift + ((x + ((y + 1) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
        read((*fb).pix, (char*)(&sauvegarde[y][x]), sizeof(u_int));
        x += 1; }
      y += 1; }}
  else
  { (*fb).shift += sizeof(u_int);
    while (y < 9)
    { x = 0;
      while (x < 7)
      { lseek((*fb).pix, (*fb).shift + ((x + ((y + 1) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&sauvegarde[y][x]), sizeof(u_int));
        x += 1; }
      y += 1; }}}

void pointeur_souris(peripherique *souris, u_int x, u_int y, pixels *fb)
{ //if (x < 2 || y < 2)
  //{ return; }
  (*fb).shift = ((*souris).motion_x + ((*souris).motion_y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Charge, fb);
  (*fb).shift = (x + (y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Sauve, fb);
  (*fb).shift = (x + (y * (*fb).w)) * sizeof(u_int);
  verre7x9((*souris).icone_souris, Jaune, fb);
  (*souris).motion_x = x;
  (*souris).motion_y = y; }

peripherique init_periph(pixels *fb)
{ peripherique periph;
 // periph.clv = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY | O_SYNC);
  periph.srs = open("/dev/input/by-path/platform-i8042-serio-1-event-mouse", O_RDONLY | O_SYNC);
  periph.motion_x = 0;
  periph.motion_y = 0;
  periph.icone_souris = Souris_Doigt;
  struct input_event e;
  while (read(periph.srs, &e, sizeof(struct input_event)))
  { if (e.type == EV_ABS)
    { if (e.code == ABS_MT_POSITION_X)
      { pointeur_souris(&periph, (e.value - 1274) / 4, periph.motion_y, fb); }
      else if (e.code == ABS_MT_POSITION_Y)
      { pointeur_souris(&periph, periph.motion_x, (e.value - 916) / 4, fb); }
    }}
  return (periph); }

int main()
{ pixels fb = init_gui();
  (void)init_periph(&fb); }

//cat /dev/input/by-path/platform-i8042-serio-0-event-kbd
//cat /dev/input/mouse0
//vim /usr/include/linux/input.h
//cat /dev/input/by-path/platform-i8042-serio-1-mouse
