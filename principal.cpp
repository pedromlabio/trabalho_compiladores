/* TUTORIAL!!!!!!!

para compilar e executar siga esses passos no VSCODE
1- g++ principal.cpp scanner.cpp -o teste
2- ./teste saida.mj    ** Vale ressaltar que nesta parte só se aceita arquivos do tipo .mj, independente do nome



*/
#include "parser.h"
//#include "scanner.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }
/*
    string input;
    
    //getline(cin, input);

    Scanner* scanner = new Scanner(argv[1]);

    Token* t;
    
    do
    {
        t = scanner->nextToken();
        
        if(t->name != WRONGFILE && t->name != CORRECTFILE)
            cout << t->name << " ";
        
    }while (t->name != END_OF_FILE && t->name != WRONGFILE);

    delete scanner;

*/
    Parser* parser = new Parser(argv[1]);

    parser->run();
    return 0;
}