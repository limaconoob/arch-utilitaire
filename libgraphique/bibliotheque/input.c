
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
#include "peripheriques.h"
#include "noyau_clavier.h"

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

enum entrees
{ Souris,
  Clavier,
  Joystick };

static void ping_pid(int sig, siginfo_t *siginfo, void *contexte)
{ switch (sig)
  { case SIGUSR1 :
    { printf("PID::%ld, UID::%ld\n", (long)(*siginfo).si_pid, (long)(*siginfo).si_uid);
      printf("SI_VALUE::(%d, %s)\n", (*siginfo).si_value.sival_int, (char*)((*siginfo).si_value.sival_ptr));
      break; }}}

/*
void nouveau_canal_repartition(int pid)
{ int fd[64][2];
  int nbytes;
  char *string = "Coucou\n";
  char readbuffer[80];
  pipe(fd);
  if (!childpid)
  { close(fd[0]);
    write(fd[1], string, strlen(string) + 1);
    exit(0); }
  else
  { close(fd[1]);
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    printf("Bonjour::%s\n", readbuffer); }}
*/

static void tache_cachee()
{ pixels fb = init_gui();
  peripherique per = init_periph(getpid(), &fb);
  init_souris(&per);
  struct sigaction act;
  bzero(&act, sizeof(act));
  act.sa_sigaction = &ping_pid;
  act.sa_flags = SA_SIGINFO;
  (void)sigaction(SIGUSR1, &act, (void*)0);
  while (42)
  { 
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


