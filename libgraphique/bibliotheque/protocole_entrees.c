
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <linux/input.h>

#include "graphiques.h"

u_char noyau_clavier[54] = {
'\0',
'\0',
'&',
'\0',
'"',
'\'',
'(',
'-',
'\0',
'_',
'\0',
'\0',
')',
'=',
'\0',
'\t',
'a',
'z',
'e',
'r',
't',
'y',
'u',
'i',
'o',
'p',
'^',
'$',
'\n',
'\0',
'q',
's',
'd',
'f',
'g',
'h',
'j',
'k',
'l',
'm',
'\0',
'\0',
'\0',
'*',
'w',
'x',
'c',
'v',
'b',
'n',
',',
';',
':',
'!' };

u_char noyau_shift_clavier[54] = {
'\0',
'\0',
'1',
'2',
'3',
'4',
'5',
'6',
'7',
'8',
'9',
'0',
'\0',
'+',
'\0',
'\t',
'A',
'Z',
'E',
'R',
'T',
'Y',
'U',
'I',
'O',
'P',
'"',
'\0',
'\n',
'\0',
'Q',
'S',
'D',
'F',
'G',
'H',
'J',
'K',
'L',
'M',
'%',
'\0',
'\0',
'\0',
'W',
'X',
'C',
'V',
'B',
'N',
'?',
'.',
'/',
'\0' };

u_char noyau_altgr_clavier[14] = {
'\0',
'\0',
'\0',
'~',
'#',
'{',
'[',
'|',
'`',
'\\',
'^',
'@',
']',
'}' };

/*
aReserved 0
'\0',
#define KEY_ESC			1
'\0',
#define KEY_1			2
'&',
#define KEY_2			3
'\0',
#define KEY_3			4
'"',
#define KEY_4			5
'\'',
#define KEY_5			6
'(',
#define KEY_6			7
'-',
#define KEY_7			8
'\0',
#define KEY_8			9
'_',
#define KEY_9			10
'\0',
#define KEY_0			11
'\0',
#define KEY_MINUS		12
')',
#define KEY_EQUAL		13
'=',
#define KEY_BACKSPACE		14
'\0'
#define KEY_TAB			15
'\t'
#define KEY_Q			16
'a',
#define KEY_W			17
'z',
#define KEY_E			18
'e',
#define KEY_R			19
'r',
#define KEY_T			20
't',
#define KEY_Y			21
'y',
#define KEY_U			22
'u',
#define KEY_I			23
'i',
#define KEY_O			24
'o',
#define KEY_P			25
'p',
#define KEY_LEFTBRACE		26
'^',
#define KEY_RIGHTBRACE		27
'$',
#define KEY_ENTER		28
'\n',
#define KEY_LEFTCTRL		29
'\0',
#define KEY_A			30
'q',
#define KEY_S			31
's',
#define KEY_D			32
'd',
#define KEY_F			33
'f',
#define KEY_G			34
'g',
#define KEY_H			35
'h',
#define KEY_J			36
'j',
#define KEY_K			37
'k',
#define KEY_L			38
'l',
#define KEY_SEMICOLON		39
'm',
#define KEY_APOSTROPHE		40
'\0',
#define KEY_GRAVE		41
'\0',
#define KEY_LEFTSHIFT		42
'\0',
#define KEY_BACKSLASH		43
'*',
#define KEY_Z			44
'w',
#define KEY_X			45
'x',
#define KEY_C			46
'c',
#define KEY_V			47
'v',
#define KEY_B			48
'b',
#define KEY_N			49
'n',
#define KEY_M			50
',',
#define KEY_COMMA		51
';',
#define KEY_DOT			52
':',
#define KEY_SLASH		53
'!' };
#define KEY_RIGHTSHIFT		54
#define KEY_KPASTERISK		55
#define KEY_LEFTALT		56
#define KEY_SPACE		57
#define KEY_CAPSLOCK		58
#define KEY_F1			59
#define KEY_F2			60
#define KEY_F3			61
#define KEY_F4			62
#define KEY_F5			63
#define KEY_F6			64
#define KEY_F7			65
#define KEY_F8			66
#define KEY_F9			67
#define KEY_F10			68
#define KEY_NUMLOCK		69
#define KEY_SCROLLLOCK		70
#define KEY_KP7			71
#define KEY_KP8			72
#define KEY_KP9			73
#define KEY_KPMINUS		74
#define KEY_KP4			75
#define KEY_KP5			76
#define KEY_KP6			77
#define KEY_KPPLUS		78
#define KEY_KP1			79
#define KEY_KP2			80
#define KEY_KP3			81
#define KEY_KP0			82
#define KEY_KPDOT		83
#define KEY_ZENKAKUHANKAKU	85
#define KEY_102ND		86
'<',
#define KEY_F11			87
#define KEY_F12			88
#define KEY_RO			89
#define KEY_KATAKANA		90
#define KEY_HIRAGANA		91
#define KEY_HENKAN		92
#define KEY_KATAKANAHIRAGANA	93
#define KEY_MUHENKAN		94
#define KEY_KPJPCOMMA		95
#define KEY_KPENTER		96
#define KEY_RIGHTCTRL		97
#define KEY_KPSLASH		98
#define KEY_SYSRQ		99
#define KEY_RIGHTALT		100
#define KEY_LINEFEED		101
#define KEY_HOME		102
#define KEY_UP			103
#define KEY_PAGEUP		104
#define KEY_LEFT		105
#define KEY_RIGHT		106
#define KEY_END			107
#define KEY_DOWN		108
#define KEY_PAGEDOWN		109
#define KEY_INSERT		110
#define KEY_DELETE		111
#define KEY_MACRO		112
#define KEY_MUTE		113
#define KEY_VOLUMEDOWN		114
#define KEY_VOLUMEUP		115
#define KEY_POWER		116
*/

