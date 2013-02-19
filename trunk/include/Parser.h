#ifndef PARSER_H
#define PARSER_H


class Parser
{
    public:
        Parser();
        virtual ~Parser();

        void Parse(char* xmlFile);
    protected:
    private:
};

#endif // PARSER_H
