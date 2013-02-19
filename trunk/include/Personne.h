#ifndef PERSONNE_H
#define PERSONNE_H


class Personne
{
    public:
        string name, lastname;
        int id;
        list<image> imageReferences;
        Personne();
        virtual ~Personne();
    protected:
    private:
};

#endif // PERSONNE_H
