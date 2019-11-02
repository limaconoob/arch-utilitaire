
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "graphiques.h"

void icone_ethernet(pixels *fb)
{ (*fb).shift = (((*fb).w - 30) + (17 * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  dessin7x9(ethernet, Blanc, Noir, fb);
  lseek((*fb).pix, (((*fb).w - 29) + (19 * (*fb).w)) * sizeof(u_int), SEEK_SET);
  u_long k = (u_long)Vert << 32 | Vert;
  write((*fb).pix, (char*)(&k), 8);
  lseek((*fb).pix, 3 * sizeof(u_int), SEEK_CUR);
  k = (u_long)Orange << 32 | Orange;
  write((*fb).pix, (char*)(&k), 8);
  lseek((*fb).pix, (((*fb).w - 29) + (20 * (*fb).w)) * sizeof(u_int), SEEK_SET);
  k = (u_long)Vert<< 32 | Vert;
  write((*fb).pix, (char*)(&k), 8);
  lseek((*fb).pix, 3 * sizeof(u_int), SEEK_CUR);
  k = (u_long)Orange << 32 | Orange;
  write((*fb).pix, (char*)(&k), 8);
  (*fb).shift += 8 * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET); }

void nettoyage_zone(pixels *fb)
{ lseek((*fb).pix, (*fb).shift, SEEK_SET);
  rectangle r = { (*fb).w - (22 * 8), 17, 22 * 8, 10 };
  dessin_pave(r, Noir, fb); }

void afficher_debit(u_long debit, pixels *fb)
{ u_char cadran[20];
  static u_char i = 0;
  if (i > 0)
  { memset(cadran, ' ', i);
    (*fb).shift = (((*fb).w - 75 - (i * 8)) + (17 * (*fb).w)) * sizeof(u_int);
    lseek((*fb).pix, (*fb).shift, SEEK_SET);
    phrase_bande(cadran, i, Blanc, Noir, fb); }
  i = 0;
  if (debit == 0)
  { cadran[15] = '0';
    i = 1; }
  while (debit > 0 && i < 15)
  { cadran[15 - i] = (debit % 10) + '0';
    debit /= 10;
    i += 1; }
  cadran[16] = 'k';
  cadran[17] = 'B';
  cadran[18] = '/';
  cadran[19] = 's';
  (*fb).shift = (((*fb).w - 75 - (i * 8)) + (17 * (*fb).w)) * sizeof(u_int);
  lseek((*fb).pix, (*fb).shift, SEEK_SET);
  phrase_bande(&(cadran[16 - i]), i + 4, Blanc, Noir, fb); }

void debit_moyen(pixels *fb)
{ static u_char i = 0;
  static u_long debit = 0, stock_rx = 0; ///en kilo-octets
  static int ether = 0;
  u_char get[20];
  if (!ether)
  { ether = open("/sys/class/net/enp5s0/statistics/rx_bytes", O_SYNC | O_RDONLY);
    lseek(ether, 0, SEEK_SET);
    bzero(get, 20);
    read(ether, get, 20);
    stock_rx = atol(get) / 1000; }
  if (i == 6)
  { /// Rafraichir le débit
    lseek(ether, 0, SEEK_SET);
    bzero(get, 20);
    read(ether, get, 20);
    debit = (atol(get) / 1000) - stock_rx;
    stock_rx += debit;
    i = 0; }
  afficher_debit(debit, fb);
  i += 1; }

void gestion_internet(pixels *fb)
{ static int ether = 0;
  static int etat_t = 0;
  if (!ether)
  { ether = open("/sys/class/net/enp5s0/operstate", O_SYNC | O_RDONLY); }
  lseek(ether, 0, SEEK_SET);
  char get;
  read(ether, &get, 1);
  if (get == 'u')
  { debit_moyen(fb);
    icone_ethernet(fb);
    etat_t = 1; }
  else if (get == 'd' && etat_t == 1)
  { nettoyage_zone(fb);
    etat_t = 0; }}

// cat /sys/class/net/enp5s0/operstate
// cat /sys/class/net/enp5s0/statistics/rx_bytes
