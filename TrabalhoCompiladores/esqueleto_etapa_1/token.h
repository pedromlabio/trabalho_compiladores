#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    LETTER,//1
    DIGIT,//2
    ID,//3
    INTEGER_LITERAL,//4
    CHAR_CONSTANT,//5                     //Provavelmente deveremos alterar alguma coisa em char_constant e string_constant
    STRING_CONSTANT,//6                   //Não sei como analisaremos "qualquer caractere ASCII imprimível"
    RELOP,//7
    ADD,//8
    SUB,//9
    MULT,//10
    DIV,//11
    ATRIB,//12
    EQ,//13
    NE,//14
    LE,//15
    LT,//16
    GE,//17
    GT,//18
    AND,//19
    OR,//20
    NOT,//21
    SEPARATOR,//22
    LP,//23
    RP,//24
    LC,//25
    RC,//26
    LB,//27
    RB,//28
    COMMA,//29
    SEMICOLON,//30
    COMMENT,//31
    NUMBER,//32
    END_OF_FILE//33
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

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};
