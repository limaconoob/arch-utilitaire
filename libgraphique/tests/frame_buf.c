
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{ time_t tt = time((void*)0);
  char watchdog = 0;
  int w = 1024;
  int h = 600;
  int fd = open("/dev/fb0", O_RDWR);
  lseek(fd, 50 * w * sizeof(int), SEEK_SET);
  int i = 0;
  int vert = 0x0000FF00;
  int cyan = 0x0000FFFF;
  while (i < w)
  { write(fd, (char*)(&vert), 4);
    i += 1; }
  lseek(fd, 850 * sizeof(int), SEEK_SET);
  i = 0;
  while (i < h)
  { write(fd, (char*)(&cyan), 4);
    lseek(fd, (w - 1) * sizeof(int), SEEK_CUR);
    i += 1; }
/*
  while (42)
  { time_t now = time((void*)0);
    if (now == tt + 1 && !watchdog)
    { 
      watchdog = 1; }
    else if (now >= tt + 6)
    { break; }}
*/
}

/*
  int i = 0;
  unsigned int ligne[1024];
  bzero(ligne, 1024 * sizeof(int));
  int fd = open("/dev/fb0", O_RDWR);
  while (i < h)
  { write(fd, ligne, 1024 * sizeof(int));
    i += 1; }}
*/

// cat /sys/class/graphics/fb0/virtual_size
