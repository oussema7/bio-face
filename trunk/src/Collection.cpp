#include "Collection.h"

Collection::Collection(){
    //ctor
}

Collection::~Collection(){
    //dtor
}

void Collection::addPersonne(const Personne& p){
    personnes.push_back(p);
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
