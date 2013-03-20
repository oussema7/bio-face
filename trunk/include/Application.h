#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <String>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include "Collection.h"
#include <QtGui/QImage>
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>

using namespace cv;

class Application
{
public:
    Application();
    virtual ~Application();
    String saveTrainImg(IplImage* frame, IplImage* subImg, int nbFrame, int idPersonne);
    void training(QLabel* conteneurImage, String nom, String prenom);
    Ptr<FaceRecognizer> creerModele();
    void recognition(QLabel* conteneurImage, QLabel* entete);
    bool capturing;
    bool saving;
protected:
private:
    Collection *collection;
    CvHaarClassifierCascade* cascade;
    IplImage* frame;
    IplImage* QImage2IplImage(QImage *qimg);
    QImage*  IplImage2QImage(IplImage *iplImg);
};

#endif // APPLICATION_H
