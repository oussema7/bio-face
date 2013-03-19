#include "../include/Parser.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

Parser::Parser()
{
}

Parser::Parser(const char* xmlFile)
{
    this->xmlFile = xmlFile;
}

Parser::~Parser()
{
    //dtor
}

bool Parser::parse(vector<Personne>& personnes)
{
    doc = TiXmlDocument(xmlFile);

    TiXmlElement *elem1,*elem2,*elem3;

    Personne personne;
    Image image;

    if(!doc.LoadFile())
    {
        cerr << "erreur lors du chargement" << endl;
        cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        return false;
    }

    TiXmlHandle hdl(&doc);

    //Node ListePersonne
    elem1 = hdl.FirstChildElement("ListePersonnes").Element();
    if(!elem1) return false;

    //Nodes Personne
    elem1=elem1->FirstChildElement("Personne");
    while(elem1)
    {
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
        while(elem2)
        {
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

        personnes.push_back(personne);
        elem1=elem1->NextSiblingElement("Personne");
    }

    personne = Personne();

    return true;
}

void Parser::exportFile() const
{
    doc.SaveFile(xmlFile);
}

bool Parser::addPersonne(const string& firstName,const string& lastName,int id)
{
    std::ostringstream  oss;
    string idString;


    TiXmlHandle hdl(&doc);
    TiXmlElement *elem1;

    //Node ListePersonne
    elem1 = hdl.FirstChildElement("ListePersonnes").Element();
    if(!elem1) return false;

    TiXmlText* newText;

    TiXmlElement new_personne("Personne");
    TiXmlElement new_nom("Nom");
    TiXmlElement new_prenom("Prenom");
    TiXmlElement new_id("Id");

    newText = new TiXmlText(firstName.c_str());
    new_nom.InsertEndChild(*newText);
    newText = new TiXmlText(lastName.c_str());
    new_prenom.InsertEndChild(*newText);
    oss <<id;
    newText = new TiXmlText(oss.str().c_str());
    new_id.InsertEndChild(*newText);

    new_personne.InsertEndChild(new_nom);
    new_personne.InsertEndChild(new_prenom);
    new_personne.InsertEndChild(new_id);

    elem1->InsertEndChild(new_personne);
    doc.SaveFile(xmlFile);

    return true;
}



void Parser::addImage(int personneId,const string& chemin,const string& date)
{
    bool trouve = false;
    TiXmlHandle hdl(&doc);
    TiXmlElement *elem1;

    //Node ListePersonne
    elem1 = hdl.FirstChildElement("ListePersonnes").FirstChildElement("Personne").Element();

    while(elem1 && !trouve)
    {
        if(atoi(elem1->FirstChildElement("Id")->GetText()) == personneId)
        {
            trouve = true;
            break;
        }
        elem1 = elem1->NextSiblingElement();
    }

    if (!trouve)
        cerr << "user inexistant" << endl;
    else
    {
        TiXmlText* newText;


        TiXmlElement new_chemin("Chemin");
        newText = new TiXmlText(chemin.c_str());
        new_chemin.InsertEndChild(*newText);
        TiXmlElement new_date("Date");
        newText = new TiXmlText(date.c_str());
        new_date.InsertEndChild(*newText);

        TiXmlElement new_image("Image");
        new_image.InsertEndChild(new_chemin);
        new_image.InsertEndChild(new_date);

        elem1->InsertEndChild(new_image);
    }
    doc.SaveFile(xmlFile);
}
