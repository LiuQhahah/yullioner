//#include "lineDetection.h"
myPoint initPoint(int x,int y){
	myPoint point;
	point.x=x;
	point.y=y;
	return point;
}
myLine initLine(int x,int y,double slope){
	myLine line;
	line.x=x;
	line.y=y;
	line.slope=slope;
	return line;
}
void displayPoint(myPoint point){
	cout<<"x="<<point.x<<",y="<<point.y<<endl;
}
void displayLine(myLine line){
	cout<<"x="<<line.x<<",y="<<line.y<<",k="<<line.slope<<endl;
}
//judge if a point is on the line 
int isOnLine(myPoint point,myLine line,int threshold){
	int ideay =(int)(line.slope*(point.x-line.x)+line.y);
	if(abs(ideay-point.y)<=threshold){
		return 1;	
	}else{
		return 0;
	}
	
}
//get a line from two points
myLine getLineFromTwoPoints(myPoint point1,myPoint point2){
	myLine line;
	if(point1.x<point2.x){
		line.x=point1.x;
		line.y=point1.y;
	}else{
		line.x=point2.x;
		line.y=point2.y;
	}
	line.slope=((double)point1.y-point2.y)/((double)point1.x-point2.x);
	return line;
}

void LineForCanny(Mat mat){
	Mat clone=mat.clone();
	int x=0,y=0;
	int flagx=0,flagy=0;
	int MAXx=mat.cols,MAXy=mat.rows;
	int timex=8,timey=6;
	int stepx=MAXx/(timex-1),stepy=MAXy/(timey-1);
	for(int i=0;i<timex;i++){
		if(i==timex-1){x=MAXx-5;}
		else{x=i*stepx+5;}
		line(clone,Point(x,0),Point(x,MAXy-1),Scalar(0,0,255),1,CV_AA);
		for(int j=0;j<MAXy;j++){
			y=j;
			if(mat.ptr<uchar>(y)[x*3]>180&&mat.ptr<uchar>(y)[3*x+1]>180&&mat.ptr<uchar>(y)[3*x+2]>180)
				circle(clone,Point(x,y),5,Scalar(255,255,0),1,8,3);	
		}
	}
	for(int j=0;j<timey;j++){
		if(j==timey-1){y=MAXy-5;}
		else {y=j*stepy+5;}
		line(clone,Point(0,y),Point(MAXx-1,y),Scalar(0,0,255),1,CV_AA);
	}
	imshow("Point",clone);
	waitKey(0);
}
