
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/home/arch-utilitaire/gestionnaire_de_fenetres/daemon/.sock/"

enum balise_periph
{ Souris_ON = 0b0001,
  Clavier_ON = 0b0010,
  Joystick_ON = 0b0100 };

typedef struct processus_ctrl
{ pid_t pid;
  int masque;
  int socket_fd;
  struct sockaddr_un addr;
} processus_ctrl;

void NBR(char *dst, unsigned int k)
{ int i = 0, tmp = k;
  while (tmp)
  { i += 1;
    tmp /= 10; }
  while (i)
  { dst[i - 1] = '0' + (k % 10);
    k /= 10;
    i -= 1; }}

processus_ctrl *connection_daemon(pid_t pid, int masque)
{ static processus_ctrl attache;
  if (pid)
  { attache.pid = pid;
    attache.socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    bzero(&(attache.addr), sizeof(attache.addr));
    attache.addr.sun_family = AF_UNIX;
    size_t j = strlen(SOCK_PATH);
    memcpy(attache.addr.sun_path, SOCK_PATH, j);
    NBR(&(attache.addr.sun_path[j]), getpid());
    printf("CONNECT::%s\n", attache.addr.sun_path);
    connect(attache.socket_fd, (struct sockaddr*)&attache.addr, sizeof(attache.addr)); }
  else
  { attache.masque = masque; }
  return (&attache); }

static void ping_pid(int sig, siginfo_t *siginfo, void *contexte)
{ switch (sig)
  { case SIGUSR1 :
    { printf("FILS\n");
      printf("PID::%ld, UID::%ld\n", (long)(*siginfo).si_pid, (long)(*siginfo).si_uid);
   //   printf("SI_VALUE::%d\n", (*siginfo).si_value.sival_int);
      (void)connection_daemon((*siginfo).si_pid, 0);
      break; }}}

int envoi_signal(char *proc_chemin, pid_t pid)
{ int fd = open(proc_chemin, O_RDONLY);
  if (fd <= 2)
  { return (1); }
  char executable[12];
  read(fd, executable, 12);
  if (!strcmp(executable, "DAEMON_INPUT"))
  { union sigval masque;
    masque.sival_int = 42;
    sigqueue(pid, SIGUSR1, masque);
    return (0); }
  return (1); }

char *daemon_input_proc(void)
{ struct dirent *info;
  char proc_chemin[19];
  memcpy(proc_chemin, "/proc/", 6);
  DIR *dossier = opendir("/proc");
  int pid, taille;
  while ((info = readdir(dossier)))
  { if (!(pid = atoi((*info).d_name)))
    { continue; }
    bzero(&(proc_chemin[6]), 12);
    taille = strlen((*info).d_name);
    memcpy(&(proc_chemin[6]), (*info).d_name, taille);
    memcpy(&(proc_chemin[6 + taille]), "/comm", 5);
    envoi_signal(proc_chemin, (pid_t)pid); }
  closedir(dossier); }

int main(void)
{ processus_ctrl *entrees = connection_daemon(0, Souris_ON | Clavier_ON);
  struct sigaction act;
  bzero(&act, sizeof(act));
  act.sa_sigaction = &ping_pid;
  act.sa_flags = SA_SIGINFO;
  (void)sigaction(SIGUSR1, &act, (void*)0);
  daemon_input_proc();
  char boeuf;
  while (read((*entrees).socket_fd, &boeuf, 1))
  { printf("%c", boeuf); }}



