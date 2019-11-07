
#ifndef DISPLAY_H
  #define DISPLAY_H

  #define DISPLAY_POSITIF 1
  #define DISPLAY_NEGATIF 0

  #include "types.h"
 
  ///----------------------------- FONT 7x9 ------------------------------------
  /// Font Alphanumérique 7x9
  draw font7x9[96] =
  { 0b0000000000000000000000000000000000000000000000000000000000000000, // ' '
    0b0011000011110001111000011000001100000110000000000001100000110000, // !
    0b0110110011011000101000000000000000000000000000000000000000000000, // "
    0b0001001001001011111110010010011011001001001111111010010010010000, // #
    0b0010100011111011000111101000011111000010111100011011111000101000, // $
    0b0100001101001101001100001100000100000110000110010110010110000100, // %
    0b0011100011011001101100011100011101111011101100110110011001110110, // &
    0b0001100000110000110000000000000000000000000000000000000000000000, // '
    0b0001100001100001100000110000011000001100000110000001100000011000, // (
    0b0011000000110000001100000110000011000001100000110000110000110000, // )
    0b0000000011011000111001111111111111100111000110110000000000000000, // *
    0b0000000001100000110001111110111111000110000011000000000000000000, // +
    0b0000000000000000000000000000000000000000000001100000110000110000, // ,
    0b0000000000000000000000000000011111000000000000000000000000000000, // -
    0b0000000000000000000000000000000000000000000001100000110000000000, // .
    0b0000010000011000001000001100000100000110000010000011000001000000, // /
    0b0011100011011011000111100011110101111000111100011011011000111000, // 0
    0b0001100001110001111000001100000110000011000001100000110001111110, // 1
    0b0111110110001100000110000110000110000110000110000110001111111110, // 2
    0b0111110110001100000110000011001111000000110000011110001101111100, // 3
    0b0000110000111000111100110110110011011111110000110000011000011110, // 4
    0b1111111110000011000001100000111111000000110000011110001101111100, // 5
    0b0011110011000011000001100000111111011000111100011110001101111100, // 6
    0b1111111110001100000110000011000011000011000001100000110000011000, // 7
    0b0111110110001111000111100011011111011000111100011110001101111100, // 8
    0b0111110110001111000111100011011111100000110000011000011001111000, // 9
    0b0000000000000000011000001100000000000000000001100000110000000000, // :
    0b0000000000000000011000001100000000000000000001100000110000110000, // ;
    0b0000110000110000110000110000110000001100000011000000110000001100, // <
    0b0000000000000011111111111111000000000000001111111111111100000000, // =
    0b0110000001100000011000000110000001100001100001100001100001100000, // >
    0b0111100110011010001100001100001100000110000000000001100000110000, // ?
    0b0111110110001111001111101011110101111010111101100110000101111100, // @
    0b0001000001110001101101100011110001111111111100011110001111000110, // A
    0b1111110011001101100110110011011111001100110110011011001111111100, // B
    0b0011110011001111000011100000110000011000001100001011001100111100, // C
    0b1111100011011001100110110011011001101100110110011011011011111000, // D
    0b1111111011001101100010110100011110001101000110001011001111111110, // E
    0b1111111011001101100010110100011110001101000110000011000011110000, // F
    0b0011110011001111000011100000110000011011111100011011001100111010, // G
    0b1100011110001111000111111111111111111000111100011110001111000110, // H
    0b0111100001100000110000011000001100000110000011000001100001111000, // I
    0b0001111000011000001100000110000011000001101100110110011001111000, // J
    0b1110011011001101100110110110011110001101100110011011001111100110, // K
    0b1111000011000001100000110000011000001100000110001011001111111110, // L
    0b1100011111011111111111101011110101111000111100011110001111000110, // M
    0b1100011111001111110111101011110111111001111100011110001111000110, // N
    0b0111110110001111000111100011110001111000111100011110001101111100, // O
    0b1111110011001101100110110011011111001100000110000011000011110000, // P
    0b0111110110001111000111100011110001111010111101111011111000001110, // Q
    0b1111110011001101100110110011011111001101100110011011001111100110, // R
    0b0111110110001111000110110000001110000001101100011110001101111100, // S
    0b1111110101101000110000011000001100000110000011000001100001111000, // T
    0b1100011110001111000111100011110001111000111100011110001101111100, // U
    0b1100011110001111000111100011110001111000110110110001110000010000, // V
    0b1100011110001111000111100011110101111010111111111111011111000110, // W
    0b1100011110001101101100111110001110001111100110110110001111000110, // X
    0b1100110110011011001101100110011110000110000011000001100001111000, // Y
    0b1111111110001110001100001100011111000110000110001110001111111110, // Z
    0b0111110011000001100000110000011000001100000110000011000001111100, // [
    0b0100000011000000100000011000000100000011000000100000011000000100, //
    0b0111110000011000001100000110000011000001100000110000011001111100, // ]
    0b0001000001110001101101100011100000100000000000000000000000000000, // ^
    0b0000000000000000000000000000000000000000000000000000000011111110, // _
    0b0110000001100000011000000000000000000000000000000000000000000000, // `
    0b0000000000000001111000000110011111011001101100110110011001110110, // a
    0b1110000011000001100000111100011011001100110110011011001111011100, // b
    0b0000000000000001111101100011110000011000001100000110001101111100, // c
    0b0001110000011000001100011110011011011001101100110110011001110110, // d
    0b0000000000000001111101100011111111111000001100000110001101111100, // e
    0b0011110011001101100010110000111100001100000110000011000011110000, // f
    0b0000000000000001110111100110110011001111100000110110011001111000, // g
    0b1110000011000001100000110110011101101100110110011011001111100110, // h
    0b0011000001100000000000111000001100000110000011000001100001111000, // i
    0b0000011000001100000000000111000001100000111100011110001101111100, // j
    0b1110000011000001100110110110011110001111000110110011001111100110, // k
    0b0111000001100000110000011000001100000110000011000001100001111000, // l
    0b0000000000000011101101111111110101111010111101011110101111010110, // m
    0b0000000000000011011100110011011001101100110110011011001111100110, // n
    0b0000000000000001111101100011110001111000111100011110001101111100, // o
    0b0000000000000011011100110011011001101111100110000011000011110000, // p
    0b0000000000000001110111100110110011001111100000110000011000011110, // q
    0b0000000000000011011100111011011001101100000110000011000011110000, // r
    0b0000000000000001111101100011011000000111000000110110001101111100, // s
    0b0001000001100000110001111110001100000110000011000001101100011100, // t
    0b0000000000000011001111100110110011011001101100110110011001110110, // u
    0b0000000000000011000111100011110001111000111100011011011000111000, // v
    0b0000000000000011000111100011110101111010111101011111111101101100, // w
    0b0000000000000011000110110110001110000111000011100011011011000110, // x
    0b0000000000000011000111100011110001101111110000011000011011111000, // y
    0b0000000000000011111111100110000110000110000110000110001111111110, // z
    0b0001110001100000110000011000111000000110000011000001100000011100, // {
    0b0011000001100000110000011000001100000110000011000001100000110000, // |
    0b0111000000110000011000001100000011100011000001100000110001110000, // }
    0b0000000000000001110011001001100111000000000000000000000000000000, // ~
    0b0000000000000000000000000000000000000000000000000000000000000000, // DEL
  };

