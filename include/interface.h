#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include "Application.h"
#include <QtWidgets/QLabel>
#include <QtGui/QPixmap>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>

class Interface : public QWidget
{
    Q_OBJECT

public:
    Interface();

public slots:
    void clicSurReco();
    void clicSurMenu();
    void clicSurTrain();
    void clicSurSuivant();

private:
    QVBoxLayout* layout;
    QWidget* pagePrincipale;
    QWidget* reco;
    QWidget* train;
    QWidget* formulaire;
    QLabel *conteneurImage;
    QLabel *conteneurImageTrain;
    QLabel *entete;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_prenom;
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
