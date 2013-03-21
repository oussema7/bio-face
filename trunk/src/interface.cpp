#include "../include/interface.h"

/** Constructeur **/
Interface::Interface() : QWidget()
{

    setFixedSize(800,600);
    conteneurImage = new QLabel();
    conteneurImageTrain = new QLabel();
    entete = new QLabel;
    enteteTrain = new QLabel;
    layout = new QVBoxLayout;
    setLayout(layout);
    creerReco();
    creerPagePrincipale();
    creerFormulaire();
    creerTrain();
    app = new Application;
    afficherPagePrincipale();

}

void Interface::cleanLayout(){
    pagePrincipale->setVisible(false);
    reco->setVisible(false);
    train->setVisible(false);
    formulaire->setVisible(false);
}

void Interface::creerPagePrincipale(){
    pagePrincipale = new QWidget();
    QVBoxLayout* ppl = new QVBoxLayout();
    QPushButton* train = new QPushButton("Apprentissage");
    QObject::connect(train, SIGNAL(clicked()), this, SLOT(clicSurTrain()));
    train->setFixedHeight(100);
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

/** Evenement clic sur menu **/
void Interface::clicSurMenu(){
    app->capturing = false;
    cleanLayout();
    pagePrincipale->setVisible(true);
}

/** Evenement clic sur train **/
void Interface::clicSurTrain(){
    afficherFormulaire();
}

/** Evenement clic sur boutton reconnaissance **/
void Interface::clicSurReco()
{
    afficherReco();
}

/** Evenement clic sur boutton suivant du formulaire **/
void Interface::clicSurSuivant()
{
    afficherTrain();
}

void Interface::clicCapture()
{
    app->saving = true;
    capture->setEnabled(false);
}

/** Creer la page de l'apprentissage **/
void Interface::creerTrain(){
    train = new QWidget;
    QVBoxLayout* rl = new QVBoxLayout();

    QPushButton* menu = new QPushButton("Retour au menu");
    menu->setFont(QFont("Comic sans MS",15));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(clicSurMenu()));
    enteteTrain->setFont(QFont("Comic sans MS",14));
    capture = new QPushButton("Capturer 10 images");
    QObject::connect(capture, SIGNAL(clicked()), this, SLOT(clicCapture()));
    QImage *image = new QImage;
    image->load("./img/picture0.jpg");
    conteneurImageTrain->setPixmap(QPixmap::fromImage(*image));
    rl->addWidget(enteteTrain);
    rl->addWidget(capture);
    rl->addWidget(conteneurImageTrain);
    rl->addWidget(menu);
    train->setLayout(rl);
    layout->addWidget(train);
}

/** Affiche la page de l'apprentissage **/
void Interface::afficherTrain()
{
    cleanLayout();
    train->setVisible(true);
    enteteTrain->setText("Appuyez sur le bouton pour vous enregistrer...");
    app->saving = false;
    capture->setEnabled(true);
    app->training(conteneurImageTrain, lineEdit_nom->text().toStdString(), lineEdit_prenom->text().toStdString(),enteteTrain);


}

/** Creer la page de la reconaissance **/
void Interface::creerReco(){
    reco = new QWidget;
    QVBoxLayout* rl = new QVBoxLayout();
    entete->setText("Veuillez vous placer devant la camera");
    entete->setFont(QFont("Comic sans MS",14));
    entete->setFixedHeight(20);
    QImage *image = new QImage;
    image->load("./img/picture0.jpg");
    conteneurImage->setPixmap(QPixmap::fromImage(*image));
    QPushButton* menu = new QPushButton("Retour au menu");
    menu->setFont(QFont("Comic sans MS",15));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(clicSurMenu()));
    rl->addWidget(entete);
    rl->addWidget(conteneurImage);
    rl->addWidget(menu);
    reco->setLayout(rl);
    layout->addWidget(reco);
}

/** Affiche la page de la reconaissance **/
void Interface::afficherReco()
{
    cleanLayout();
    reco->setVisible(true);
    app->recognition(conteneurImage, entete);
}

/** Creer la page du formulaire (pour l'apprentissage) **/
void Interface::creerFormulaire()
{
    formulaire = new QWidget;
    QFormLayout* fl = new QFormLayout();
    fl->setVerticalSpacing(30);
    fl->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *label_nom = new QLabel("Nom : ");
    label_nom->setFont(QFont("Comic sans MS",20));
    QLabel *label_prenom = new QLabel("Prenom : ");
    label_prenom->setFont(QFont("Comic sans MS",20));
    lineEdit_nom = new QLineEdit();
    lineEdit_nom->setFixedHeight(40);
    lineEdit_nom->setFont(QFont("Comic sans MS",20));
    lineEdit_prenom = new QLineEdit();
    lineEdit_prenom->setFixedHeight(40);
    lineEdit_prenom->setFont(QFont("Comic sans MS",20));
    QPushButton* menu = new QPushButton("Retour menu");
    menu->setFont(QFont("Comic sans MS",20));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(clicSurMenu()));
    QPushButton* suivant = new QPushButton("Suivant");
    QObject::connect(suivant, SIGNAL(clicked()), this, SLOT(clicSurSuivant()));
    suivant->setFont(QFont("Comic sans MS",20));
    fl->addRow(label_nom, lineEdit_nom);
    fl->addRow(label_prenom, lineEdit_prenom);
    QHBoxLayout* bl = new QHBoxLayout();
    bl->addWidget(menu);
    bl->addWidget(suivant);
    fl->addRow(bl);
    formulaire->setLayout(fl);
    layout->addWidget(formulaire);
}

/** Affichel la page du formulaire (pour l'apprentissage) **/
void Interface::afficherFormulaire()
{
    cleanLayout();
    formulaire->setVisible(true);
}
