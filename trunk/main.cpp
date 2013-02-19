#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <string.h>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <sys/stat.h>


using namespace std;
using namespace cv;


int main()
{
	CvCapture* capture;
	IplImage* frame = 0;
	char s[] = "picture.jpg";
	char Filexml[]="haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = 0;
	CvMemStorage *storage = 0;
	CvSeq *faceRectSeq;

	storage = cvCreateMemStorage(0);

	struct stat buf;
	int statResult=stat(Filexml,&buf);
	if (statResult ||buf.st_ino<0) {
		printf("xml non trouvé");
	}
	else
	{
		// Create a new Haar classifier
		cascade = (CvHaarClassifierCascade*) cvLoad(Filexml);
	}


	capture = cvCaptureFromCAM(0);

	while (true)
	{
		//Read the video stream
		//capture = cvCaptureFromCAM(0);
		frame = cvQueryFrame( capture );
		// create a window to display detected faces
		cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
		// display face detections
		faceRectSeq = cvHaarDetectObjects(frame,cascade,storage,1.2, 3,CV_HAAR_DO_CANNY_PRUNING,cvSize(50,50));

		for ( int i = 0; i < (faceRectSeq? faceRectSeq->total:0); i++ )
		{
			CvRect *r = (CvRect*)cvGetSeqElem(faceRectSeq,i);
			CvPoint p1 = { r->x, r->y };
			CvPoint p2 = { r->x + r->width, r->y + r->height };

			// printf(" %d %d %d %d\n", r->x, r->y, r->width, r->height);
			cvRectangle(frame,p1,p2,CV_RGB(0,255,0),1,4,0);
		}

		cvShowImage("Sample Program", frame);
		int c = cvWaitKey(10);
		if( (char)c == 27 )
		{
			cvSaveImage(s, frame);
			exit(0);
		}
	}


	// clean up and release resources
	cvReleaseImage(&frame);
	return 0;
}
