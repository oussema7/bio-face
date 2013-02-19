#include "Personne.h"

Personne::Personne(string name,string lastname,int id,list<Image> imageReferences)
{
    this->name=name;
    this->lastname=lastname;
    this->id=id;
    this->imageReferences=imageReferences;
}

void Personne::addImage(Image img){
    imageReferences.push_back(img);
}

Personne::~Personne()
{
    //dtor
}
