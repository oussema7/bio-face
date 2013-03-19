#ifndef PERSONNE_H
#define PERSONNE_H

#include <iostream>
#include <string>
#include <vector>
#include "Image.h"

using namespace std;

class Personne
{
public:
    //Constructors and destructors
    Personne();
    Personne(const string& firstName,const string& lastName,
             int id);
    Personne(const string& firstName,const string& lastName,
             int id,const vector<Image>& imageReferences);
    virtual ~Personne();

    //Getters and setters
    inline const string& getFirstName() const
    {
        return firstName;
    };
    inline void setFirstName(const string& firstName)
    {
        this->firstName=firstName;
    };

    inline const string& getLastName() const
    {
        return lastName;
    };
    inline void setLastName(const string& lastName)
    {
        this->lastName=lastName;
    };

    inline int getId() const
    {
        return id;
    };
    inline void setId(int id)
    {
        this->id=id;
    };

    inline const vector<Image>& getImageReferences() const
    {
        return imageReferences;
    };
    inline void setImageReferences(const vector<Image>& imageReferences)
    {
        this->imageReferences=imageReferences;
    };

    //Methods
    void addImage(const Image& img);

    //Overrrided
    string to_string() const;

protected:

private:
    string firstName, lastName;
    int id;
    vector<Image> imageReferences;
};

#endif // PERSONNE_H
