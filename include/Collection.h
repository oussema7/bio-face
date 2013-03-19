#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include "Personne.h"
#include "Parser.h"

using namespace std;

class Collection
{
    public:
        //Constructors and destructors
        Collection(const char* xmlFile);
        virtual ~Collection();

        //Getters and setters
        inline const vector<Personne>& getPersonnes() const {return personnes;};
        const Personne& getPersonne(int id) const;

        inline void setPersonnes(const vector<Personne>& personnes){this->personnes=personnes;}
        //Methods
        int addPersonne(const string& firstName,const string& lastName);
        void addImage(int personneId,const string& chemin);

        void saveChanges() const;

        //Overrided
        string to_string() const;


    private:
        Parser parser;
        vector<Personne> personnes;
};

#endif // COLLECTION_H
