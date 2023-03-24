#include "drawbitmap.h"
#include "TVout.h"
#include <avr/pgmspace.h>

void DrawBitmap( TVout tv,unsigned char* spriteP, int xPos, int yPos, int frame) {
  unsigned char hideH = 0;
  
  if (yPos < 0) {
    hideH=-yPos;
    yPos=0;
  }
  unsigned char w,l;
  w = pgm_read_byte(spriteP);
  l = pgm_read_byte(spriteP+1);
  unsigned char showL = l;

  if (hideH < l && yPos<tv.vres() ){
    tv.bitmap(xPos,yPos,spriteP,2 + hideH*(w/8) + frame*((w/8) + l)-frame ,w,showL-hideH);
  }
}