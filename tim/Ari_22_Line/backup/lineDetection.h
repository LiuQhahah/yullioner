#ifndef OLI_H
#define OLI_H


#include "total.h"

myPoint initPoint(int x,int y);
myLine initLine(int x,int y,double slope);
void displayPoint(myPoint);
void displayLine(myLine);
int isOnLine(myPoint point,myLine line,int threshold);
myLine getLineFromTwoPoints(myPoint,myPoint);
void LineForCanny(Mat mat);


#endif