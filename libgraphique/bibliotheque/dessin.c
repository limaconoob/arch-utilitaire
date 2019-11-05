
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

#include "graphiques.h"

void dessin_rect(rectangle rect, couleurs couleur, pixels *fb)
{ u_int hor_bord[1024];
  u_int i = 0;
  if (rect.w < 2 || rect.h < 2)
  { return; }
  while (i < rect.w)
  { hor_bord[i] = couleur;
    i += 1; }
  if (rect.x < (*fb).w && rect.y < (*fb).h)
  { (*fb).shift = (rect.x + (rect.y * (*fb).w)) * sizeof(u_int); }
  lseek((*fb).pix, (*fb).shift , SEEK_SET);
  write((*fb).pix, hor_bord, rect.w * sizeof(u_int));
  i = 0;
  while (i < rect.h - 2)
  { lseek((*fb).pix, (*fb).shift + (((i + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, (char*)(&couleur), 4);
    lseek((*fb).pix, (rect.w - 2) * sizeof(u_int), SEEK_CUR);
    write((*fb).pix, (char*)(&couleur), 4);
    i += 1; }
  lseek((*fb).pix, (*fb).shift + (((i + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
  write((*fb).pix, hor_bord, rect.w * sizeof(u_int));
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void dessin_pave(rectangle rect, couleurs couleur, pixels *fb)
{ u_int remplisseur[1024];
  u_int i = 0;
  if (rect.w < 2 || rect.h < 2 || rect.x >= (*fb).w || rect.y >= (*fb).h)
  { return; }
  while (i < rect.w)
  { remplisseur[i] = couleur;
    i += 1; }
  (*fb).shift = (rect.x + (rect.y * (*fb).w)) * sizeof(u_int);
  i = 0;
  while (i < rect.h)
  { lseek((*fb).pix, (*fb).shift + ((i * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, remplisseur, rect.w * sizeof(u_int));
    i += 1; }
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void dessin_cercle(cercle c, couleurs couleur, pixels *fb)
{ float i = -3.14;
  float x, y, tmp_x, tmp_y;
  float pas = 3.14 / (c.rayon * 2);
  x = c.x + (u_int)(cos(i) * (float)c.rayon);
  y = c.y + (u_int)(sin(i) * (float)c.rayon);
  while (i <= 3.14)
  { i += pas;
    tmp_x = c.x + (u_int)(cos(i) * (float)c.rayon);
    tmp_y = c.y + (u_int)(sin(i) * (float)c.rayon);
    ligne l = { x, y, tmp_x, tmp_y };
    dessin_ligne(l, couleur, fb);
    x = tmp_x;
    y = tmp_y; }}

void dessin_ligne(ligne l, couleurs couleur, pixels *fb)
{ if (l.x1 >= (*fb).w || l.x2 >= (*fb).w || l.y1 >= (*fb).h || l.y2 >= (*fb).h)
  { return; }
  float i = 0;
  int tmp;
  u_int nb_pixels_dessin;
  float a = 0;
  if (l.x2 < l.x1)
  { tmp = l.x2;
    l.x2 = l.x1;
    l.x1 = tmp;
    tmp = l.y2;
    l.y2 = l.y1;
    l.y1 = tmp; }
  (*fb).shift = (l.x1 + (l.y1 * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  if (l.x2 > l.x1)
  { a = ((float)l.y2 - (float)l.y1) / ((float)l.x2 - (float)l.x1);
    if (a < 0)
    { a = -a;
      if (a > 1)
      { nb_pixels_dessin = (l.y1 - l.y2) + 1; 
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + (((u_int)((float)i / a) - (i * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}
      else
      { nb_pixels_dessin = (l.x2 - l.x1) + 1;
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + ((i - ((u_int)(a * i) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}}
    else
    { if (a > 1)
      { nb_pixels_dessin = (l.y2 - l.y1) + 1; 
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + (((u_int)(i / a) + (i * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}
      else
      { nb_pixels_dessin = (l.x2 - l.x1) + 1;
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + ((i + ((u_int)(a * i) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}}}
  else
  { if (l.y2 > l.y1)
    { nb_pixels_dessin = l.y2 - l.y1;
      i = 0;
      while (i < nb_pixels_dessin)
      { lseek((*fb).pix, (*fb).shift + (i * (*fb).w * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&couleur), sizeof(u_int));
        i += 1; }}
    else
    { nb_pixels_dessin = l.y1 - l.y2;
      i = 0;
      while (i < nb_pixels_dessin)
      { lseek((*fb).pix, (*fb).shift - (i * (*fb).w * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&couleur), sizeof(u_int));
        i += 1; }}}
  (*fb).shift = (l.x2 + (l.y2 * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  write((*fb).pix, (char*)(&couleur), sizeof(u_int)); }

