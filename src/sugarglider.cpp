#include <Arduino.h>
#include "sugarglider.h"
#include "glidersprites.h"
#include "drawbitmap.h"
#include "TVout.h"

SugarGlider::SugarGlider( double x, double y)
:x(x)
,y(y)
{
	dx = 0;
	dy = 0;
	width = 16;
  height = 12;
  ht = 0;
}

void SugarGlider::Update() 
{
  dy += 0.07;
  spd = sqrt((dx*dx) + (dy*dy));

  if (spd > 3.3) {
    spd = 3.3;
  }

  double angl = atan2(dy,dx);
  
  if (ht <= millis()) {
    if (!digitalRead(0)) {
      angl -= 0.1;
    }

    if (!digitalRead(3)) {
      angl += 0.1;
    }
  }

  dx = spd*cos(angl);
  dy = spd*sin(angl);

  y += dy;

  if (dx>0) {
    if (dy < -0.5) {
      sprite = gliderUpR;
    }else if (dy > 0.5) {
      sprite = gliderDownR;
    } else if (dy < 0.5 && dy > -0.5){
      sprite = gliderNeutralR;
    }
  } 

  if (dx<0) {
    if (dy < -0.5) {
      sprite = gliderUpL;
    }else if (dy > 0.5) {
      sprite = gliderDownL;
    } else if (dy < 0.5 && dy > -0.5){
      sprite = gliderNeutralL;
    }
  }

}

void SugarGlider::Draw(TVout TV) 
{
	DrawBitmap( TV, sprite, (int)x, (int)y-SPRITEOFFSET,0);
	if (spd > 3 && ((millis()/30)%3)==0 && y+(height/2) > SPARKRADIUS && (TV.vres() - (y+(height/2))) > SPARKRADIUS) {
		TV.draw_circle(x+(width/2), y+(height/2), SPARKRADIUS, WHITE, WHITE);
	}
}