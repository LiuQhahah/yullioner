#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define TIME 1
using namespace cv;
int main(){
	VideoCapture capture(0);
	Mat frame;
	char path[100]="/home/monk/Workspace/opencv/getPicFromCamera/data/";
	int recentFile=0;
	char flagFile[100];
	char lastFlagFile[100];
	char fileName[100];
	sprintf(flagFile,"%s%d",path,recentFile);
	int fd=open(flagFile,O_WRONLY|O_CREAT);
	close(fd);
	while(1){
		capture>>frame;

		sprintf(lastFlagFile,"%s%d",path,recentFile);
		recentFile++;
		sprintf(flagFile,"%s%d",path,recentFile);
		sprintf(fileName,"%sfile%06d.jpg",path,recentFile);
		imwrite(fileName,frame);
		rename(lastFlagFile,flagFile);
//		imshow("Loading Video",frame);
		if(waitKey(TIME)==27){
			break;
		}

	}
	return 0;

}
