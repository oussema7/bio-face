#include "Application.h"
using namespace std;
using namespace cv;

/** Constructeur **/
Application::Application()
{
    const char* XML_FILE = "data/Personnes.xml";
    collection = new Collection(XML_FILE);
    char Filexml[]="haarcascade_frontalface_alt.xml";
    cascade = 0;
    frame = 0;
    struct stat buf;
    int statResult=stat(Filexml,&buf);
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
Application::~Application(){
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
void Application::training(IplImage* frame, CvHaarClassifierCascade* cascade, String nom, String prenom)
{
    //cerr<<"dans training"<<endl;

    char s[] = "picture.jpg";
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
            Result=saveTrainImg(frame, subImg, nbFrame, idNewPersonne);
            if(i<10){
                collection->addImage(idNewPersonne,Result);
            }
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
    for(int i=0;i<(int)personnes.size();i++){
        personne = personnes[i];
        imageRefs = personne.getImageReferences();
        for(int j=0;j<(int)imageRefs.size();j++){
            IplImage* src = cvLoadImage(imageRefs[j].getChemin().c_str(), CV_LOAD_IMAGE_GRAYSCALE);
            Mat matDst=src;
            images.push_back(matDst); labels.push_back(personne.getId());
        }
    }

    Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
    model->train(images, labels);
    //cerr<<"modele cree"<<endl;
    return model;
}

/** Reconnaissance de visages **/
void Application::recognition(IplImage* frame, CvHaarClassifierCascade* cascade)
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
        capture = cvCaptureFromCAM(0);
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

            double confidence=-1.0;
            int predicted=-1;
            // And get a prediction from the cv::FaceRecognizer:
            model->predict(matTest, predicted, confidence);

            cout<< predicted << " " << collection->getPersonne(predicted).getFirstName()<< "/ confiance : "<<confidence << endl;

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
