#ifndef COLLECTION_H
#define COLLECTION_H

#include <list>
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
        inline const list<Personne>& getPersonnes() const {return personnes;};
        const Personne& getPersonne(int id) const;

        inline void setPersonnes(const list<Personne>& personnes){
            this->personnes=personnes;
        }

        //Methods
        void addPersonne(const string& firstName,const string& lastName);
        void addImage(int personneId,const string& chemin,
                          const string& date);

        void saveChanges() const;

        //Overrided
        string to_string() const;


    private:
        Parser parser;
        list<Personne> personnes;
};

#endif // COLLECTION_H
