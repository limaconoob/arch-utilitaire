
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

#include "graphiques.h"

point_pix creation_pixel(u_int x, u_int y, couleurs c)
{ point_pix p = { x, y, c };
  return (p); }

void dessin_pixel(point_pix p, pixels *fb)
{ (*fb).shift = (p.x + (p.y * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  write((*fb).pix, (char*)(&p.c), sizeof(u_int)); }

void dessin_objet(u_int *objet, rectangle rect, pixels *fb)
{ if (rect.w < 2 || rect.h < 2)
  { return; }
  if (rect.xy.x < (*fb).w && rect.xy.y < (*fb).h)
  { (*fb).shift = (rect.xy.x + (rect.xy.y * (*fb).w)) * sizeof(u_int); }
  u_int y = 0;
  while (y < rect.h)
  { lseek((*fb).pix, (*fb).shift + ((y * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, (char*)objet, rect.w * sizeof(u_int));
    y += 1; }}

void dessin_monochrome(u_int *objet, rectangle rect, pixels *fb)
{ u_int i = 0, j;
  while (i < rect.w)
  { (*fb).remplisseur[i] = rect.xy.c;
    i += 1; }
  u_int x, y = 0;
  while (y < rect.h)
  { x = 0;
    while (x < rect.w)
    { i = 0;
      while (i < 64)
      { 
        i += 1; }
      x += 1; }
    y += 1; }
  }

void dessin16x16(u_short *objet, rectangle rect, couleurs fond, pixels *fb)
// rect w h : coin haut droit, <= 16
{ u_short x, y = 0;
  (*fb).shift = (rect.xy.x + (rect.xy.y * (*fb).w)) * sizeof(u_int);
  while (y < rect.h)
  { x = 0;
    while (x < rect.w)
    { (*fb).remplisseur[x] = objet[y] & 1 << (15 - x) ? rect.xy.c : fond;
      x += 1; }
    lseek((*fb).pix, (*fb).shift + ((y * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, (*fb).remplisseur, rect.w * sizeof(u_int));
    y += 1; }}

void dessin_rect(rectangle rect, pixels *fb)
{ u_int i = 0;
  if (rect.w < 2 || rect.h < 2)
  { return; }
  while (i < rect.w)
  { (*fb).remplisseur[i] = rect.xy.c;
    i += 1; }
  if (rect.xy.x < (*fb).w && rect.xy.y < (*fb).h)
  { (*fb).shift = (rect.xy.x + (rect.xy.y * (*fb).w)) * sizeof(u_int); }
  lseek((*fb).pix, (*fb).shift , SEEK_SET);
  write((*fb).pix, (*fb).remplisseur, rect.w * sizeof(u_int));
  i = 0;
  while (i < rect.h - 2)
  { lseek((*fb).pix, (*fb).shift + (((i + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, (char*)(&(rect.xy.c)), 4);
    lseek((*fb).pix, (rect.w - 2) * sizeof(u_int), SEEK_CUR);
    write((*fb).pix, (char*)(&(rect.xy.c)), 4);
    i += 1; }
  lseek((*fb).pix, (*fb).shift + (((i + 1) * (*fb).w) * sizeof(u_int)), SEEK_SET);
  write((*fb).pix, (*fb).remplisseur, rect.w * sizeof(u_int));
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void dessin_pave(rectangle rect, pixels *fb)
{ u_int i = 0;
  if (rect.w < 2 || rect.h < 2 || rect.xy.x >= (*fb).w || rect.xy.y >= (*fb).h)
  { return; }
  couleurs couleur = rect.xy.c;
  while (i < rect.w)
  { (*fb).remplisseur[i] = couleur;
    i += 1; }
  (*fb).shift = (rect.xy.x + (rect.xy.y * (*fb).w)) * sizeof(u_int);
  i = 0;
  while (i < rect.h)
  { lseek((*fb).pix, (*fb).shift + ((i * (*fb).w) * sizeof(u_int)), SEEK_SET);
    write((*fb).pix, (*fb).remplisseur, rect.w * sizeof(u_int));
    i += 1; }
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void dessin_triangle(triangle t, pixels *fb)
//    /\
//   /  \
//  '----`
{ ligne l1 = { t.i.x, t.i.y, t.i.c, t.j.x, t.j.y };
  ligne l2 = { t.j.x, t.j.y, t.j.c, t.k.x, t.k.y };
  ligne l3 = { t.k.x, t.k.y, t.k.c, t.i.x, t.i.y };
  dessin_ligne(l1, fb);
  dessin_ligne(l2, fb);
  dessin_ligne(l3, fb); }

//void dessin_part(, pixels *fb)
//{ float angle_base, float angle_horaire;
//  }

void dessin_part(cercle c, float angle_base, float angle_horaire, pixels *fb)
//  /\
// /__)
{ float i = -3.14;
  float x, y, tmp_x, tmp_y;
  float pas = 3.14 / (c.rayon * 2);
  x = c.xy.x - ((float)c.rayon - 1);
  y = c.xy.y;
  while (i <= 3.14)
  { i += pas;
    tmp_x = c.xy.x + (int)(cos(i) * (float)c.rayon);
    tmp_y = c.xy.y + (int)(sin(i) * (float)c.rayon);
    ligne l = { x, y, c.xy.c, tmp_x, tmp_y };
    dessin_ligne(l, fb);
    x = tmp_x;
    y = tmp_y; }}

void dessin_arc(cercle c, float angle_base, float angle_horaire, pixels *fb)
//  \
//   )
// angle_base &
{ float x, y, tmp_x, tmp_y;
  float mina, maxa;
  if (angle_base <= 180.0)
  { mina = -((3.14 * angle_base) / 180.0); }
  else
  { mina = (3.14 * (angle_base - 180.0)) / 180.0; }
  if (angle_horaire <= 180.0)
  { maxa = -((3.14 * angle_horaire) / 180.0); }
  else
  { maxa = (3.14 * (angle_horaire - 180.0)) / 180.0; }
  float pas = 3.14 / (c.rayon * 2);
  x = c.xy.x + (int)(cos(mina) * (float)c.rayon);
  y = c.xy.y + (int)(sin(mina) * (float)c.rayon);
  if (mina <= maxa)
  { while (mina <= maxa)
    { mina += pas;
      tmp_x = c.xy.x + (int)(cos(mina) * (float)c.rayon);
      tmp_y = c.xy.y + (int)(sin(mina) * (float)c.rayon);
      ligne l = { x, y, c.xy.c, tmp_x, tmp_y };
      dessin_ligne(l, fb);
      x = tmp_x;
      y = tmp_y; }}
  else
  { while (mina > maxa)
    { mina -= pas;
      tmp_x = c.xy.x + (int)(cos(mina) * (float)c.rayon);
      tmp_y = c.xy.y + (int)(sin(mina) * (float)c.rayon);
      ligne l = { x, y, c.xy.c, tmp_x, tmp_y };
      dessin_ligne(l, fb);
      x = tmp_x;
      y = tmp_y; }}}

void dessin_cercle(cercle c, pixels *fb)
{ float i = -3.14;
  float x, y, tmp_x, tmp_y;
  float pas = 3.14 / (c.rayon * 2);
  x = c.xy.x - ((float)c.rayon - 1);
  y = c.xy.y;
  while (i <= 3.14)
  { i += pas;
    tmp_x = c.xy.x + (int)(cos(i) * (float)c.rayon);
    tmp_y = c.xy.y + (int)(sin(i) * (float)c.rayon);
    ligne l = { x, y, c.xy.c, tmp_x, tmp_y };
    dessin_ligne(l, fb);
    x = tmp_x;
    y = tmp_y; }}

void dessin_disque(cercle c, pixels *fb)
{ float i = -3.14;
  float pas = 3.14 / (c.rayon * 2);
  i += pas;
  rectangle rect;
  rect.xy.c = c.xy.c;
  while (i <= -1.57)
  { rect.xy.x = c.xy.x + (int)(cos(i) * (float)c.rayon);
    rect.xy.y = c.xy.y + (int)(sin(i) * (float)c.rayon);
    rect.w = (2 * (c.xy.x - rect.xy.x) + 1);
    rect.h = (c.xy.y - rect.xy.y) + 1;
    dessin_pave(rect, fb);
    rect.xy.y += c.xy.y - rect.xy.y;
    dessin_pave(rect, fb);
    i += pas; }}

void dessin_anneau(cercle externe, cercle interne, pixels *fb)
{ dessin_disque(externe, fb);
  dessin_disque(interne, fb); }

//printf("RECT! X::%d, Y::%d, W::%d, H::%d\n", rect.xy.x, rect.xy.y, rect.w, rect.h);
//printf("COS(%f)::%f, RAYON::%f, ML::%d\n", i, cos(i), (float)c.rayon, (int)(cos(i) * (float)c.rayon));
//printf("C(%d, %d, R::%d)\n", c.xy.x, c.xy.y, c.rayon);

void dessin_ligne(ligne l, pixels *fb)
{ //if (l.xy.x >= (*fb).w || l.x2 >= (*fb).w || l.xy.y >= (*fb).h || l.y2 >= (*fb).h)
  //{ return; }
  couleurs couleur = l.xy.c;
  float i = 0;
  int tmp;
  u_int nb_pixels_dessin;
  float a = 0;
  if (l.x2 < l.xy.x)
  { tmp = l.x2;
    l.x2 = l.xy.x;
    l.xy.x = tmp;
    tmp = l.y2;
    l.y2 = l.xy.y;
    l.xy.y = tmp; }
  (*fb).shift = (l.xy.x + (l.xy.y * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  if (l.x2 > l.xy.x)
  { a = ((float)l.y2 - (float)l.xy.y) / ((float)l.x2 - (float)l.xy.x);
    if (a < 0)
    { a = -a;
      if (a > 1)
      { nb_pixels_dessin = (l.xy.y - l.y2) + 1; 
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + (((u_int)((float)i / a) - (i * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}
      else
      { nb_pixels_dessin = (l.x2 - l.xy.x) + 1;
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + ((i - ((u_int)(a * i) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}}
    else
    { if (a > 1)
      { nb_pixels_dessin = (l.y2 - l.xy.y) + 1; 
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + (((u_int)(i / a) + (i * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}
      else
      { nb_pixels_dessin = (l.x2 - l.xy.x) + 1;
        i = 0;
        while (i < nb_pixels_dessin)
        { write((*fb).pix, (char*)(&couleur), sizeof(u_int));
          lseek((*fb).pix, (*fb).shift + ((i + ((u_int)(a * i) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
          i += 1; }}}}
  else
  { if (l.y2 > l.xy.y)
    { nb_pixels_dessin = l.y2 - l.xy.y;
      i = 0;
      while (i < nb_pixels_dessin)
      { lseek((*fb).pix, (*fb).shift + (i * (*fb).w * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&couleur), sizeof(u_int));
        i += 1; }}
    else
    { nb_pixels_dessin = l.xy.y - l.y2;
      i = 0;
      while (i < nb_pixels_dessin)
      { lseek((*fb).pix, (*fb).shift - (i * (*fb).w * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&couleur), sizeof(u_int));
        i += 1; }}}
  (*fb).shift = (l.x2 + (l.y2 * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  write((*fb).pix, (char*)(&couleur), sizeof(u_int)); }

