#include "coin.h"
#include "coinsprites.h"
#include "drawbitmap.h"
#include "TVout.h"
#include <Arduino.h>

Coin::Coin( double x, double y)
:x(x)
,y(y)
{
	width = 8;
  height = 8;
  sprite = coinSpr;
}

void Coin::Update(double dx) 
{
  x -= dx;
}

void Coin::Draw(TVout TV) 
{
  if (x < -64) {
    RandomPos(TV);
  }

  if (x >= 0 && x <= TV.hres()-width)  {
    	DrawBitmap( TV, sprite, (int)x, (int)y, (millis()%300)/100);
  }
}

void Coin::RandomPos(TVout TV) 
{
	x = TV.hres()+random(120);
  y = random(88);
}