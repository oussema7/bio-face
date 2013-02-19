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
    //char* xmlFile = "Personnes.xml";
	//Parser parser= Parser();
	//parser.Parse(xmlFile);


	CvCapture* capture;
	IplImage* frame = 0;
	char s[] = "picture.jpg";
	char Filexml[]="haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = 0;
	CvMemStorage *storage = 0;
	CvSeq *faceRectSeq;
    int nbFrame=0;

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

    //Read the video stream
	//capture = cvCaptureFromAVI("Test.avi");

	while (true)
	{
		capture = cvCaptureFromCAM(1);
		frame = cvQueryFrame( capture );
		// create a window to display detected faces
		cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
		cvNamedWindow("Visage", CV_WINDOW_AUTOSIZE);
		// display face detections
		faceRectSeq = cvHaarDetectObjects(frame,cascade,storage,1.2, 3,CV_HAAR_DO_CANNY_PRUNING,cvSize(50,50));
        CvRect *r;

		for ( int i = 0; i < (faceRectSeq? faceRectSeq->total:0); i++ )
		{
            r = (CvRect*)cvGetSeqElem(faceRectSeq,i);
			CvPoint p1 = { r->x, r->y };
			CvPoint p2 = { r->x + r->width, r->y + r->height };

			// printf(" %d %d %d %d\n", r->x, r->y, r->width, r->height);
			cvRectangle(frame,p1,p2,CV_RGB(0,255,0),1,4,0);

			//Récupération de l'image à l'interieur du rectangle r
        cvSetImageROI(frame, *r);
        //Copie l'image dans le dossier Img avec le nom picture+NbFrame+.jpg
        IplImage *subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
        cvCopy(frame, subImg, NULL);
        string Result;
        char* str_Result[100];
        ostringstream convert;
        convert << nbFrame;
        Result = "Img\\picture"+convert.str()+".jpg";

        //Affiche l'image dans le rectangle et l'image dans son intégralité
        cvSaveImage(Result.c_str(), subImg);
        cvShowImage("Visage", subImg);
        cvResetImageROI(frame);
        cvShowImage("Sample Program", frame);


		}


		int c = cvWaitKey(10);
		if( (char)c == 27 )
		{
			cvSaveImage(s, frame);
			exit(0);
		}
		nbFrame++;
	}


	// clean up and release resources
	cvReleaseImage(&frame);
	return 0;
}
