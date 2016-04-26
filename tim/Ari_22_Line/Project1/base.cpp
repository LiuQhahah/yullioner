#include "base.h"
myPoints initPoints(){
	myPoints points;
	points.array=(myPoint*)malloc(sizeof(myPoint)*BLOCK_SIZE_POINT);
	points.size=0;
	points.max=BLOCK_SIZE_POINT;
	return points;
}
void freeArray(myPoints *points){
	free(points->array);
	points->array=NULL;
	points->size=0;
	points->max=0;
	return;
}
int getArraySize(myPoints *points){
	return points->size;
}
myPoint getPoint(myPoints *points,int index){
	if(index>=points->size){cout<<"Out of range!"<<endl;return initPoint(-1,-1);}
	return (points->array)[index];
}
void setPoint(myPoints *points,int index,myPoint point){
	if(index>=points->size){cout<<"Out of range!"<<endl;return;}
	(points->array)[index]=point;
	return;
}
int getArrayMax(myPoints *points){
	return points->max;
}
void expandArray(myPoints *points){
	myPoint *newArray=(myPoint*)malloc(sizeof(myPoint)*(BLOCK_SIZE_POINT+points->max));
	int size=points->size;
	for(int i=0;i<size;i++){
		newArray[i]=getPoint(points,i);
	}
	points->array=newArray;
	(points->max)+=BLOCK_SIZE_POINT;
	return ;
}
void addPoint(myPoints *points,myPoint point){
	if(points->size==points->max){expandArray(points);}
	points->size+=1;
	setPoint(points,points->size-1,point);
	return;
}
void displayPoints(myPoints *points){
	cout<<"size="<<points->size;
	cout<<",max="<<points->max<<endl;
	for(int i=0;i<points->size;i++){
		cout<<"No."<<i<<":";
		displayPoint(points->array[i]);
	}
}



