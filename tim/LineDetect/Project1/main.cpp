#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

void printHelp(){
	cout<<"q:quit"<<endl<<"w:open control panel"<<endl<<"s:save the frame"<<endl<<"h:help"<<endl;
	cout<<"----------------------"<<endl;
}
int main(){
	int save_number=0;
	char imageFromCamera[20];
	char imageAfterCanny[20];
	char imageAfterHough[20];
	char key;
	int g_nthreshold=100;
	int canny1=50;
	int canny2=200;
	namedWindow("Control Panel");
	cvCreateTrackbar("threshold","Control Panel",&g_nthreshold,200);
	cvCreateTrackbar("canny1","Control Panel",&canny1,500);
	cvCreateTrackbar("canny2","Control Panel",&canny2,500);
	VideoCapture cap(1);
	Mat frame;
	Mat frame2;
	Mat hough;
	printHelp();
	
	while(1){

		cap>>frame2;
		frame=frame2.clone();
		Canny(frame, frame,canny1,canny2,3);
		imshow("Video after canny",frame);
		hough=frame2.clone();
	    vector<Vec4i> mylines;
		HoughLinesP(frame, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );
		for( size_t i = 0; i < mylines.size(); i++ )
		{
			Vec4i l = mylines[i];
			line( hough, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
		}
		imshow("after hough",hough);
		save_number++;
			sprintf(imageFromCamera,"data/Camera%03d.jpg",save_number);
			sprintf(imageAfterCanny,"data/Canny%03d.jpg",save_number);
			sprintf(imageAfterHough,"data/Hough%03d.jpg",save_number);
			imwrite(imageFromCamera,frame2);
			imwrite(imageAfterCanny,frame);
			imwrite(imageAfterHough,hough);
		key = waitKey(10);
		if(key=='q'){
			break;
		}else if(key=='w'){
			namedWindow("Control Panel");
			cvCreateTrackbar("threshold","Control Panel",&g_nthreshold,200);
			cvCreateTrackbar("canny1","Control Panel",&canny1,500);
			cvCreateTrackbar("canny2","Control Panel",&canny2,500);
		}else if(key=='h'){
			printHelp();
		}
	}
}