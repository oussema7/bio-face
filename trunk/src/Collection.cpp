#include "Collection.h"

Collection::Collection(){
    //ctor
}

Collection::~Collection(){
    //dtor
}

Personne& Collection::getPersonne(int id) {
    list<Personne>::iterator it=getPersonnes().begin();
    while(it!=getPersonnes().end() && it->getId()!=id){
        it++;
    }
    if(it==getPersonnes().end()){

    }
    return (*it);
}

void Collection::addPersonne(const Personne& p){
    personnes.push_back(p);
}

string Collection::to_string(){

    string res = "[Collection]\n";

    list<Personne>::iterator it;
    for(it=getPersonnes().begin(); it!=getPersonnes().end();it++){
        res=res+it->to_string()+"\n";
    }


    res.append("[Collection]");
    return res;
}