void dessous_icone(bool_sauvegarde s, pixels *fb)
{ static u_int sauvegarde[9][7];
  u_int y = 0, x;
  if (s == Sauve)
  { (*fb).shift += sizeof(u_int);
    while (y < 9)
    { x = 0;
      while (x < 7)
      { lseek((*fb).pix, (*fb).shift + ((x + ((y + 1) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
        read((*fb).pix, (char*)(&sauvegarde[y][x]), sizeof(u_int));
        x += 1; }
      y += 1; }}
  else
  { (*fb).shift += sizeof(u_int);
    while (y < 9)
    { x = 0;
      while (x < 7)
      { lseek((*fb).pix, (*fb).shift + ((x + ((y + 1) * (*fb).w)) * sizeof(u_int)), SEEK_SET);
        write((*fb).pix, (char*)(&sauvegarde[y][x]), sizeof(u_int));
        x += 1; }
      y += 1; }}}

void pointeur_souris(peripherique *souris, u_int x, u_int y, pixels *fb)
{ (*fb).shift = ((*souris).motion_x + ((*souris).motion_y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Charge, fb);
  (*fb).shift = (x + (y * (*fb).w)) * sizeof(u_int);
  dessous_icone(Sauve, fb);
  verre7x9((*souris).icone_souris, Jaune, x, y, fb);
  (*souris).motion_x = x;
  (*souris).motion_y = y; }

void *gestion_souris(void *s)
{ peripherique periph = *((peripherique*)s);
  struct input_event e;
  while (read(periph.srs, &e, sizeof(struct input_event)))
  { if (e.type == EV_ABS)
    { if (e.code == ABS_MT_POSITION_X)
      { pointeur_souris(&periph, ((e.value - 1274) * (*periph.fb).w) / 4452, periph.motion_y, periph.fb); }
      else if (e.code == ABS_MT_POSITION_Y)
      { pointeur_souris(&periph, periph.motion_x, ((e.value - 916) * (*periph.fb).h) / 4040, periph.fb); }}
    else if (e.type == EV_KEY) 
    { if (e.value == 1) /// Appui
      { if (e.code == BTN_LEFT)
        {}
        else if (e.code == BTN_RIGHT)
        {}}
      else if (e.value == 0) /// Relâchement
      { if (e.code == BTN_LEFT)
        {}
        else if (e.code == BTN_RIGHT)
        {}}}}}

// BTN_TOOL_FINGER
// BTN_TOUCH

    //{ printf("(%lu, %lu)\n", periph.motion_x, periph.motion_y); }
    //{ printf("TYPE::%d, CODE::%d, VALUE::%d\n", e.type, e.code, e.value); }

void *gestion_clavier(void *s)
{ peripherique periph = *((peripherique*)s);
  struct input_event e;
  u_char shift = 0, altgr = 0;
  while (read(periph.clv, &e, sizeof(struct input_event)))
  { if (e.type == EV_KEY)
    { if (e.value == 1) // Appui
      { if (altgr == 0 && e.code < 54)
        { if (shift == 0)
          { //printf("NOYAU::%c, CODE::%d\n", noyau_clavier[e.code], e.code); }
            }
          else if (shift == 1)
          { //printf("NOYAU::%c, CODE::%d\n", noyau_shift_clavier[e.code], e.code); }
            }
          if (e.code == KEY_LEFTSHIFT || e.code == KEY_RIGHTSHIFT) 
          { shift = 1; }}
        if (altgr == 1 && e.code < 14)
        { //printf("NOYAU::%c, CODE::%d\n", noyau_altgr_clavier[e.code], e.code); }
          }
        if (e.code == 100)
        { altgr = 1; }
        }
      else if (e.value == 0) // Relâchement
      { if (e.code == KEY_LEFTSHIFT || e.code == KEY_RIGHTSHIFT) 
        { shift = 0; }
        else if (e.code == 100)
        { altgr = 0; }
        }
      else if (e.value == 2) // Maintien enfoncé
      {}}}
}

peripherique init_periph(pixels *fb)
{ peripherique periph;
  periph.clv = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY | O_SYNC);
  periph.srs = open("/dev/input/by-path/platform-i8042-serio-1-event-mouse", O_RDONLY | O_SYNC);
  periph.motion_x = 0;
  periph.motion_y = 0;
  periph.icone_souris = Souris_Fleche;
  periph.etat_clavier = 0;
  periph.fb = fb;
  pthread_create(&(periph.canaux[0]), (void*)0, &gestion_souris, &periph);
  pthread_create(&(periph.canaux[1]), (void*)0, &gestion_clavier, &periph);
  return (periph); }

//cat /dev/input/by-path/platform-i8042-serio-0-event-kbd
//cat /dev/input/mouse0
//vim /usr/include/linux/input.h
//cat /dev/input/by-path/platform-i8042-serio-1-mouse