myLines initLines(){
	myLines lines;
	lines.array=(myLine*)malloc(sizeof(myLine)*BLOCK_SIZE_LINE);
	lines.size=0;
	lines.max=BLOCK_SIZE_LINE;
	return lines;
}
void freeArray(myLines *lines){
	free(lines->array);
	lines->array=NULL;
	lines->size=0;
	lines->max=0;
	return;
}
int getArraySize(myLines *lines){
	return lines->size;
}
myLine getLine(myLines *lines,int index){
	if(index>=lines->size){cout<<"Out of range!"<<endl;return initLine(-1,-1,-1);}
	return (lines->array)[index];
}
void setLine(myLines *lines,int index,myLine line){
	if(index>=lines->size){cout<<"Out of range!"<<endl;return;}
	(lines->array)[index]=line;
	return;
}
int getArrayMax(myLines *lines){
	return lines->max;
}
void expandArray(myLines *lines){
	myLine *newArray=(myLine*)malloc(sizeof(myLine)*(BLOCK_SIZE_POINT+lines->max));
	int size=lines->size;
	for(int i=0;i<size;i++){
		newArray[i]=getLine(lines,i);
	}
	lines->array=newArray;
	(lines->max)+=BLOCK_SIZE_LINE;
	return ;
}
void addLine(myLines *lines,myLine line){
	if(lines->size==lines->max){expandArray(lines);}
	lines->size+=1;
	setLine(lines,lines->size-1,line);
	return;
}
void displayLines(myLines *lines){
	cout<<"size="<<lines->size;
	cout<<",max="<<lines->max<<endl;
	for(int i=0;i<lines->size;i++){
		cout<<"No."<<i<<":";
		displayLine(lines->array[i]);
	}
}


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
int isOnLine(myPoint point,myLine line,int threshold){
	int ideay =(int)(line.slope*(point.x-line.x)+line.y);
	if(abs(ideay-point.y)<=threshold){
		return 1;	
	}else{
		return 0;
	}
	
}
myLine getLineFromTwoPoints(myPoint point1,myPoint point2){
	myLine line;
	if(point1.x==point2.x){
		line.x=point1.x;
		line.y=point1.y;
		line.slope=999.9;
	}
	else{
		if(point1.x<point2.x){
			line.x=point1.x;
			line.y=point1.y;
		}else{
			line.x=point2.x;
			line.y=point2.y;
			}
		line.slope=((double)point1.y-point2.y)/((double)point1.x-point2.x);
	}

	return line;
}
int isOnExistLines(myPoint point,myLines *lines){
	int size=getArraySize(lines);
	for(int i=0;i<size;i++){
		if(isOnLine(point,getLine(lines,i),20)==1){
			return 1;
		}
	}
	return 0;
}
int isLine(myPoints *points,int *flag,int i,int j,Mat mat){
	myPoint point1 = getPoint(points,i);
	myPoint point2 = getPoint(points,j);
	//printf("point1,x=%d,y=%d,point2,x=%d,y=%d\n",point1.x,point1.y,point2.x,point2.y);
	//if(point1.x==20&&point1.y==36&&point2.x==293&&point2.y==6){
	//	cout<<i<<":"<<j<<endl;
	//}
	if(abs(point1.x-point2.x)<=TH_SKIP_LINE&&abs(point1.y-point2.y)<=TH_SKIP_LINE){return 0;}
	int x,y;
	myPoint tmp;
	if(point1.x>point2.x){
		tmp=point1;
		point1=point2;
		point2=tmp;
	}
	double slope;
	if(point1.x==point2.x){
		slope=999.9;
	}else{
		slope=((double)point1.y-point2.y)/((double)point1.x-point2.x);
	}
	int stepX=(point2.x-point1.x)/(LINE_CHECK_TIME+1);
	int stepY=(point2.y-point1.y)/(LINE_CHECK_TIME+1);
	
	int sum=0;
	for(int i=0;i<LINE_CHECK_TIME;i++){
		x=point1.x+stepX*(i+1);
		y=point1.y+stepY*(i+1);
		//printf("check,x=%d,y=%d,slope=%.2f\n",x,y,slope);
		sum+=checkArea(mat,x,y,slope);
	}
	if(sum>=LINE_CHECK_TIME-1){
		//cout<<"match"<<endl;
		return 1;}
	//cout<<"No match"<<endl;
	return 0;
}
//区域内有白点就返回1，过滤消抖操作放到isLine里面
int checkArea(Mat mat,int x,int y,double slope){
	int maxX=mat.cols;
	int maxY=mat.rows;
	int basex,basey;
	int scanx,scany;
	if(abs(slope)<0.1){
		for(int i=0;i<3;i++){
			basex=x-1+i;
			basey=y;
			for(int j=0;j<TH_CHECK_AREA;j++){
				scanx=basex;
				scany=basey-TH_CHECK_AREA/2+j;
				//printf("in in check!x=%d,y=%d,maxX=%d,maxY=%d\n",scanx,scany,mat.cols,mat.rows);
				if(scanx>0&&scanx<maxX&&scany>0&&scany<maxY&&
					mat.ptr<uchar>(scany)[scanx*3]>180&&mat.ptr<uchar>(scany)[3*scanx+1]>180&&mat.ptr<uchar>(scany)[3*scanx+2]>180){
					return 1;
				}
			}
		}
	}else if(abs(slope)>900){
		for(int i=0;i<3;i++){
			basex=x;
			basey=y-1+i;
			for(int j=0;j<TH_CHECK_AREA;j++){
				scanx=basex-TH_CHECK_AREA/2+j;
				scany=basey;
				//printf("x=%d,y=%d,maxX=%d,maxY=%d\n",scanx,scany,mat.cols,mat.rows);
				if(scanx>0&&scanx<maxX&&scany>0&&scany<maxY&&
					mat.ptr<uchar>(scany)[scanx*3]>180&&mat.ptr<uchar>(scany)[3*scanx+1]>180&&mat.ptr<uchar>(scany)[3*scanx+2]>180){
					return 1;
				}
			}
		}
	}else{
		double scanSlope=-1.0/slope;
		for(int i=0;i<3;i++){
			basex=x-1+i;
			basey=(int)(slope*(basex-x)+y);
			for(int j=0;j<TH_CHECK_AREA;j++){
				scanx=basex-TH_CHECK_AREA/2+j;
				scany=(int)(scanSlope*(scanx-basex)+basey);
				//printf("x=%d,y=%d,maxX=%d,maxY=%d\n",scanx,scany,mat.cols,mat.rows);
				if(scanx>0&&scanx<maxX&&scany>0&&scany<maxY&&
					mat.ptr<uchar>(scany)[scanx*3]>180&&mat.ptr<uchar>(scany)[3*scanx+1]>180&&mat.ptr<uchar>(scany)[3*scanx+2]>180){
					return 1;
				}
			}
		}
	}

	return 0;
}
void displayMatchPoints(Mat mat,myPoints *points){
	Mat clone = mat.clone();
	int size=points->size;
	int x,y;
	for(int i =0;i<size;i++){
		x=getPoint(points,i).x;
		y=getPoint(points,i).y;
		circle(clone,Point(x,y),5,Scalar(0,255,0),1,8,3);
	}

	
	x=0,y=0;
	int flagx=0,flagy=0;
	int MAXx=mat.cols,MAXy=mat.rows;
	int stepx=MAXx/(TIME_X-1),stepy=MAXy/(TIME_Y-1);
	for(int i=0;i<TIME_X;i++){
		if(i==TIME_X-1){x=MAXx-SCAN_RANGE;}
		else{x=i*stepx+SCAN_RANGE;}
		line(clone,Point(x,0),Point(x,MAXy-1),Scalar(0,0,255),1,CV_AA);

	}
	for(int j=0;j<TIME_Y;j++){
		if(j==TIME_Y-1){y=MAXy-SCAN_RANGE;}
		else {y=j*stepy+SCAN_RANGE;}
		line(clone,Point(0,y),Point(MAXx-1,y),Scalar(0,0,255),1,CV_AA);
	}
	imshow("Point",clone);
	waitKey(0);
}
void displayMatchLines(Mat mat,myLines *lines){
	Mat clone = mat.clone();
	int size=getArraySize(lines);
	int bigx,smallx,bigy,smally;
	smallx=0;
	bigx=640;
	for(int i=0;i<size;i++){
		smally =(int)(getLine(lines,i).slope*(smallx-getLine(lines,i).x)+getLine(lines,i).y);
		bigy =(int)(getLine(lines,i).slope*(bigx-getLine(lines,i).x)+getLine(lines,i).y);
		line(clone,Point(smallx,smally),Point(bigx,bigy),Scalar(0,0,255),3,CV_AA);
	}
	imshow("Line",clone);
	waitKey(0);
	
}


