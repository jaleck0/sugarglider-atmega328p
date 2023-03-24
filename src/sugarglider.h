#ifndef SUGARGLIDER_H
#define SUGARGLIDER_H

#include "TVout.h"

#define SPARKRADIUS 11
#define SPRITEOFFSET 2

class SugarGlider 
{
public:
    SugarGlider( double x, double y);
    void Update();
    void Draw(TVout TV);
	double x;
    double y;
    double width;
    double height;
    double spd;
    double dx;
    double dy;
    unsigned long ht;
private:
    unsigned char* sprite;    
};

#endif