/*
0b
0000000
0000000
0000000
0000000
0000000
0000000
0000000
0000000
0000000
0;
*/

  draw icones7x9[14] =
  { 0b0000000011011001101100000000000000001000101001001011011000000000, // :3
    0b0000000011011001101100000000000000010000011100011011111000000000, // :)
    0b0000000011011001101100000000000000001111101100011100000100000000, // :(
    0b0000000011011001101100000000000000000111000111110001110000000000, // :O
    0b0000000011011001101100000000000000011111111111111000000000000000, // :|

    0b1000110011100100011100011000011000011100001011000101100101101100, // Limaconoob
    0b0001000001110000010111101011110100110011100111000000100000111000, // Usb
    0b0001111001000001001110101000100101110100101010100101010110101010, // Wifi
    0b0000000111111111000111100011100000110000011000001111111100000000, // Ethernet

    0b0010000001000011111000010000001000000000000000000000000000000000, // Plus
    0b0111000100010010101001000100011100000000000000000000000000000000, // Marqueur
    0b0000000000000000100000011000001110000111110010100000001000000000, // Flèche
    0b0000000000000000100000010000001111001111100111110001110000111000, // Doigt

    0b0000000000000000000000000000000000000000000000000000000000000000, // Gomme
  };

  ///----------------------------- FONT 3x5 ------------------------------------
  /// Font Alphanumérique 3x5
  minip font3x5[96] =
  { 0b0000000000000000, // ' '
    0b0100100100000100, // !
    0b1011010000000000, // "
    0b1011111011111010, // #
    0b0101110101110100, // $
    0b1000010101000010, // %
    0b0101010101011100, // &
    0b0100100000000000, // '
    0b0101001001000100, // (
    0b0100010010010100, // )
    0b1010101010000000, // *
    0b0000101110100000, // +
    0b0000000000101000, // ,
    0b0000000000001110, // -
    0b0000000000100000, // .
    0b0010110101101000, // /
    0b0101011011010100, // 0
    0b0101100100100100, // 1
    0b1100010101001110, // 2
    0b1100010100011100, // 3
    0b0010111011110010, // 4
    0b1111001110011100, // 5
    0b0101001101010100, // 6
    0b1110010100100100, // 7
    0b0101010101010100, // 8
    0b0101010110010100, // 9
    0b0000100000100000, // :
    0b0000100000101000, // ;
    0b0010101000100010, // <
    0b0001110001110000, // =
    0b1000100010101000, // >
    0b1100010100000100, // ?
    0b1101111111001110, // @
    0b0101011111011010, // A
    0b1101011101011100, // B
    0b0111001001000110, // C
    0b1101011011011100, // D
    0b1111001101001110, // E
    0b1111001101001000, // F
    0b0111001011010100, // G
    0b1011011111011010, // H
    0b1110100100101110, // I
    0b0010010011010100, // J
    0b1011011101011010, // K
    0b1001001001001110, // L
    0b1011111011011010, // M
    0b1011111111011010, // N
    0b0101011011010100, // O
    0b1101011101001000, // P
    0b0101011010100010, // Q
    0b1101011101011010, // R
    0b0111000100011100, // S
    0b1110100100100100, // T
    0b1011011011010110, // U
    0b1011011010100100, // V
    0b1011011011111110, // W
    0b1011010101011010, // X
    0b1011110100100100, // Y
    0b1110010101001110, // Z
    0b1101001001001100, // [
    0b1001100100110010, //
    0b0110010010010110, // ]
    0b0101010000000000, // ^
    0b0000000000001110, // _
    0b1000100000000000, // `
    0b0000111011010110, // a
    0b1001001101011100, // b
    0b0000111001000110, // c
    0b0010010111010110, // d
    0b0000111011100110, // e
    0b0101001101001000, // f
    0b0001101110011100, // g
    0b1001001101011010, // h
    0b0100000100100100, // i
    0b0010000011010100, // j
    0b1001001011101010, // k
    0b0100100100100110, // l
    0b0001111111011010, // m
    0b0001101011011010, // n
    0b0000101011010100, // o
    0b0000101011101000, // p
    0b0000101010110010, // q
    0b0001011101001000, // r
    0b0000111100011100, // s
    0b0100110100100110, // t
    0b0001011011010110, // u
    0b0001011011010100, // v
    0b0001011011110100, // w
    0b0001011100111010, // x
    0b0001010110010100, // y
    0b0001110101001110, // z
    0b0110101000100110, // {
    0b0100100100100100, // |
    0b1100100010101100, // }
    0b0001101110110000, // ~
    0b0000000000000000, // DEL
  };


