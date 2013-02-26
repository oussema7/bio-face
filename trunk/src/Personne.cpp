#include "Personne.h"

#include <sstream>

Personne::Personne(){

}

Personne::Personne(const string& firstName,const string& lastName,
                   int id,const list<Image>& imageReferences){
    this->firstName=firstName;
    this->lastName=lastName;
    this->id=id;
    this->imageReferences=imageReferences;
}

Personne::~Personne()
{
    //dtor
}

void Personne::addImage(const Image& img){
    imageReferences.push_back(img);
}

string Personne::to_string() const{
    stringstream ss;
    string res="[Personne]\n";

    res+="Nom : "+firstName+" "+lastName+"\n";
    ss << id;
    res+="Id : "+ss.str()+"\n";
    ss.str(std::string());
    ss << imageReferences.size();
    res+="Nb Images : "+ss.str()+"\n";
    res+="[Personne]";

    return res;
}

