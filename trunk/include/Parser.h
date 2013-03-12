#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "tinyxml.h"
#include "tinystr.h"
#include "Personne.h"

class Parser
{
    public:
        Parser();
        Parser(const char* xmlFile);
        virtual ~Parser();

        //Fonctions d'import/export
        bool parse(vector<Personne>& personnnes);
        void exportFile() const;

        //Fonctions de modif des données
        bool addPersonne(const string& firstName,const string& lastName,
                 int id);
       void addImage(int personneId,const string& chemin,
                          const string& date);
    protected:
    private:
        const char* xmlFile;
        TiXmlDocument doc;
};

#endif // PARSER_H
