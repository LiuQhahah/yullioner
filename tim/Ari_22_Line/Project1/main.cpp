#include <iostream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include "base.h"
#include <time.h>
#include <vector>

int main(){
	Mat mat = imread("Canny133.jpg");
	int time=clock();

	myPoints points = initPoints();
	myLines lines = frame(mat,&points);
	cout<<"MyLine:"<<clock()-time<<"ms"<<endl;


	displayMatchPoints(mat,&points);
	displayMatchLines(mat,&lines);

	/*getPointsFromMat(mat,&points);
	int size=getArraySize(&points);
	int* flag =(int*)malloc(sizeof(int)*size);
	initFlag(flag,size);
	isLine(&points,flag,0,6,mat);
	displayMatchPoints(mat,&points);*/
	while(1);
}