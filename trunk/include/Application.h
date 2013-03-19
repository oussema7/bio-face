#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include <string.h>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include "Collection.h"

using namespace cv;

class Application
{
public:
    Application();
    virtual ~Application();
    String saveTrainImg(IplImage* frame, IplImage* subImg, int nbFrame, int idPersonne);
    void training(IplImage* frame, CvHaarClassifierCascade* cascade, String nom, String prenom);
    Ptr<FaceRecognizer> creerModele();
    void recognition(IplImage* frame, CvHaarClassifierCascade* cascade);
protected:
private:
    Collection *collection;
    CvHaarClassifierCascade* cascade;
    IplImage* frame;
};

#endif // APPLICATION_H