/*
0000011111100000
0001111111111000
0001111111111000
0011111111111100, //0
0111110000111110
0111100000011110
0111100000011110
0111100000011110, //0
0111100000011110
0111100000011110
0111100000011110
0111100000011110, //0
0111100000011110
0111100000011110
0111100000011110
0111110000111110, //0
0011111111111100
0001111111111000
0001111111111000
0000011111100000, //0
*/

  /// Nombres pour le Chrono, Font 16x20
  draw nombres[50] =
  { 0b0000011111100000000111111111100000011111111110000011111111111100, //0
    0b0111110000111110011110000001111001111000000111100111100000011110, //0
    0b0111100000011110011110000001111001111000000111100111100000011110, //0
    0b0111100000011110011110000001111001111000000111100111110000111110, //0
    0b0011111111111100000111111111100000011111111110000000011111100000, //0

    0b0000000111100000000000011110000000000111111000000000111111100000, //1
    0b0111111111100000011111111110000001111111111000000000000111100000, //1
    0b0000000111100000000000011110000000000001111000000000000111100000, //1
    0b0000000111100000000000011110000000000001111000000000000111100000, //1
    0b0000000111100000011111111111111001111111111111100111111111111110, //1

    0b0001111111111000000111111111100001111111111111100111110000011110, //2
    0b0111000000011110000000000011111000000000011111000000000011111000, //2
    0b0000000111110000000000111110000000000111110000000000111110000000, //2
    0b0001111100000000001111100000000001111100000000000111100000000000, //2
    0b0111100000011110011111111111111001111111111111100111111111111110, //2

    0b0001111111110000001111111111100001111111111111000111100000111100, //3
    0b0000000000011110000000000001111000000000000111100000000000111100, //3
    0b0000011111111000000001111111100000000111111110000000000000111100, //3
    0b0000000000011110000000000001111000000000000111100000000000011110, //3
    0b0111100000111100011111111111110000111111111110000001111111110000, //3

    0b0000000000011110000000000011110000000000011110000000000011110000, //4
    0b0000000111100000000000111100000000000111100000000000111100000000, //4
    0b0001111000000000001111000011100001111000001110000111111111111100, //4
    0b0111111111111100011111111111110000000000001110000000000000111000, //4
    0b0000000000111000000000001111111000000000111111100000000011111110, //4

    0b0111111111111110011111111111111001111111111111100111100000000000, //5
    0b0111100000000000011110000000000001111000000000000111100000000000, //5
    0b0111111111100000011111111111100001111111111111000000000000111100, //5
    0b0000000000011110000000000001111000000000000111100000000000011110, //5
    0b0111100000111110011111111111111000111111111111000000111111110000, //5

    0b0000111111110000001111111111110000111111111111000111110000011110, //6
    0b0111100000000000011110000000000001111000000000000111100000000000, //6
    0b0111111111100000011111111111100001111111111111000111110000111100, //6
    0b0111100000011110011110000001111001111000000111100111100000011110, //6
    0b0111110000111110001111111111110000111111111111000000111111110000, //6

    0b0111111111111110011111111111111001111111111111100111100000011110, //7
    0b0000000000011110000000000011111000000000011111000000000011111000, //7
    0b0000000111110000001111111111110000111111111111000011111111111100, //7
    0b0000001111000000000000111100000000000011110000000000001111000000, //7
    0b0000001111000000000011111111000000001111111100000000111111110000, //7

    0b0000111111110000001111111111110000111111111111000111110000111110, //8
    0b0111100000011110011110000001111001111000000111100111110000111110, //8
    0b0111111111111110001111111111110000011111111110000011110000111100, //8
    0b0111100000011110011110000001111001111000000111100111100000011110, //8
    0b0111110000111110001111111111110000111111111111000000111111110000, //8

    0b0000111111110000001111111111110000111111111111000111110000111110, //9
    0b0111100000011110011110000001111001111000000111100111100000011110, //9
    0b0111110000111110001111111111111000011111111111100000011111011110, //9
    0b0000000000011110000000000001111000000000000111100000000000011110, //9
    0b0111100000111110001111111111110000111111111111000000111111110000, //9
  };
  
