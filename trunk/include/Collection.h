#ifndef COLLECTION_H
#define COLLECTION_H

#include <list>
#include "Personne.h"

using namespace std;

class Collection
{
    public:
        //Constructors and destructors
        Collection();
        virtual ~Collection();

        //Getters and setters
        inline list<Personne>& getPersonnes() {return personnes;};
        Personne& getPersonne(int id);
        inline void setPersonnes(const list<Personne>& personnes){
            this->personnes=personnes;
        }

        //Methods
        void addPersonne(const Personne& p);

        //Overrided
        string to_string();

    protected:
    private:
        list<Personne> personnes;
};

#endif // COLLECTION_H
