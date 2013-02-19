#ifndef IMAGE_H
#define IMAGE_H

#include <string>

using namespace std;

class Image
{
    public:
        string chemin,date;

        Image(string chemin,string date);
        virtual ~Image();
    protected:
    private:
};

#endif // IMAGE_H
