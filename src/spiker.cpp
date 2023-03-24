#include "spiker.h"
#include "spikesprites.h"
#include "drawbitmap.h"
#include "TVout.h"
#include <Arduino.h>

Spiker::Spiker( double x, double y)
:x(x)
,y(y)
{
	width = 8;
  height = 8;
  sprite = spikeSpr;
}

void Spiker::Update(double dx) 
{
  x -= dx;
}

void Spiker::Draw(TVout TV) 
{
  if (x < -64) {
    RandomPos(TV);
  }

  if (x >= 0 && x <= TV.hres()-width) {
    DrawBitmap( TV, sprite, (int)x, (int)y, (millis()%150)/50);
  }
}

void Spiker::RandomPos(TVout TV) 
{
	x = TV.hres()+random(120);
  y = random(88);
}