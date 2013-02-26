#ifndef PARSER_H
#define PARSER_H

#include "Collection.h"

class Parser
{
    public:
        Parser();
        virtual ~Parser();

        bool Parse(Collection& collection,const char* xmlFile) const;
    protected:
    private:
};

#endif // PARSER_H
