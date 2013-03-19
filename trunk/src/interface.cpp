#include "interface.h"

/** Constructeur **/
Interface::Interface() : QWidget()
{
    app = new Application;
    setFixedSize(800,600);
    layout = new QVBoxLayout;
    setLayout(layout);
    creerReco();
    creerPagePrincipale();
    afficherPagePrincipale();
}

void Interface::cleanLayout(){
    pagePrincipale->setVisible(false);
    reco->setVisible(false);
    //train->setVisible(false);
    //formulaire->setVisible(false);
}

void Interface::creerPagePrincipale(){
    pagePrincipale = new QWidget();
    QVBoxLayout* ppl = new QVBoxLayout();
    QPushButton* train = new QPushButton("Apprentissage");
    //QObject::connect(train, SIGNAL(clicked()), qApp, SLOT(quit()));
    train->setFixedHeight( 100);
    train->setFont(QFont("Comic sans MS",40));

    QPushButton* reco = new QPushButton("Reconnaissance");
    QObject::connect(reco, SIGNAL(clicked()), this, SLOT(clicSurReco()));
    reco->setFixedHeight(100);
    reco->setFont(QFont("Comic sans MS",40));

    ppl->addWidget(train);
    ppl->addWidget(reco);
    pagePrincipale->setLayout(ppl);
    layout->addWidget(pagePrincipale);
}

/** Affiche la page principale **/
void Interface::afficherPagePrincipale()
{
    cleanLayout();
    pagePrincipale->setVisible(true);
}

/** Evenement clic sur boutton reconnaissance **/
void Interface::clicSurReco()
{
    afficherReco();
}

/** Creer la page de l'apprentissage **/
void Interface::creerTrain(){

}

/** Affiche la page de l'apprentissage **/
void Interface::afficherTrain()
{

}

/** Creer la page de la reconaissance **/
void Interface::creerReco(){
    reco = new QPushButton("coucou");
    layout->addWidget(reco);
}

/** Affiche la page de la reconaissance **/
void Interface::afficherReco()
{
    cleanLayout();
    reco->setVisible(true);
}

/** Creer la page du formulaire (pour l'apprentissage) **/
void Interface::creerFormulaire(){
}

/** Affichel la page du formulaire (pour l'apprentissage) **/
void Interface::afficherFormulaire()
{

}


/** Fonction convertissant une image QT en image OpenCV **/
IplImage* Interface::QImage2IplImage(QImage *qimg)
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
QImage*  Interface::IplImage2QImage(IplImage *iplImg)
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
