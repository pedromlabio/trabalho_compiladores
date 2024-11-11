#include "scanner.h"
#include "symboltable.h"

class Parser
{
	private:
		Scanner* scanner;
		Token* lToken;
		SymbolTable* globalST;
		SymbolTable* currentST;

		void advance();
		void match(int);
		
	public:
		Parser(string);
		void run();
        void program();
        void function();
		void varDeclaration();
		void type();
		void paramTypes();
		void statement();
		void assign();
		void assignL();
		void expression();
		void term();
		void binOp();
		void relOp();
		void logOp();
		void initSymbolTable();
        void error(string);
};