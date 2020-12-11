
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <linux/input.h>

#include "peripheriques.h"
#include "noyau_clavier.h"

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

void pointeur_souris(souris *srs, u_int x, u_int y, pixels *fb)
{ (*fb).shift = ((*srs).motion_x + ((*srs).motion_y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Charge, fb);
  (*fb).shift = (x + (y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Sauve, fb);
  verre7x9((*srs).icone_souris, Jaune, x, y, fb);
  (*srs).motion_x = x;
  (*srs).motion_y = y; }

void *gestion_souris(void *s)
{ peripherique *periph = (peripherique*)s;
  souris *srs = &((*periph).srs);
  struct input_event e;
  fd_set rfds;
  printf("INIT_SRS\n");
  while (42)
  { FD_ZERO(&rfds);
    FD_SET((*srs).fd, &rfds);
    select((*srs).fd + 1, &rfds, (void*)0, (void*)0, (void*)0);
    read((*srs).fd, &e, sizeof(struct input_event));
    if (e.type == EV_ABS)
    { (*periph).pret |= Motion_Absolu;
      if (e.code == ABS_MT_POSITION_X)
      { pointeur_souris(srs, ((e.value - 1274) * (*(*periph).fb).w) / 4452, (*srs).motion_y, (*periph).fb); }
      else if (e.code == ABS_MT_POSITION_Y)
      { pointeur_souris(srs, (*srs).motion_x, ((e.value - 916) * (*(*periph).fb).h) / 4040, (*periph).fb); }}
    else if (e.type == EV_KEY) 
    { if (e.value == 1) /// Appui
      { (*periph).pret |= Bouton_Appui;
        if (e.code == BTN_LEFT)
        { (*periph).srs.dernier_clic = Bouton_Souris_Gauche; }
        else if (e.code == BTN_RIGHT)
        { (*periph).srs.dernier_clic = Bouton_Souris_Droit; }}
      else if (e.value == 0) /// Relâchement
      { (*periph).pret |= Bouton_Relache;
        if (e.code == BTN_LEFT)
        { (*periph).srs.dernier_clic = Bouton_Souris_Gauche; }
        else if (e.code == BTN_RIGHT)
        { (*periph).srs.dernier_clic = Bouton_Souris_Droit; }}}
    (*periph).pret |= Souris_PRET; }}

// BTN_TOOL_FINGER
// BTN_TOUCH

/// flag_persistant : 0b shift_gauche shift_droite alt altgr ctrl_gauche ctrl_droite fn 
void *gestion_clavier(void *s)
{ peripherique *periph = (peripherique*)s;
  struct input_event e;
  fd_set rfds;
  printf("INIT_CLV\n");
  while (42)
  { FD_ZERO(&rfds);
    FD_SET((*periph).clv.fd, &rfds);
    select((*periph).clv.fd + 1, &rfds, (void*)0, (void*)0, (void*)0);
    read((*periph).clv.fd, &e, sizeof(struct input_event));
    if (e.type == EV_KEY)
    { if (e.value == 1) // Appui
      { (*periph).clv.derniere_touche = noyau_clavier[e.code];
        (*periph).pret |= Bouton_Appui;
        if ((*periph).clv.flag_persistant & AltGr != 0 && e.code < 54)
        { if ((*periph).clv.flag_persistant & Shift != 0)
          { //printf("NOYAU::%c, CODE::%d\n", noyau_clavier[e.code], e.code);
            }
          else if ((*periph).clv.flag_persistant & Shift == 0)
          { //printf("NOYAU::%c, CODE::%d\n", noyau_shift_clavier[e.code], e.code);
            }
          if (e.code == KEY_LEFTSHIFT)
          { (*periph).clv.flag_persistant |= Shift_Gauche; }
          else if (e.code == KEY_RIGHTSHIFT)
          { (*periph).clv.flag_persistant |= Shift_Droit; }}
        if ((*periph).clv.flag_persistant & AltGr && e.code < 14)
        { //printf("NOYAU::%c, CODE::%d\n", noyau_altgr_clavier[e.code], e.code);
          }
        if (e.code == KEY_RIGHTALT)
        { (*periph).clv.flag_persistant |= AltGr; }
        }
      else if (e.value == 0) // Relâchement
      { (*periph).pret |= Bouton_Relache;
        if (e.code == KEY_LEFTSHIFT && (*periph).clv.flag_persistant & Shift_Gauche)
        { (*periph).clv.flag_persistant -= Shift_Gauche; }
        else if (e.code == KEY_RIGHTSHIFT && (*periph).clv.flag_persistant & Shift_Droit)
        { (*periph).clv.flag_persistant -= Shift_Droit; }
        else if (e.code == KEY_RIGHTALT && (*periph).clv.flag_persistant & AltGr)
        { (*periph).clv.flag_persistant -= AltGr; }
        }
      else if (e.value == 2) // Maintien enfoncé
      { (*periph).pret |= Bouton_Maintien;
        }}
    (*periph).pret |= Clavier_PRET; }}

void init_souris(peripherique *periph)
{ (*periph).srs.fd = open("/dev/input/by-path/platform-i8042-serio-1-event-mouse", O_RDONLY | O_SYNC);
//{ (*periph).srs.fd = open("/dev/input/mice", O_RDONLY | O_SYNC);
  (*periph).srs.motion_x = 0;
  (*periph).srs.motion_y = 0;
  (*periph).srs.dernier_clic = 0;
  (*periph).srs.icone_souris = Souris_Fleche;
  pthread_create(&((*periph).srs.canal), (void*)0, &gestion_souris, periph); }

void init_clavier(peripherique *periph)
{ (*periph).clv.fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY | O_SYNC);
//{ (*periph).clv.fd = open("/dev/input/event2", O_RDONLY | O_SYNC);
  (*periph).clv.flag_persistant = 0;
  (*periph).clv.derniere_touche = 0;
  bzero((*periph).clv.queue, 42 * sizeof(u_int));
  pthread_create(&((*periph).clv.canal), (void*)0, &gestion_clavier, periph); }

peripherique init_periph(pid_t maitre_pid, pixels *fb)
{ peripherique periph;
  bzero(&(periph.clv.canal), sizeof(pthread_t));
  bzero(&(periph.srs.canal), sizeof(pthread_t));
  periph.pid = maitre_pid;
  periph.pret = 0;
  periph.fb = fb;
  return (periph); }

/*
int main()
{ pixels fb = init_gui();
  init_periph(&fb);
  while(42)
  { ; }
  }
*/

//cat /dev/input/by-path/platform-i8042-serio-0-event-kbd
//cat /dev/input/mouse0
//vim /usr/include/linux/input.h
//cat /dev/input/by-path/platform-i8042-serio-1-mouse
