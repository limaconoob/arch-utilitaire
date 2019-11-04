
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "graphiques.h"
#include "display.h"

#include <stdio.h>

void dessin7x9(extra_font c, couleurs fg, couleurs bg, pixels *fb)
{ u_int carr[7];
  bzero(carr, 7 * sizeof(u_int));
  draw from_table = icones7x9[c];
  u_char y = 0, x;
  (*fb).shift += sizeof(u_int);
  while (y < 9)
  { x = 0;
    while (x < 7)
    { carr[x] = from_table & ((u_long)1 << (((9 - y) * 7) - x)) ? fg : bg;
      x += 1; }
    lseek((*fb).pix, (*fb).shift + (((y + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, carr, 7 * sizeof(u_int));
    y += 1; }
  (*fb).shift += 8; }

void phrase_bande(u_char *str, u_int taille, couleurs fg, couleurs bg, pixels *fb)
{ u_int bande[9][1024];
  if (taille > 128)
  { return ; }
  int i = 0;
  int y, x; // en pixel
  draw from_table;
  while (i < taille)
  { if (str[i] < 32)
    { i += 1;
      continue; }
    from_table = font7x9[str[i] - 32];
    y = 0;
    while (y < 9)
    { x = 0;
      while (x < 7)
      { bande[y][x + (i * 8)] = from_table & ((u_long)1 << (((9 - y) * 7) - x)) ? fg : bg;
        x += 1; }
      bande[y][x + (i * 8)] = bg;
      y += 1; }
    i += 1; }
  y = 0;
  rectangle r = { 1024, 1024, (taille * 8) + 1, 11 };
  dessin_rect(r, bg, fb);
  (*fb).shift += sizeof(u_int);
  while (y < 9)
  { lseek((*fb).pix, (*fb).shift + (((y + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, bande[y], (taille * 8) * sizeof(u_int));
    y += 1; }
  (*fb).shift += taille * 8;
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void phrase_verre(u_char *str, u_int taille, couleurs fg, couleurs bg, pixels *fb)
{
  }
/*
    y = 0;
    while (y < 9)
    { x = 0;
      while (x < 7)
      { bande[y][x + (i * 8)] = from_table & ((u_long)1 << (((9 - y) * 7) - x)) ? fg : bg;
        x += 1; }
      bande[y][x + (i * 8)] = bg;
      y += 1; }
*/
/*
i = 0;
while (i < taille * 8)
{ write(fd, bande[y][i] == fg ? "1" : "0", 1);
  i += 1; }
write(fd, "\n", 1);
int fd = open("Bonjour.txt", O_CREAT | O_WRONLY);
lseek(fd, i * 8, SEEK_SET);
write(fd, from_table & ((u_long)1 << ((((9 - y) * 7) - 1) - x)) ? "1" : "0", 1);
write(fd, "0\n", 1);
*/
