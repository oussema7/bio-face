#include "../include/interface.h"

/** Constructeur **/
Interface::Interface() : QWidget()
{
    app = new Application;
    setFixedSize(800,600);
    conteneurImage = new QLabel;
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
    reco = new QWidget;
    QVBoxLayout* rl = new QVBoxLayout();
    QLabel *entete = new QLabel("Veuillez vous placer devant la camera");
    entete->setFixedHeight(10);
    QImage *image = new QImage;
    image->load("./img/picture0.jpg");
    conteneurImage->setPixmap(QPixmap::fromImage(*image));
    rl->addWidget(entete);
    rl->addWidget(conteneurImage);
    reco->setLayout(rl);
    layout->addWidget(reco);
}

/** Affiche la page de la reconaissance **/
void Interface::afficherReco()
{
    cleanLayout();
    reco->setVisible(true);
    app->recognition(conteneurImage);
}

/** Creer la page du formulaire (pour l'apprentissage) **/
void Interface::creerFormulaire()
{
}

/** Affichel la page du formulaire (pour l'apprentissage) **/
void Interface::afficherFormulaire()
{

}