#endif
/*
0b0011100
  0110110
  1100011
  1100111
  1101011
  1101011
  1110011
  0110110
  00111000, //0

0b0001100
  0011100
  1111100
  0001100
  0001100
  0001100
  0001100
  0001100
  00111100, //1

0b0111110
  1100011
  0000011
  0000110
  0001100
  0011000
  0110000
  1100011
  11111110, //2

0b0111110
  1100011
  0000011
  0000011
  0011110
  0000011
  0000011
  1100011
  01111100, //3

0b0000110
  0001110
  0011110
  0110110
  1100110
  1111111
  0000110
  0000110
  00011110, //4

0b1111111
  1100000
  1100000
  1100000
  1111110
  0000011
  0000011
  1100011
  01111100, //5

0b0011110
  0110001
  1100000
  1100000
  1101110
  1110011
  1100001
  1110011
  01111100, //6

0b1111111
  1100011
  0000011
  0000110
  0001100
  0011110
  0001100
  0001100
  00111100, //7

0b0111110
  1100011
  1000001
  1100011
  0111110
  1100011
  1000001
  1100011
  01111100, //8

0b0111110
  1100111
  1000011
  1100111
  0111011
  0000011
  0000011
  1000110
  01111000, //9
*/

/*
0b0001111111111000
  0001111111111000
  0111111111111110
  0111110000011110, //2
0b0111000000011110
  0000000000111110
  0000000001111100
  0000000011111000, //2
0b0000000111110000
  0000001111100000
  0000011111000000
  0000111110000000, //2
0b0001111100000000
  0011111000000000
  0111110000000000
  0111100000000000, //2
0b0111100000011110
  0111111111111110
  0111111111111110
  0111111111111110, //2


0b0000000000011110
  0000000000111100
  0000000001111000
  0000000011110000, //4
0b0000000111100000
  0000001111000000
  0000011110000000
  0000111100000000, //4
0b0001111000000000
  0011110000000000
  0111100001110000
  0111111111111100, //4
0b0111111111111100
  0111111111111100
  0000000001110000
  0000000001110000, //4
0b0000000001110000
  0000001111111110
  0000001111111110
  0000001111111110, //4

0b0111111111111110
  0111111111111110
  0111111111111110
  0111100000000000, //5
0b0111100000000000
  0111100000000000
  0111100000000000
  0111100000000000, //5
0b0111111111100000
  0111111111111000
  0111111111111100
  0000000000111100, //5
0b0000000000011110
  0000000000011110
  0000000000011110
  0000000000011110, //5
0b0111100000111110
  0111111111111110
  0011111111111100
  0000111111110000, //5

0b0000111111110000
  0011111111111100
  0011111111111100
  0111110000011110, //6
0b0111100000000000
  0111100000000000
  0111100000000000
  0111100000000000, //6
0b0111111111100000
  0111111111111000
  0111111111111100
  0111110000111100, //6
0b0111100000011110
  0111100000011110
  0111100000011110
  0111100000011110, //6
0b0111110000111110
  0011111111111100
  0011111111111100
  0000111111110000, //6
  
0b0111111111111110
  0111111111111110
  0111111111111110
  0111100000011110, //7
0b0000000000011110
  0000000000111110
  0000000001111100
  0000000011111000, //7
0b0000000111110000
  0011111111111100
  0011111111111100
  0011111111111100, //7
0b0000001111000000
  0000001111000000
  0000001111000000
  0000001111000000, //7
0b0000001111000000
  0000111111110000
  0000111111110000
  0000111111110000, //7

0b0000111111110000
  0011111111111100
  0011111111111100
  0111110000111110, //8
0b0111100000011110
  0111100000011110
  0111100000011110
  0111110000111110, //8
0b0111111111111110
  0011111111111100
  0001111111111000
  0011110000111100, //8
0b0111100000011110
  0111100000011110
  0111100000011110
  0111100000011110, //8
0b0111110000111110
  0011111111111100
  0011111111111100
  0000111111110000, //8

0b0000111111110000
  0011111111111100
  0011111111111100
  0111110000111110, //9
0b0111100000011110
  0111100000011110
  0111100000011110
  0111100000011110, //9
0b0111110000111110
  0011111111111110
  0001111111111110
  0000011111011110, //9
0b0000000000011110
  0000000000011110
  0000000000011110
  0000000000011110, //9
0b0111100000111110
  0011111111111100
  0011111111111100
  0000111111110000, //9
*/

