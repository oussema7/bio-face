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

//mode = 0 : training, mode = 1 : recognition
const int mode = 0;


//A MODIFIER : faire enregistrement dans base de données
void saveTrainImg(IplImage* frame, IplImage* subImg, int nbFrame)
{
    //cerr<<"dans saveTrainImg"<<endl;

    //Copie l'image dans le dossier imgResizedGray avec le nom picture+NbFrame+.jpg
    subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
    cvCopy(frame, subImg, NULL);
    string Result;
    char* str_Result[100];
    ostringstream convert;
    convert << nbFrame;
    Result = "imgResizedGray\\picture"+convert.str()+".jpg";


    IplImage *dst = cvCreateImage(cvSize(400, 400),subImg->depth,3);
    IplImage *dstGray = cvCreateImage(cvSize(400, 400),dst->depth,1);

    //resize picture
    cvResize(subImg,dst, CV_INTER_LINEAR );

    //convert in grey and in Matrice
    cvCvtColor(dst, dstGray, CV_RGB2GRAY);

    //save image
    cvSaveImage(Result.c_str(), dstGray);
}

void training(IplImage* frame, CvHaarClassifierCascade* cascade)
{
    //cerr<<"dans training"<<endl;

    char s[] = "picture.jpg";
    int nbFrame=0;
    CvCapture* capture;
    IplImage *subImg;
    CvSeq *faceRectSeq;
    CvMemStorage *storage = cvCreateMemStorage(0);
    //Read the video stream
    //capture = cvCaptureFromAVI("Test.avi");

    while (true)
    {
        capture = cvCaptureFromCAM(1);
        frame = cvQueryFrame(capture);
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
            subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
            cvCopy(frame, subImg, NULL);

            //On enregistre l'image du visage
            saveTrainImg(frame, subImg, nbFrame);

            //Affiche l'image dans le rectangle et l'image dans son intégralité
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
}

Ptr<FaceRecognizer> creerModele()
{
    //cerr<<"creation du modele"<<endl;
    //A MODIFIER => chargement depuis base de données
    //Chargement des images depuis le dossier imgResizedGray
    IplImage* src0 = cvLoadImage( "imgResizedGray/picture0.jpg" );
    IplImage* src1 = cvLoadImage( "imgResizedGray/picture1.jpg" );
    IplImage* src2 = cvLoadImage( "imgResizedGray/picture2.jpg" );

    IplImage* src3 = cvLoadImage( "imgResizedGray/picture3.jpg" );
    IplImage* src4 = cvLoadImage( "imgResizedGray/picture4.jpg" );
    IplImage* src5 = cvLoadImage( "imgResizedGray/picture5.jpg" );

    IplImage* src6 = cvLoadImage( "imgResizedGray/picture6.jpg" );
    IplImage* src7 = cvLoadImage( "imgResizedGray/picture7.jpg" );
    IplImage* src8 = cvLoadImage( "imgResizedGray/picture8.jpg" );

    //Transformation en matrices
    Mat matDst0=src0;
    Mat matDst1=src1;
    Mat matDst2=src2;

    Mat matDst3=src3;
    Mat matDst4=src4;
    Mat matDst5=src5;

    Mat matDst6=src6;
    Mat matDst7=src7;
    Mat matDst8=src8;

    // holds images and labels
    vector<Mat> images;
    vector<int> labels;

    // images for first person
    //images.push_back(imread("resize/picture1.jpg", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(0);
    images.push_back(matDst0); labels.push_back(0);
    images.push_back(matDst1); labels.push_back(0);
    images.push_back(matDst2); labels.push_back(0);
    // images for second person
    images.push_back(matDst3); labels.push_back(1);
    images.push_back(matDst4); labels.push_back(1);
    images.push_back(matDst5); labels.push_back(1);
    // images for third person
    images.push_back(matDst6); labels.push_back(2);
    images.push_back(matDst7); labels.push_back(2);
    images.push_back(matDst8); labels.push_back(2);

    Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
    model->train(images, labels);

    //cerr<<"modele cree"<<endl;
    return model;
}

// A MODIFIER !!!!!
void recognition(IplImage* frame, CvHaarClassifierCascade* cascade)
{
    //cerr<<"dans recognition"<<endl;

    char s[] = "picture.jpg";
    int nbFrame=0;
    CvCapture* capture;
    IplImage *subImg;
    CvSeq *faceRectSeq;
    CvMemStorage *storage = cvCreateMemStorage(0);
    Ptr<FaceRecognizer> model;
    //Read the video stream
    //capture = cvCaptureFromAVI("Test.avi");

    //Creation du modele
    model = creerModele();

    while (true)
    {
        capture = cvCaptureFromCAM(1);
        frame = cvQueryFrame(capture);
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
            subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
            cvCopy(frame, subImg, NULL);

            //Affiche l'image dans le rectangle et l'image dans son intégralité
            cvShowImage("Visage", subImg);
            cvResetImageROI(frame);
            cvShowImage("Sample Program", frame);


            //Formatage de l'image du visage
            IplImage *dstTest = cvCreateImage(cvSize(400 , 400),subImg->depth,3);
            IplImage *dstTestGray = cvCreateImage(cvSize(400 , 400),subImg->depth,1);
            cvResize(subImg,dstTest, CV_INTER_LINEAR );
            cvCvtColor(dstTest, dstTestGray, CV_RGB2GRAY);

            //Creation de la matrice de l'image de visage test pour comparaison avec le modele
            Mat matTest=dstTestGray;

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
}

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

        char Filexml[]="haarcascade_frontalface_alt.xml";
        CvHaarClassifierCascade* cascade = 0;
        IplImage* frame = 0;


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


        //MODE TRAIN : enregistrer les images de la camera
        if (::mode == 0)
        {
            //cerr<<"mode TRAIN"<<endl;

            training(frame, cascade);
        }
        //MODE RECOGNITION : fabriquer le modele et reconnaissance
        else if (::mode == 1)
        {
            //cerr<<"dans RECOGNITION"<<endl;

            recognition(frame, cascade);
        }

        // clean up and release resources
        cvReleaseImage(&frame);
    }
	return Msg.wParam;
}
