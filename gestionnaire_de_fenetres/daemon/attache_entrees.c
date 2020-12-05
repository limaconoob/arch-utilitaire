
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

#include "peripheriques.h"

typedef struct processus_ctrl
{ pid_t pid;
  int masque;
  int socket_fd;
  struct sockaddr_un addr;
} processus_ctrl;

static void NBR(char *dst, unsigned int k)
{ int i = 0, tmp = k;
  while (tmp)
  { i += 1;
    tmp /= 10; }
  while (i)
  { dst[i - 1] = '0' + (k % 10);
    k /= 10;
    i -= 1; }}

static processus_ctrl *connection_daemon(pid_t pid, int masque)
{ static processus_ctrl attache;
  if (pid)
  { attache.pid = pid;
    attache.socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    bzero(&(attache.addr), sizeof(attache.addr));
    attache.addr.sun_family = AF_UNIX;
    size_t j = strlen(SOCK_PATH);
    memcpy(attache.addr.sun_path, SOCK_PATH, j);
    NBR(&(attache.addr.sun_path[j]), getpid());
    connect(attache.socket_fd, (struct sockaddr*)&attache.addr, sizeof(attache.addr)); }
  else
  { attache.masque = masque;
    attache.pid = 0; }
  return (&attache); }

static void ping_pid(int sig, siginfo_t *siginfo, void *contexte)
{ switch (sig)
  { case SIGUSR1 :
    { (void)connection_daemon((*siginfo).si_pid, 0);
      break; }}}

static int envoi_signal(char *proc_chemin, pid_t pid, int masque)
{ int fd = open(proc_chemin, O_RDONLY);
  if (fd <= 2)
  { return (1); }
  char executable[12];
  read(fd, executable, 12);
  if (!strcmp(executable, "DAEMON_INPUT"))
  { union sigval transfert;
    transfert.sival_int = masque;
    sigqueue(pid, SIGUSR1, transfert);
    return (0); }
  return (1); }

static int daemon_input_proc(int masque)
{ struct dirent *info;
  char proc_chemin[19];
  memcpy(proc_chemin, "/proc/", 6);
  DIR *dossier = opendir("/proc");
  int pid, taille, flag = 1;
  while ((info = readdir(dossier)))
  { if (!(pid = atoi((*info).d_name)))
    { continue; }
    bzero(&(proc_chemin[6]), 12);
    taille = strlen((*info).d_name);
    memcpy(&(proc_chemin[6]), (*info).d_name, taille);
    memcpy(&(proc_chemin[6 + taille]), "/comm", 5);
    if (!envoi_signal(proc_chemin, (pid_t)pid, masque))
    { flag = 0; }}
  closedir(dossier);
  return (flag); }

int attache_entrees(int masque)
{ static processus_ctrl *entrees;
  entrees = connection_daemon(0, masque);
  struct sigaction act;
  bzero(&act, sizeof(act));
  act.sa_sigaction = &ping_pid;
  act.sa_flags = SA_SIGINFO;
  (void)sigaction(SIGUSR1, &act, (void*)0);
  if (!daemon_input_proc(masque))
  { while (!(*entrees).pid)
    { ; }
    return ((*entrees).socket_fd); }
  return (-1); }