/*
0b1000110
  0111001
  0000110
  0001100
  0011000
  0110000
  1011000
  1011001
  01101100, //Limaconoob

0b1111100
  0110110
  0110011
  0110011
  0110011
  0110011
  0110011
  0110110
  11111000;, //D

0b1111111
  0110011
  0110001
  0110100
  0111100
  0110100
  0110001
  0110011
  11111110;, //E

0b1111111
  0110011
  0110001
  0110100
  0111100
  0110100
  0110000
  0110000
  11110000;, //F

0b0011110
  0110011
  1100001
  1100000
  1100000
  1101111
  1100011
  0110011
  00111010, //G

0b1100011
  1100011
  1100011
  1111111
  1111111
  1100011
  1100011
  1100011
  11000110, //H

0b0111100
  0011000
  0011000
  0011000
  0011000
  0011000
  0011000
  0011000
  01111000, //I
  
0b0001111
  0000110
  0000110
  0000110
  0000110
  0000110
  1100110
  1100110
  01111000, //J
  
0b1110011
  0110011
  0110011
  0110110
  0111100
  0110110
  0110011
  0110011
  11100110, //K
  
0b1111000
  0110000
  0110000
  0110000
  0110000
  0110000
  0110001
  0110011
  11111110, //L

0b0100010
  1110111
  1111111
  1101011
  1101011
  1100011
  1100011
  1100011
  11000110, //M

0b0100011
  1110011
  1111011
  1101011
  1101111
  1100111
  1100011
  1100011
  11000110, //N

0b0111110
  1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  01111100, //O

0b1111110
  0110011
  0110011
  0110011
  0111110
  0110000
  0110000
  0110000
  11110000, //P
  
0b0111110
  1100011
  1100011
  1100011
  1101011
  1101111
  0111110
  0000110
  00001110, //Q

0b1111110
  0110011
  0110011
  0110011
  0111110
  0110110
  0110011
  0110011
  11100110, //R
  
0b0111110
  1100011
  1100011
  0110000
  0011100
  0000110
  1100011
  1100011
  01111100, //S
  
0b1111110
  1011010
  0011000
  0011000
  0011000
  0011000
  0011000
  0011000
  01111000, //T

0b1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  01111100, //U

0b1100011
  1100011
  1100011
  1100011
  1100011
  1100011
  0110110
  0011100
  00010000, //V

0b1100011
  1100011
  1100011
  1100011
  1101011
  1101011
  1111111
  1110111
  01000100, //W

0b1100110
  1100110
  1100110
  1100110
  0111100
  0011000
  0011000
  0011000
  01111000, //Y
  
0b1111111
  1100011
  1000110
  0001100
  0111110
  0011000
  0110001
  1100011
  11111110, //Z
*/
