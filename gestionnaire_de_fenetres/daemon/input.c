
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
  if (!k)
  { return (1); }
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
  //printf("NOM::%s\n", structure.my_addr.sun_path);
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

// Motion : (Souris_PRET | Souris_Motion)'motion_x';'motion_y'
// Bouton : (Souris_PRET | Bouton_Action)'dernier_clic'
// Maintien : (Souris_PRET)'dernier_clic'
void envoyer_souris(processus_ctrl *maitre_proc, peripherique per)
{ unsigned char evenement_souris[40];
  bzero(evenement_souris, 40);
  *evenement_souris = per.pret;
  size_t num_taille = 1;
  if (per.pret & Souris_Motion)
  { NBR(&(evenement_souris[num_taille]), per.srs.motion_x);
    num_taille += NBR_LEN(per.srs.motion_x);
    evenement_souris[num_taille] = ';';
    num_taille += 1;
    NBR(&(evenement_souris[num_taille]), per.srs.motion_y);
    num_taille += NBR_LEN(per.srs.motion_y); }
  else
  { *(evenement_souris + 1) = per.srs.dernier_clic;
    num_taille += 1; }
  evenement_souris[num_taille] = '\n';
  write((*maitre_proc).sub_fd, evenement_souris, num_taille + 1); }

// Bouton : (Clavier_PRET | Bouton_Action)'derniere_touche'
// Maintien : (Clavier_PRET)'derniere_touche'
void envoyer_clavier(processus_ctrl *maitre_proc, peripherique per)
{ char touche_clavier[6];
  bzero(touche_clavier, 6);
  *touche_clavier = per.pret;
  touche_clavier[1] = (per.clv.derniere_touche & 0xFF000000) >> 24;
  touche_clavier[2] = (per.clv.derniere_touche & 0x00FF0000) >> 16;
  touche_clavier[3] = (per.clv.derniere_touche & 0x0000FF00) >> 8;
  touche_clavier[4] = per.clv.derniere_touche & 0x000000FF;
  touche_clavier[5] = '\n';
  write((*maitre_proc).sub_fd, touche_clavier, 6); }

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
  { if ((*maitre_proc).masque & Souris_ON && per.pret & Souris_PRET)
    { envoyer_souris(maitre_proc, per);
      per.pret = 0; }
    if ((*maitre_proc).masque & Clavier_ON && per.pret & Clavier_PRET)
    { envoyer_clavier(maitre_proc, per);
      per.pret = 0; }
    usleep(5000); }}

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


