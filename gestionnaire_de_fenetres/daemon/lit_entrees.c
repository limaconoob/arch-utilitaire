
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

static void PNBR(unsigned int nb)
{ if (nb / 10)
  { PNBR(nb / 10); }
  char c = '0' + (nb % 10);
  write(1, &c, 1); }

void prochaine_entree(int fd)
{ fd_set rfds;
  FD_ZERO(&rfds);
  FD_SET(fd, &rfds);
  select(fd + 1, &rfds, (void*)0, (void*)0, (void*)0); }

void debug(int fd)
{ char boeuf;
  while (read(fd, &boeuf, 1))
  { if (boeuf == '\n')
    { write(1, "\n", 1);
      continue ; }
    write(1, "0x", 2);
    if (!boeuf)
    { write(1, "0", 1); }
    PNBR(boeuf);
    write(1, " ", 1); }}
