#include "../include/Application.h"
using namespace std;
using namespace cv;

/** Constructeur **/
Application::Application()
{
    capturing = false;

    const char* XML_FILE = "data/Personnes.xml";
    collection = new Collection(XML_FILE);
    char Filexml[]="haarcascade_frontalface_alt.xml";
    struct stat buf;
    int statResult=stat(Filexml,&buf);
    cvNamedWindow("zut", CV_WINDOW_AUTOSIZE);
    if (statResult ||buf.st_ino<0)
    {
        cerr << "xml non trouvé" << endl;
    }
    else
    {
        // Create a new Haar classifier
        cascade = (CvHaarClassifierCascade*) cvLoad(Filexml);
    }
}

/** Destructeur **/
Application::~Application()
{
    cvReleaseImage(&frame);
}

/** Enregistrement dans la base de données **/
String Application::saveTrainImg(IplImage* frame, IplImage* subImg, int nbFrame, int idPersonne)
{
    //cerr<<"dans saveTrainImg"<<endl;

    //Copie l'image dans le dossier imgResizedGray avec le nom picture+NbFrame+.jpg
    subImg = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
    cvCopy(frame, subImg, NULL);
    string Result;
    //char* str_Result[100];
    //char* str_IdPersonne[100];
    ostringstream convert;
    ostringstream convertIdPersonne;
    convert << nbFrame;
    convertIdPersonne <<idPersonne;
    Result = "imgResizedGray\\picture"+convertIdPersonne.str()+""+convert.str()+".jpg";

    IplImage *dst = cvCreateImage(cvSize(400, 400),subImg->depth,3);
    IplImage *dstGray = cvCreateImage(cvSize(400, 400),dst->depth,1);

    //resize picture
    cvResize(subImg,dst, CV_INTER_LINEAR );

    //convert in grey and in Matrice
    cvCvtColor(dst, dstGray, CV_RGB2GRAY);

    //save image
    cvSaveImage(Result.c_str(), dstGray);
    return Result;
}

/** Effectue l'apprentissage **/
void Application::training(QLabel* conteneurImage, String nom, String prenom)
{
    //cerr<<"dans training"<<endl;
    int nbFrame=0;
    int idNewPersonne=0;
    String Result="";
    CvCapture* capture;
    IplImage *subImg;
    CvSeq *faceRectSeq;
    CvMemStorage *storage = cvCreateMemStorage(0);

    //Mise à jour du fichier XML
    idNewPersonne=collection->addPersonne(nom,prenom);

    //Read the video stream
    //capture = cvCaptureFromAVI("Test.avi");
    capturing = true;
    while (capturing)
    {
        capture = cvCaptureFromCAM(1);
        frame = cvQueryFrame(capture);
        // create a window to display detected faces
        //cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);
        //cvNamedWindow("Visage", CV_WINDOW_AUTOSIZE);
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
            //cvCopy(frame, subImg, NULL);

            //On enregistre l'image du visage

            if(i<10)
            {
                //Result=saveTrainImg(frame, subImg, nbFrame, idNewPersonne);
                //collection->addImage(idNewPersonne,Result);
            }
            //Affiche l'image dans le rectangle et l'image dans son intégralité
            //cvShowImage("Visage", subImg);
            cvResetImageROI(frame);
            //cvShowImage("Sample Program", frame);
            QImage* image = IplImage2QImage(frame);
            conteneurImage->setPixmap(QPixmap::fromImage(*image));
            delete image;
        }


        int c = cvWaitKey(10);
        if( (char)c == 27 )
        {
            //cvSaveImage(s, frame);
            //exit(0);
        }
        nbFrame++;
    }
}

/** Crée un modèle **/
Ptr<FaceRecognizer> Application::creerModele()
{
    // holds images and labels
    vector<Mat> images;
    vector<int> labels;

    // ----------------------------------------------------------- //
    // -------------------------- Parse -------------------------- //
    // ----------------------------------------------------------- //

    vector<Personne> personnes = collection->getPersonnes();
    vector<Image> imageRefs;

    Personne personne;
    for(int i=0; i<(int)personnes.size(); i++)
    {
        personne = personnes[i];
        imageRefs = personne.getImageReferences();
        for(int j=0; j<(int)imageRefs.size(); j++)
        {
            IplImage* src = cvLoadImage(imageRefs[j].getChemin().c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            Mat matDst=src;
            images.push_back(matDst);
            labels.push_back(personne.getId());
        }
    }

    Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
    model->train(images, labels);
    //cerr<<"modele cree"<<endl;
    return model;
}

/** Reconnaissance de visages **/
void Application::recognition(QLabel* conteneurImage, QLabel* entete)
{
    //cerr<<"dans recognition"<<endl;
    capturing = true;
    int nbFrame=0;
    CvCapture* capture;
    IplImage *subImg;
    CvSeq *faceRectSeq;
    CvMemStorage *storage = cvCreateMemStorage(0);
    Ptr<FaceRecognizer> model;
    //Creation du modele
    model = creerModele();
    capture = cvCaptureFromCAM(0);
    while (capturing)
    {
        frame = cvQueryFrame(capture);
        // create a window to display detected faces
        //cvNamedWindow("Sample Program", CV_WINDOW_AUTOSIZE);

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
            //cvCopy(frame, subImg, NULL);

            //Affiche l'image dans le rectangle et l'image dans son intégralité
            //cvShowImage("Visage", subImg);
            cvResetImageROI(frame);
            //cvShowImage("Sample Program", frame);


            //Formatage de l'image du visage
            IplImage *dstTest = cvCreateImage(cvSize(400 , 400),subImg->depth,3);
            IplImage *dstTestGray = cvCreateImage(cvSize(400 , 400),subImg->depth,1);
            cvResize(subImg,dstTest, CV_INTER_LINEAR );
            cvCvtColor(dstTest, dstTestGray, CV_RGB2GRAY);

            //Creation de la matrice de l'image de visage test pour comparaison avec le modele
            Mat matTest=dstTestGray;

            double confidence=-1.0;
            int predicted=-1;
            // And get a prediction from the cv::FaceRecognizer:
            model->predict(matTest, predicted, confidence);

            std::ostringstream  oss;
            oss << "Vous etes : " << collection->getPersonne(predicted).getFirstName()<< " (confiance : "<<confidence<<")";
            entete->setText(oss.str().c_str());
        }

        QImage* image = IplImage2QImage(frame);
            conteneurImage->setPixmap(QPixmap::fromImage(*image));
            delete image;

        int c = cvWaitKey(10);
        if( (char)c == 27 )
        {
            //cvSaveImage(s, frame);
            //exit(0);
        }
        nbFrame++;
    }
}

/** Fonction convertissant une image QT en image OpenCV **/
IplImage* Application::QImage2IplImage(QImage *qimg)
{

    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg->width(), qimg->height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg->bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg->byteCount());
    memcpy(newdata, qimg->bits(), qimg->byteCount());
    imgHeader->imageData = (char*) newdata;
    //cvClo
    return imgHeader;
}

/** Fonction convertissant une image openCV en image QT **/
QImage*  Application::IplImage2QImage(IplImage *iplImg)
{
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1)
            {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4)
            {
                a = data[x * channels + 3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                qimg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qimg;
}

