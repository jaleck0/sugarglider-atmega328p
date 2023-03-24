#include <Arduino.h>

#include "sugarglider.h"
#include "coin.h"
#include "spiker.h"

#include "TVout.h"
#include "logosprite.h"
#include "font4x6.h"
#include "glidersprites.h"
#include "drawbitmap.h"

TVout TV;

SugarGlider glider(32,9);

Coin coin(60,60);

Spiker spike(80,40);

unsigned long score = 0;

unsigned long highScore = 0;

unsigned long xAble = 1000;

typedef enum {
  MENU,
  GAME,
  OVER
} GAMESTATE;

GAMESTATE state = MENU;

void setup() {
  TV.begin(PAL,128,96);
  TV.select_font(font4x6);
  pinMode(0,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
}

int hit( double x, double y, double w, double h, double ex, double ey, double ew, double eh) {
  if ((x + h) > ex && x < (ex + ew) && 
  (y + h) > ey && y < (ey + eh)) {
    return 1;
  }
  return 0;
}

void StartGame() {
  glider.x = 32;
  glider.y = 9;
  glider.dx = 0;
  glider.dy = 0;

  coin.x = 60;
  coin.y = 60;

  spike.x = 80;
  spike.y = 40;
  
  score = 0;

  state = GAME;
}

void loop() {

  switch(state) {
    case MENU:
      //TV.clear_screen();
      static unsigned long flickerTime = 0;

      if (!digitalRead(4) && xAble <= millis()) {
        StartGame();
      }

      TV.bitmap( 25, 6, gameLogo, 2, 80, 13);
      TV.set_cursor( 64, 21);
      TV.print("BY:JALECKO");

      TV.set_cursor( 42, 32);
      TV.print("HIGHSCORE:");
      TV.print(highScore);
      
      
      if ((millis() - flickerTime) >= 500) {
        TV.set_cursor( 36, 80);
        TV.print("PRESS X TO PLAY");
        if ((millis() - flickerTime) >= 1000) {
          flickerTime = millis();
        }
      } else {
        TV.draw_rect( 31, 80, 80, 6, BLACK, BLACK);
      }

      TV.set_cursor( 26, 90);
      TV.print("USE < AND > TO STEER");

      TV.bitmap( 56, 50, gliderUpR, 2, 16, 15);

      TV.delay(16);
    break;
    case GAME:
      TV.clear_screen();
      
      glider.Update();
      coin.Update(glider.dx);
      spike.Update(glider.dx);

      coin.Draw(TV);
      spike.Draw(TV);
      glider.Draw(TV);
      
      if (hit( glider.x, glider.y, glider.width, glider.height, coin.x, coin.y, coin.width, coin.height)) 
      {
        coin.RandomPos(TV);
        score++;
        glider.dx*=1.25;
        glider.dy*=1.25;
      }

      if (hit( glider.x, glider.y, glider.width, glider.height, spike.x, spike.y, spike.width, spike.height) && glider.ht <= millis())
      {
        if (glider.spd > 3) {
          spike.RandomPos(TV);
          score++;
        } else {
          glider.dx/=2;
          glider.dy/=2;
          glider.ht = millis()+500;
        }
      }

      if (glider.y > TV.vres()) {
        state = OVER;
        xAble = millis() + 500;
        TV.set_cursor(50,40);
        TV.print("YOU FELL!");
      }

      TV.set_cursor(61,8);
      TV.print(score);

      TV.delay(16);
    break;
    case OVER:
      //TV.clear_screen();

      if (!digitalRead(4) && xAble <= millis()) {
        TV.clear_screen();
        xAble = millis() + 1000;
        if (score > highScore) {
          highScore = score;
        }
        state = MENU;
      }

      TV.delay(16);
    break;
  }
}