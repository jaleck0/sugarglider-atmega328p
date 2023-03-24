#ifndef SPIKER_H
#define SPIKER_H

#include "TVout.h"

class Spiker
{
public:
    Spiker( double x, double y);
    void Update(double dx);
    void Draw(TVout TV);
    void RandomPos(TVout TV);
    double x;
    double y;
    double width;
    double height;
private:
    unsigned char* sprite;    
};

#endif