#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;

    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
            
        }
        inputFile.close();
        //cout << cont[0] << endl;
    }
    else 
        cout << "Unable to open file\n"; 

    //A próxima linha deve ser comentada posteriormente.
    //Ela é utilizada apenas para verificar se o 
    //preenchimento de input foi feito corretamente.
    //cout << this->input;

}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* tok;
    string lexeme;

    //cout << this->input << endl;
    //cout << input[8] << endl;

    int state = 0;

    while(true){
        if(input[pos] == '\n')
            line++;
        switch(state){
            case 0:
                // O input[pos] começa com o nome do arquivo, esse if serve para separar o nome do conteúdo
                if(pos == 0){

                    while(input[pos] != '.'){
                        pos++;
                    }
                    // Especifica o tipo de arquivo que deva receber
                    if(input[pos] == '.' && input[pos+1] == 'm' && input[pos+2] == 'j')
                    {
                        tok = new Token(CORRECTFILE);
                        pos += 3 ;
                        return tok;
                    }else{
                        cout << "INCORRECT FILE TYPE" << endl;
                        tok = new Token(WRONGFILE);
                        return tok;
                    }
                }else{

                    if(input[pos] == '\0')
                    {
                        tok = new Token(END_OF_FILE);
                        return tok;
                    }
                    else if(isalpha(input[pos]))
                        state = 1;
                    else if(isdigit(input[pos]))
                        state = 2;
                    else if(input[pos] == '>')
                        state = 3;
                    else if(input[pos] == '<')
                        state = 4;
                    else if(input[pos] == '=')
                        state = 5;
                    else if(input[pos] == '!')
                        state = 6;
                    else if(input[pos] == '+')
                        state = 7;
                    else if(input[pos] == '-')
                        state = 8;
                    else if(input[pos] == '*')
                        state = 9;
                    else if(input[pos] == '/'){

                        // Verifica se é o comentário em bloco.  OBS: comentários são ignorados, não são tokens
                        if(input[pos+1] == '*'){
                            pos += 2;
                            while(input[pos] != '*' && input[pos+1] != '/'){
                                pos++;  
                            }
                            pos ++;
                        // Verifica se é o comentário simples
                        }else if(input[pos+1] == '/'){
                            pos += 2;
                            while(input[pos] != '\n'){
                                pos++;
                            }
                        // Caso não seja um comentário
                        }else
                            state = 10;
                    }
                    else if(input[pos] == '(')
                        state = 11;
                    else if(input[pos] == ')')
                        state = 12;
                    else if(input[pos] == '[')
                        state = 13;
                    else if(input[pos] == ']')
                        state = 14;
                    else if(input[pos] == '{')
                        state = 15;
                    else if(input[pos] == '}')
                        state = 16;
                    else if(input[pos] == ',')
                        state = 17;
                    else if(input[pos] == ';')
                        state = 18;
                    else if(input[pos] == '&')
                        state = 19;
                    else if(input[pos] == '|')
                        state = 20;
                    // charconstant
                    else if(input[pos] == '\''){
                        state = 37;
                    }
                    // stringconstant
                    else if(input[pos] == '"'){
                        state = 38;
                    }
                    else if(isspace(input[pos]))
                        state = 32;
                    else
                        lexicalError(lexeme);
                }
                pos++;
                break;

            case 1:
                if(isalnum(input[pos]) || isdigit(input[pos]) || input[pos] == '_')
                    state = 35;
                else
                    state = 34;

                pos++;
                break;

            case 2:
                if(isdigit(input[pos]))
                    state = 21;
                else
                    state = 22;
               
                pos++;
                break;

            case 3:
                if(input[pos] == '=')
                    state = 24;
                else
                    state = 25;

                pos++;
                break;

            case 4:
                if(input[pos] == '=')
                    state = 26;
                else
                    state = 27;

                pos++;
                break;

            case 5:
                if(input[pos] == '=')
                    state = 28;
                else
                    state = 29;

                pos++;
                break;

            case 6:
                if(input[pos] == '=')
                    state = 30;
                else
                    state = 31;

                pos++;
                break;

            case 7:
                tok = new Token(BINOP, ADD);

                break;

            case 8:
                tok = new Token(BINOP, SUB);

                break;

            case 9:
                tok = new Token(BINOP, MULT);

                break;

            case 10:
                
                tok = new Token(BINOP, DIV);
                
                break;
                

            case 11:
                tok = new Token(SEPARATOR, LP);

                break;

            case 12:
                tok = new Token(SEPARATOR, RP);

                break;

            case 13:
                tok = new Token(SEPARATOR, LB);

                break;

            case 14:
                tok = new Token(SEPARATOR, RB);

                break;

            case 15:
                tok = new Token(SEPARATOR, LC);

                break;

            case 16:
                tok = new Token(SEPARATOR, RC);

                break;

            case 17:
                tok = new Token(SEPARATOR, COMMA);

                break;

            case 18:
                tok = new Token(SEPARATOR, SEMICOLON);

                return tok;

            case 21:
                if(!isdigit(input[pos]))
                    state = 23;
                
                pos++;
                break;

            case 22:
                tok = new Token(NUMBER, DIGIT);

                pos--;

                return tok;

            case 23:
                tok = new Token(NUMBER, INTEGER_LITERAL);
                
                pos--;

                return tok;

            case 24:
                tok = new Token(RELOP, GE);

                return tok;

            case 25:
                tok = new Token(RELOP, GT);

                pos--;

                return tok;

            case 26:
                tok = new Token(RELOP, LE);

                return tok;

            case 27:
                tok = new Token(RELOP, LT);

                pos--;

                return tok;

            case 28:
                tok = new Token(RELOP, EQ);

                return tok;

            case 29:
                tok = new Token(RELOP, ATRIB);

                pos--;

                return tok;

            case 30:
                tok = new Token(RELOP, NE);

                return tok;

            case 31:
                tok = new Token(RELOP, NOT);

                pos--;

                return tok;

            case 32:
                if (!isspace(input[pos]))
                    state = 33;

                pos++;

                break;

            case 33:
                pos--;
                state = 0;

                break;

            case 34:
                tok = new Token(LETTER);

                pos--;

                return tok;

            case 35:
                while(isalnum(input[pos]) || (isdigit(input[pos]) || input[pos] == '_')){
                    pos++;
                }
                pos++;
                state = 36;
                break;

            case 36:
                tok = new Token(ID);

                pos--;

                return tok;

            case 37:
                // Temporiariamente estão definidos como tokens UNDEF
                if(isprint(input[pos]) && input[pos+1] == '\''){
                    if(input[pos] == '\\'){
                        tok = new Token(UNDEF);
                    }else{
                        tok = new Token(CHAR_CONSTANT);
                    }
                    pos += 2;
                    return tok;
                }else{
                    lexeme = "Muitos argumentos para um tipo char OU Formato char incompleto.";
                    lexicalError(lexeme);
                }
                break;

             case 38:
                
                if(isprint(input[pos])){
                    while(input[pos] != '"'){
                        if(input[pos] == '\\' && input[pos+1] == 'n'){
                            //tok = new Token(UNDEF);
                            pos++;
                        }else if(input[pos] == '\0'){
                            lexeme = "Formato String incompleto.";
                            lexicalError(lexeme);
                        }
                        pos++;
                    }
                    tok = new Token(STRING_CONSTANT);
                }
                pos++;
                return tok;
                break;
    
            default:
                lexicalError(lexeme);
        }

    }

    return tok;
 
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
