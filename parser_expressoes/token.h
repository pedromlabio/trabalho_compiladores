#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    ADD,//2
    SUB,//3
    MULT,//4
    DIV,//5
    NUMBER,//6
    LP,//7
    RP,//8
    END_OF_FILE//9
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};