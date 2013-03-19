#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <string.h>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include "Collection.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>

using namespace cv;

class Application
{
public:
    Application();
    virtual ~Application();
    String saveTrainImg(IplImage* frame, IplImage* subImg, int nbFrame, int idPersonne);
    void training(String nom, String prenom);
    Ptr<FaceRecognizer> creerModele();
    void recognition(QLabel* conteneurImage);
protected:
private:
    Collection *collection;
    CvHaarClassifierCascade* cascade;
    IplImage* frame;
    IplImage* QImage2IplImage(QImage *qimg);
    QImage*  IplImage2QImage(IplImage *iplImg);
};

#endif // APPLICATION_H
