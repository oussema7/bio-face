#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>
#include <list>
#include "Image.h"

using namespace std;

class Personne
{
    public:
        string name, lastname;
        int id;
        list<Image> imageReferences;

        Personne(string name,string lastname,int id,list<Image> imageReferences);
        virtual ~Personne();

        void addImage(Image img);
    protected:
    private:
};

#endif // PERSONNE_H
