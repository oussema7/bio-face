#ifndef IMAGE_H
#define IMAGE_H

#include <string>

using namespace std;

class Image
{
    public:
        //Contructors and destructors
        Image();
        Image(const string& chemin,const string& date);
        virtual ~Image();

        //Getters and setters
        inline const string& getChemin() const {return chemin;};
        inline void setChemin(const string& chemin) {this->chemin=chemin;};

        inline const string& getDate() const {return date;};
        inline void setDate(const string& date) {this->date=date;};

    protected:
    private:
        string chemin,date;
};

#endif // IMAGE_H
