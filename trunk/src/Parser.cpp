#include "Parser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

Parser::Parser(){

}

Parser::~Parser(){
    //dtor
}

bool Parser::Parse(Collection& collection,const char* xmlFile) const{
    TiXmlDocument doc(xmlFile);
    TiXmlElement *elem1,*elem2,*elem3;

    list<Personne> personnes;
    Personne personne;
    Image image;


    if(!doc.LoadFile()){
        cerr << "erreur lors du chargement" << endl;
        cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        return false;
    }

    TiXmlHandle hdl(&doc);

    //Node ListePersonne
    elem1 = hdl.FirstChildElement("ListePersonnes").Element();
    if(!elem1) return false;
    collection = Collection();

    //Nodes Personne
    elem1=elem1->FirstChildElement("Personne");
    while(elem1){
        personne=Personne();

        //Nom
        elem2=elem1->FirstChildElement("Nom");
        if(!elem2) return false;
        personne.setLastName(elem2->GetText());

        //Prenom
        elem2=elem2->NextSiblingElement("Prenom");
        if(!elem2) return false;
        personne.setFirstName(elem2->GetText());

        //Id
        elem2=elem2->NextSiblingElement("Id");
        if(!elem2) return false;
        personne.setId(atoi(elem2->GetText()));

        //Nodes Image
        elem2=elem2->NextSiblingElement("Image");
        while(elem2){
            image=Image();

            //Chemin
            elem3=elem2->FirstChildElement("Chemin");
            if(!elem3) return false;
            image.setChemin(elem3->GetText());

            //Date
            elem3=elem2->FirstChildElement("Date");
            if(!elem3) return false;
            image.setDate(elem3->GetText());

            personne.addImage(image);
            elem2=elem2->NextSiblingElement("Image");
        }

        collection.addPersonne(personne);
        elem1=elem1->NextSiblingElement("Personne");
    }

    personne = Personne();



    return true;
}
