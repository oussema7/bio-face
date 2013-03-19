#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Application.h"

class Interface : public QWidget
{
    Q_OBJECT

public:
    Interface();

public slots:
    void clicSurReco();

private:
    QVBoxLayout* layout;
    QWidget* pagePrincipale;
    QWidget* reco;
    QWidget* train;
    QWidget* formulaire;
    void cleanLayout();
    void creerPagePrincipale();
    void afficherPagePrincipale();
    void creerTrain();
    void afficherTrain();
    void creerFormulaire();
    void afficherFormulaire();
    void creerReco();
    void afficherReco();
    IplImage* QImage2IplImage(QImage *qimg);
    QImage*  IplImage2QImage(IplImage *iplImg);
    Application *app;
};
#endif // INTERFACE_H
