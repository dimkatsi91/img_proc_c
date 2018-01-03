#ifndef BMP_H
#define BMP_H


#include <stdio.h>
#include <stdlib.h>


typedef unsigned short int WORD;
typedef unsigned long int DWORD;
typedef signed long int LONG;
typedef unsigned char BYTE;
typedef long int UINT;

typedef struct {
    WORD   bfType;           /* "BM" */
  	DWORD  bfSize;           /* Size of file in bytes */
  	WORD   bfReserved1;      /* set to 0 */
  	WORD   bfReserved2;      /* set to 0 */
  	DWORD  bfOffBits;        /* Byte offset to actual bitmap data (= 54 if RGB) */
} BMFH;		//BitmapFileHeader


typedef struct {
    DWORD  biSize;           /* Size of BITMAPINFOHEADER, in bytes (= 40) */   
  	LONG   biWidth;          /* Width of image, in pixels */
  	LONG   biHeight;         /* Height of images, in pixels */
  	WORD   biPlanes;         /* Number of planes in target device (set to 1) */
  	WORD   biBitCount;       /* Bits per pixel (24 in this case) */  
  	DWORD  biCompression;    /* Type of compression (0 if no compression) */
  	DWORD  biSizeImage;      /* Image size, in bytes (0 if no compression) */
  	LONG   biXPelsPerMeter;  /* Resolution in pixels/meter of display device */
  	LONG   biYPelsPerMeter;  /* Resolution in pixels/meter of display device */
  	DWORD  biClrUsed;        /* Number of colors in the color table (if 0, use 
                              maximum allowed by biBitCount) */
  	DWORD  biClrImportant;   /* Number of important colors.  If 0, all colors 
                              are important */
} BMIH;		//BitmapInfoHeader



typedef struct {
  BMFH bmfh;
  BMIH bmih;
} HTLM_bmp_H;



#endif
