#include "Parser.h"
#include <iostream>
#include "include/tinyxml.h"
#include "include/tinystr.h"

using namespace std;

Parser::Parser()
{
        TiXmlDocument doc("data/Personnes.xml");
    if(!doc.LoadFile()){
        cerr << "erreur lors du chargement" << endl;
        cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        return 1;
    }
}

Parser::~Parser()
{
    //dtor
}

void Parser::Parse(char* xmlFile){
    cout << "Non Implémentée!" <<endl;
}
