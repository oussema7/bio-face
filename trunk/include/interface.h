#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Application.h"
#include <QLabel>
#include <QPixmap>
#include <QTextLine>

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
    QLabel *conteneurImage;
    void cleanLayout();
    void creerPagePrincipale();
    void afficherPagePrincipale();
    void creerTrain();
    void afficherTrain();
    void creerFormulaire();
    void afficherFormulaire();
    void creerReco();
    void afficherReco();
    Application *app;
};
#endif // INTERFACE_H