void initFlag(int* flag,int size){
	for(int i=0;i<size;i++){
		flag[i]=1;
	}
}
void removePoint(int* flag,int index){
	flag[index]=0;
}
void recoverPoint(int* flag,int index){
	flag[index]=1;
}
int isFlag(int* flag,int index){
	return flag[index];
}
void displayFlag(int*flag,int size){
	for(int i=0;i<size;i++){
		cout<<"No."<<i<<":"<<flag[i]<<endl;
	}
}



void getPointsFromMat(Mat mat,myPoints * points){
	int x=0,y=0;
	int flagx=0,flagy=0;
	int MAXx=mat.cols,MAXy=mat.rows;
	int lastValue=-1;
	int stepx=MAXx/(TIME_X-1),stepy=MAXy/(TIME_Y-1);
	for(int i=0;i<TIME_X;i++){
		if(i==TIME_X-1){x=MAXx-SCAN_RANGE;}
		else{x=i*stepx+SCAN_RANGE;}
		lastValue=-1;
		for(int j=0;j<MAXy-SCAN_RANGE;j++){
			y=j;		
			if(mat.ptr<uchar>(y)[x*3]>180&&mat.ptr<uchar>(y)[3*x+1]>180&&mat.ptr<uchar>(y)[3*x+2]>180)
			{
				//判断是不是扫描位置的第一个点
				if(lastValue!=-1){
					//不是得话，判断检测到的点时候和上一点有一定距离
					if((abs(y-lastValue))<TH_SAME){
						lastValue=y;
						continue;
					}else if((abs(y-lastValue))>TH_CLOSE){
						//是的话添加点，更新lastValue
						addPoint(points,initPoint(x,y));	
						lastValue=y;
					}else{
						setPoint(points,points->size-1,initPoint(x,(lastValue+y)/2));
						lastValue=(lastValue+y)/2;
					}

				}else{
					addPoint(points,initPoint(x,y));	
					lastValue=y;
				}

			}
		}
	}
	for(int j=0;j<TIME_Y;j++){
		if(j==TIME_Y-1){y=MAXy-SCAN_RANGE;}
		else {y=j*stepy+SCAN_RANGE;}
		lastValue=-1;
		for(int i=0;i<MAXx-SCAN_RANGE;i++){
			x=i;
			if(mat.ptr<uchar>(y)[x*3]>180&&mat.ptr<uchar>(y)[3*x+1]>180&&mat.ptr<uchar>(y)[3*x+2]>180)
			{	
				if(lastValue!=-1){
					if((abs(x-lastValue))<TH_SAME){
						lastValue=x;
						continue;
					}else if((abs(x-lastValue))>TH_CLOSE){
						addPoint(points,initPoint(x,y));	
						lastValue=x;
					}else{
						setPoint(points,points->size-1,initPoint((lastValue+x)/2,y));
						lastValue=(lastValue+x)/2;
					}
				}else{
					addPoint(points,initPoint(x,y));	
					lastValue=x;
				}
			}
		}
	}

}
//用完记得free！
myLines frame(Mat mat,myPoints *points){
	getPointsFromMat(mat,points);
	int size=getArraySize(points);
	int* flag =(int*)malloc(sizeof(int)*size);
	initFlag(flag,size);

	myLines lines = initLines();
	for(int i=0;i<size;i++){
		//判断点是否可用
		if(isFlag(flag,i)==1){
			//判断点是否在已知直线上
			if(isOnExistLines(getPoint(points,i),&lines)==1){
				removePoint(flag,i);
			}else{
				for(int j=i+1;j<size;j++){
					if(isFlag(flag,j)==1&&isFlag(flag,i)==1){
						if(isLine(points,flag,i,j,mat)==1){
							addLine(&lines,getLineFromTwoPoints(getPoint(points,i),getPoint(points,j)));
							removePoint(flag,i);
							removePoint(flag,j);
							continue;
						}
					}else{
						continue;
					}
				}
			}
		}else{
			continue;
		}

	}
	return lines;
}