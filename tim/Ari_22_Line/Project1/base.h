#ifndef _OLI_H
#define _OLI_H_
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <cstdlib>
#include <cstdio>
//50
#define BLOCK_SIZE_POINT 50
//10
#define BLOCK_SIZE_LINE 10
//合并点时，坐标相差TH_SAME以下时认为是同一个点，不做操作,3
#define TH_SAME 3
//合并点时，坐标相差TH_CLOSE以下时认为是相邻点，与原点去平均值后存入,15
#define TH_CLOSE 15
//TIME_X和TIME_Y是扫描次数,8*6
#define TIME_X 8
#define TIME_Y 6

//检查是否构成直线时，检查区域的次数,5
#define LINE_CHECK_TIME 5
//判断是否构成直线式，若两点的x和y差均小于TH_SKIP_LINE，判断不构成直线,10
#define TH_SKIP_LINE 10
//20
#define SCAN_RANGE 20
//检查区域的范围(必须小于SCAN_RANGE的两倍，否则可能越界访问),5
#define TH_CHECK_AREA 5


using namespace cv;
using namespace std;



typedef struct __MyPoint{
	int x;
	int y;
}myPoint;
typedef struct __MyLine{
	int x;
	int y;
	double slope;
}myLine;
typedef struct  __MyPoints{
	myPoint *array;
	int size;
	int max;
}myPoints;
typedef struct __MyLines{
	myLine *array;
	int size;
	int max;
}myLines;

myPoints initPoints();
void freeArray(myPoints *points);
int getArraySize(myPoints *points);
myPoint getPoint(myPoints *points,int index);
void setPoint(myPoints *points,int index,myPoint point);
int getArrayMax(myPoints *points);
void expandArray(myPoints *points);
void addPoint(myPoints *points,myPoint point);
void displayPoints(myPoints *points);

myLines initLines();
void freeArray(myLines *lines);
int getArraySize(myLines *lines);
myLine getLine(myLines *lines,int index);
void setLine(myLines *lines,int index,myLine line);
int getArrayMax(myLines *lines);
void expandArray(myLines *lines);
void addLine(myLines *lines,myLine line);
void displayLines(myLines *lines);

myPoint initPoint(int x,int y);
myLine initLine(int x,int y,double slope);
void displayPoint(myPoint);
void displayLine(myLine);
int isOnLine(myPoint point,myLine line,int threshold);
myLine getLineFromTwoPoints(myPoint,myPoint);
int isOnExistLines(myPoint point,myLines *lines);
int isLine(myPoints *points,int *flag,int i,int j,Mat mat);
int checkArea(Mat mat,int x,int y,double slope);
void displayMatchPoints(Mat mat,myPoints *points);
void displayMatchLines(Mat mat,myLines *lines);

void initFlag(int* flag,int size);
void removePoint(int* flag,int index);
void recoverPoint(int* flag,int index);
int isFlag(int* flag,int index);
void displayFlag(int*flag,int size);

void getPointsFromMat(Mat mat,myPoints *points);
myLines frame(Mat mat,myPoints *points);
#endif