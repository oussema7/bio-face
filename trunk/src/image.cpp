#include "../include/Image.h"

Image::Image()
{

}

Image::Image(const string& chemin,const string& date)
{
    this->chemin=chemin;
    this->date=date;
}

Image::~Image()
{
    //dtor
}
