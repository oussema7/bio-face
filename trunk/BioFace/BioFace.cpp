// BioFace.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"

int main( int argc, const char** argv ){
	CvCapture* capture;
	IplImage* frame = 0;
	while (true)
	{
		//Read the video stream
		capture = cvCaptureFromCAM(0);
		frame = cvQueryFrame( capture );
		// create a window to display detected faces
		cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
		// display face detections
		cvShowImage("Sample Program", frame);
		int c = cvWaitKey(10);
		if( (char)c == 27 ) 
		{ 
			exit(0); 
		}
	}
	// clean up and release resources
	cvReleaseImage(&frame);
	return 0;
}

