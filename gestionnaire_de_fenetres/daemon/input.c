
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "graphiques.h"
#include "peripheriques.h"

#define SOCK_PATH "/home/arch-utilitaire/gestionnaire_de_fenetres/daemon/.sock/"

// Mettre un get_event() dans le programme utilisateur
// init_event 
// read /dev/input, et qui crée un Socket par nouveau processus

/*
** Il faut écrire ça dans le processus appelant :
**
** int main(void)
** { struct sigaction act;
**   bzero(&act, sizeof(act));
**   act.sa_sigaction = &hdl;
**   act.sa_flags = SA_SIGINFO;
**   (void)sigaction(SIGUSR1, &act, (void*)0);
**   while (42)
**   { ; }}
*/

typedef struct processus_ctrl
{ pid_t pid;
  int masque;
  int calque;
  int socket_fd;
  int sub_fd;
  struct sockaddr_un my_addr;
  struct sockaddr_un peer_addr;
  struct processus_ctrl *suivante;
} processus_ctrl;

size_t NBR_LEN(unsigned int k)
{ size_t i = 0;
  while (k)
  { i += 1;
    k /= 10; }
  return (i); }

void NBR(char *dst, unsigned int k)
{ size_t i = NBR_LEN(k);
  while (i)
  { dst[i - 1] = '0' + (k % 10);
    k /= 10;
    i -= 1; }}

processus_ctrl nouveau_socket(pid_t pid, int masque)
{ processus_ctrl structure;
  bzero(&structure, sizeof(processus_ctrl));
  structure.masque = masque;
  structure.pid = pid;
  structure.socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  structure.my_addr.sun_family = AF_UNIX;
  size_t j = strlen(SOCK_PATH);
  memcpy(structure.my_addr.sun_path, SOCK_PATH, j);
  NBR(&(structure.my_addr.sun_path[j]), pid);
  printf("NOM::%s\n", structure.my_addr.sun_path);
  bind(structure.socket_fd, (struct sockaddr *)&(structure.my_addr), sizeof(structure.my_addr));
  listen(structure.socket_fd, 5);
  socklen_t k = sizeof(structure.my_addr);
  kill(pid, SIGUSR1);
  structure.sub_fd = accept(structure.socket_fd, (struct sockaddr*)&(structure.peer_addr), &k);
  return (structure); }

size_t nombre_processus(processus_ctrl *attache)
{ size_t i = 0;
  while ((*attache).suivante)
  { attache = (*attache).suivante;
    i += 1; }
  return (i); }

void ajout_processus(processus_ctrl *attache, pid_t pid, int masque)
{ while ((*attache).suivante)
  { attache = (*attache).suivante; }
  (*attache).suivante = (processus_ctrl*)malloc(sizeof(processus_ctrl));
  *((*attache).suivante) = nouveau_socket(pid, masque); }

processus_ctrl *nouveau_processus(pid_t pid, int masque)
{ static processus_ctrl *attache = (void*)0;
  if (!pid)
  { return (attache); }
  else if (attache)
  { ajout_processus(attache, pid, masque); 
    return (attache); }
  else
  { attache = (processus_ctrl*)malloc(sizeof(processus_ctrl));
    *attache = nouveau_socket(pid, masque);
    return (attache); }}

static void ping_pid(int sig, siginfo_t *siginfo, void *contexte)
{ switch (sig)
  { case SIGUSR1 :
    { //printf("PID::%ld, UID::%ld\n", (long)(*siginfo).si_pid, (long)(*siginfo).si_uid);
      //printf("SI_VALUE::%d\n", (*siginfo).si_value.sival_int);
      nouveau_processus((*siginfo).si_pid, (*siginfo).si_value.sival_int);
      break; }}}

void envoyer_souris(processus_ctrl *maitre_proc, peripherique per)
{ char motion_souris[40];
  size_t num_taille = 9;
  memcpy(motion_souris, "MOTION::(", 9);
  bzero(&(motion_souris[num_taille]), 31);
  NBR(&(motion_souris[num_taille]), per.srs.motion_x);
  num_taille += NBR_LEN(per.srs.motion_x);
  memcpy(&(motion_souris[num_taille]), ", ", 2);
  num_taille += 2;
  NBR(&(motion_souris[num_taille]), per.srs.motion_y);
  num_taille += NBR_LEN(per.srs.motion_y);
  memcpy(&(motion_souris[num_taille]), ")\n", 2);
  write((*maitre_proc).sub_fd, motion_souris, num_taille + 2); }

void envoyer_clavier(processus_ctrl *maitre_proc, peripherique per)
{ char touche_clavier[20];
  size_t num_taille = 9;
  memcpy(touche_clavier, "CLAVIER::", 9);
//  bzero(&(touche_clavier[num_taille]), 11);
//  NBR(&(touche_clavier[num_taille]), per.clv.derniere_touche);
//  num_taille += NBR_LEN(per.clv.derniere_touche);
  touche_clavier[9] = per.clv.derniere_touche;
  touche_clavier[10] = '\n';
  write((*maitre_proc).sub_fd, touche_clavier, 11); }

static void tache_cachee()
{ pixels fb = init_gui();
  peripherique per = init_periph(getpid(), &fb);
  init_souris(&per);
  init_clavier(&per);
  struct sigaction act;
  bzero(&act, sizeof(act));
  act.sa_sigaction = &ping_pid;
  act.sa_flags = SA_SIGINFO;
  (void)sigaction(SIGUSR1, &act, (void*)0);
  processus_ctrl *maitre_proc = (void*)0;
  while (!maitre_proc)
  { maitre_proc = nouveau_processus(0, 0); }
  while (42)
  { maitre_proc = nouveau_processus(0, 0);
    envoyer_souris(maitre_proc, per);
    envoyer_clavier(maitre_proc, per);
    usleep(8000); }}

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


