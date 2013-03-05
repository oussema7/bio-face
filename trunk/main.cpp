#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <string.h>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include <windows.h>

#include "Collection.h"

using namespace std;
using namespace cv;

const char g_szClassName[] = "mainWindowClass";

//The Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

//Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ----------------------------------------------------------- //
    // -------------------------- Parse -------------------------- //
    // ----------------------------------------------------------- //
    const char* xmlFile = "data/Personnes.xml";
    Collection collection(xmlFile);


    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    // ----------------------------------------------------------- //

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);


    //Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Bio-Face",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);

	CvCapture* capture;
	IplImage* frame = 0;
	char s[] = "picture.jpg";
	char Filexml[]="haarcascade_frontalface_alt.xml";
	CvHaarClassifierCascade* cascade = 0;
	CvMemStorage *storage = 0;
	CvSeq *faceRectSeq;
	IplImage *subImg;
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
            subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
            cvCopy(frame, subImg, NULL);
            string Result;
            char* str_Result[100];
            ostringstream convert;
            convert << nbFrame;
            Result = "Img\\picture"+convert.str()+".jpg";

            //Affiche l'image dans le rectangle et l'image dans son intégralité
            //cvSaveImage(Result.c_str(), subImg);
            cvShowImage("Visage", subImg);
            cvResetImageROI(frame);
            cvShowImage("Sample Program", frame);


 IplImage* src0 = cvLoadImage( "Img/picture1.jpg" );
        IplImage* src1 = cvLoadImage( "Img/picture2.jpg" );
        IplImage* src2 = cvLoadImage( "Img/picture3.jpg" );
        IplImage* src3 = cvLoadImage( "Img/picture30.jpg" );
        IplImage* src4 = cvLoadImage( "Img/picture31.jpg" );
        IplImage* src5 = cvLoadImage( "Img/picture32.jpg" );
        IplImage* src6 = cvLoadImage( "Img/picture100.jpg" );
        IplImage* src7 = cvLoadImage( "Img/picture101.jpg" );
        IplImage* src8 = cvLoadImage( "Img/picture102.jpg" );

        IplImage *dst = cvCreateImage(cvSize(400 , 400 ),src0->depth,3);
        IplImage *dst1 = cvCreateImage(cvSize(400 , 400 ),src1->depth,3);
        IplImage *dst2 = cvCreateImage(cvSize(400 , 400),src2->depth,3);
        IplImage *dst3 = cvCreateImage(cvSize(400 , 400 ),src3->depth,3);
        IplImage *dst4 = cvCreateImage(cvSize(400 , 400),src4->depth,3);
        IplImage *dst5 = cvCreateImage(cvSize(400 , 400),src5->depth,3);
        IplImage *dstTest = cvCreateImage(cvSize(400 , 400),subImg->depth,3);
        IplImage *dst6 = cvCreateImage(cvSize(400 , 400 ),src6->depth,3);
        IplImage *dst7 = cvCreateImage(cvSize(400 , 400),src7->depth,3);
        IplImage *dst8 = cvCreateImage(cvSize(400 , 400),src8->depth,3);
        IplImage *dstTestGray = cvCreateImage(cvSize(400 , 400),subImg->depth,1);
        IplImage *dstGray = cvCreateImage(cvSize(400 , 400),dst->depth,1);
        IplImage *dst1Gray = cvCreateImage(cvSize(400 , 400),dst1->depth,1);
        IplImage *dst2Gray = cvCreateImage(cvSize(400 , 400),dst2->depth,1);
        IplImage *dst3Gray = cvCreateImage(cvSize(400 , 400),dst3->depth,1);
        IplImage *dst4Gray = cvCreateImage(cvSize(400 , 400),dst4->depth,1);
        IplImage *dst5Gray = cvCreateImage(cvSize(400 , 400),dst5->depth,1);
        IplImage *dst6Gray = cvCreateImage(cvSize(400 , 400),dst6->depth,1);
        IplImage *dst7Gray = cvCreateImage(cvSize(400 , 400),dst7->depth,1);
        IplImage *dst8Gray = cvCreateImage(cvSize(400 , 400),dst8->depth,1);


            //train

            // holds images and labels
            vector<Mat> images;
            vector<int> labels;

            //resize picture

            cvResize(src0,dst, CV_INTER_LINEAR );
            cvResize(src1,dst1, CV_INTER_LINEAR );
            cvResize(src2,dst2, CV_INTER_LINEAR );
            cvResize(src3,dst3, CV_INTER_LINEAR );
            cvResize(src4,dst4, CV_INTER_LINEAR );
            cvResize(src5,dst5, CV_INTER_LINEAR );
            cvResize(subImg,dstTest, CV_INTER_LINEAR );
            cvResize(src6,dst6, CV_INTER_LINEAR );
            cvResize(src7,dst7, CV_INTER_LINEAR );
            cvResize(src8,dst8, CV_INTER_LINEAR );

            /*cvSaveImage( "resize\\picture1.jpg", dst );
            cvSaveImage( "resize\\picture2.jpg", dst1 );
            cvSaveImage( "resize\\picture3.jpg", dst2 );
            cvSaveImage( "resize\\picture30.jpg", dst3 );
            cvSaveImage( "resize\\picture31.jpg", dst4 );
            cvSaveImage( "resize\\picture32.jpg", dst5 );
            //cvSaveImage( "resize\\pictureTest.jpg", dstTest );
            cvSaveImage( "resize\\picture100.jpg", dst6 );
            cvSaveImage( "resize\\picture101.jpg", dst7 );
            cvSaveImage( "resize\\picture102.jpg", dst8 );*/

            //convert in grey and in Matrice
            cvCvtColor(dst, dstGray, CV_RGB2GRAY);
            Mat matDst=dstGray;
            cvCvtColor(dst1, dst1Gray, CV_RGB2GRAY);
            Mat matDst1=dst1Gray;
            cvCvtColor(dst2, dst2Gray, CV_RGB2GRAY);
            Mat matDst2=dst2Gray;
            cvCvtColor(dst3, dst3Gray, CV_RGB2GRAY);
            Mat matDst3=dst3Gray;
            cvCvtColor(dst4, dst4Gray, CV_RGB2GRAY);
            Mat matDst4=dst4Gray;
            cvCvtColor(dst5, dst5Gray, CV_RGB2GRAY);
            Mat matDst5=dst5Gray;
            cvCvtColor(dst6, dst6Gray, CV_RGB2GRAY);
            Mat matDst6=dst6Gray;
            cvCvtColor(dst7, dst7Gray, CV_RGB2GRAY);
            Mat matDst7=dst7Gray;
            cvCvtColor(dst8, dst8Gray, CV_RGB2GRAY);
            Mat matDst8=dst8Gray;

            cvCvtColor(dstTest, dstTestGray, CV_RGB2GRAY);
            Mat matTest=dstTestGray;


            // images for first person
            //images.push_back(imread("resize/picture1.jpg", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(0);
            images.push_back(matDst); labels.push_back(0);
            images.push_back(matDst1); labels.push_back(0);
            images.push_back(matDst2); labels.push_back(0);
            // images for second person
            images.push_back(matDst3); labels.push_back(1);
            images.push_back(matDst4); labels.push_back(1);
            images.push_back(matDst5); labels.push_back(1);

            images.push_back(matDst6); labels.push_back(2);
            images.push_back(matDst7); labels.push_back(2);
            images.push_back(matDst8); labels.push_back(2);





            Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
            model->train(images, labels);

           //Mat img = imread("", CV_LOAD_IMAGE_GRAYSCALE);
            // And get a prediction from the cv::FaceRecognizer:
            int predicted = model->predict(matTest);

            cout<<predicted<<endl;

            if (predicted==0){
                cout<<"camille"<<endl;
            }
            else if (predicted==1){
                cout<<"Marie"<<endl;
            }
             else if (predicted==2){
                cout<<"Christopher"<<endl;
            }
            else{
                cout<<"Personne inconnue"<<endl;
            }

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
    }
	return Msg.wParam;
}
