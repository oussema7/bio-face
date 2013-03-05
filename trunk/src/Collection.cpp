#include "Collection.h"

Collection::Collection(const char* xmlFile){
    parser = Parser(xmlFile);
    if(parser.parse(personnes)){
        cout << "Collection chargee." << endl;
    }
    else{
        cout << "Erreur dans le chargement de la collection" << endl;
    }
}

Collection::~Collection(){
    //dtor
}

const Personne& Collection::getPersonne(int id) const{
    list<Personne>::const_iterator it=getPersonnes().begin();
    while(it!=getPersonnes().end() && it->getId()!=id){
        it++;
    }
    if(it==getPersonnes().end()){
        cout <<"Personne with id "<<id<<" not found." << endl;
    }
    return (*it);
}

void Collection::addPersonne(const string& firstName,const string& lastName,
                 int id){
    Personne p(firstName,lastName,id);
    personnes.push_back(p);
    parser.addPersonne(firstName,lastName,id);
}

void Collection::addImage(int personneId,const string& chemin,
                          const string& date){
    Image img(chemin,date);

    list<Personne>::iterator it=personnes.begin();
    while(it!=personnes.end() && it->getId()!=personneId){
        it++;
    }
    if(it==getPersonnes().end()){
        cout <<"Personne with id "<<personneId<<" not found." << endl;
    }
    else{
        it->addImage(img);
        parser.addImage(personneId,chemin,date);
    }
}

void Collection::saveChanges() const{
    parser.exportFile();
}

string Collection::to_string() const{

    string res = "[Collection]\n";

    list<Personne>::const_iterator it;
    for(it=getPersonnes().begin(); it!=getPersonnes().end();it++){
        res=res+it->to_string()+"\n";
    }

    res.append("[Collection]");
    return res;
}
