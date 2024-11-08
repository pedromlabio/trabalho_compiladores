#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void
Parser::advance()
{
	lToken = scanner->nextToken();
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
}

void
Parser::run()
{
	advance();	

	program();
	
	cout << "Compilação encerrada com sucesso!\n";
}

void
Parser::program() //regra 1
{
    while (lToken->name != END_OF_FILE)
        function();

    match(END_OF_FILE);
}

void //regras 2 e 3, tanto type como void são considerados IDS no momento ent meio q n faz diferença
Parser::function()
{
    type();
    match(ID);
    match(LP);
    paramTypes();
    match(RP);
    match(LB);
    while (lToken->name != ID||
	lToken->name != SEMICOLON ||
	lToken->name != LB ||)
	{
		type();
		varDeclaration();
		while (lToken->name != SEMICOLON)
		{
			match(COMMA);
			varDeclaration();
		}
		match(SEMICOLON);
	}
	while (lToken->name != RB)
	{
		statement();
	}
	match(SEMICOLON);
	
}

Parser::varDeclaration() // regra 4
{
	match(ID);
	if (lToken->name == RB)
	{
		match(LB);
		match(INTEGER_LITERAL);
		match(RB);
	}
	
}

Parser::type() // regras 5 e 6
{
	match(ID);
}

Parser::paramTypes() // regras 7 e 8
{
	if (lToken->name == ID)
	{
		type();
		match(ID);
		if (lToken->name == RB)
		{
			match(LB);
			match(RB);
		}
		while (lToken->name != RP)
		{
			match(COMMA);
			type();
			match(ID);
			if (lToken->name == RB)
			{
				match(LB);
				match(RB);
			}
			
		}
		
		
	}else{
		match(ID);
	}
	
}

Parser::statement() //regras 9-15
{
	//acho q é meio q uma gambiarra q to fazendo
	if (/* condition */)
	{
		/* code */
	}
	
}
//TODO

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
