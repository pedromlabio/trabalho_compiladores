#include "parser.h"

bool siga = true;
string func;

Parser::Parser(string input)
{
	currentST = globalST = new SymbolTable();
	initSymbolTable();

	scanner = new Scanner(input, globalST);
}

void
Parser::advance()
{
	
	lToken = scanner->nextToken();
	if(lToken->name == CORRECTFILE)
		lToken = scanner->nextToken();
	if(lToken->name == WRONGFILE)
		siga = false;
}

void
Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else{
		if(t == SEMICOLON)
			error("expected a ';'");
		else
			error("Erro inesperado");
	}

}
void
Parser::run()
{
	advance();	
	if(siga == true){
		program();
		cout << "Compilação encerrada com sucesso!\n";
	}
	else{
		cout << "INCORRECT FILE TYPE" << endl;
	}
	/*TESTE DA TABELA DE SÍMBOLOS

	currentST = new SymbolTable(currentST);
	currentST = new SymbolTbale(currentST);
	if(currentST -> add(new STEntry(new Token(ID), "batata")))
		cout << "Adição de batata deu certo" << endl;
	else
		cout << Adição de batata não deu certo" << endl;

	STEntry** obj = currentST ->get("batata");

	if(obj)
		cout << "Encontrei o símbolo' << obj -> lexeme" << endl;
	else
		cout << "Não encontrei o símbolo buscado" << endl; 

	///Fim do Escopo
	currentST = currentST -> getParent();
	
	obj = currentST -> get("batata");

	if(obj)
		cout << "Encontrei o símbolo' << obj -> lexeme" << endl;
	else
		cout << "Não encontrei o símbolo buscado" << endl; 

	*/
}

void
Parser::program() //regra 1
{
    while (lToken->name != END_OF_FILE){
		currentST = new SymbolTable(currentST);
		function();
		currentST = currentST -> getParent();
	}

    match(END_OF_FILE);
}

void 
Parser::function() // regras 2 e 3
{
	if (lToken->lexeme == "void" || lToken->lexeme == "int")
	{
		//cout << lToken->lexeme << endl;
		advance();
		match(ID);
		match(LP);
		paramTypes();
		match(RP);
		match(LC);
		currentST = new SymbolTable(currentST);
		
		while (lToken->attribute != RC){
			if(
		lToken->lexeme == "char" || //essas duas linhas servem como first de assign pq é tudo id
		lToken->lexeme == "int"
		
			)
		{
			type();
			// adciona os nomes da variáveis à tabela de símbolos
			globalST -> add(new STEntry(lToken, true));
			STEntry* obj = currentST -> get(lToken->lexeme);
			if(obj)
				cout << "Encontrei o símbolo " << obj->token->lexeme << endl;
			else
				cout << "Não encontrei o símbolo buscado" << endl;
			varDeclaration();
			
			while (lToken->attribute != SEMICOLON && lToken->attribute != ATRIB)
			{
				
				match(COMMA);
				varDeclaration();
			}
			if(lToken->attribute == SEMICOLON){
				//cout << "oi" << endl;
				advance();
			}
			else{
				while(lToken->attribute != RC && lToken->name != ID)
				{
					//cout << lToken->attribute << endl;
					//cout << "oi" << endl;
					statement();
				}
			}
			
		}
		if (lToken->lexeme == "if"||
		lToken->lexeme == "while"||
		lToken->lexeme == "for"||
		lToken->lexeme == "return"|| lToken->attribute == LC ||
		lToken->attribute == SEMICOLON)
		{
			//cout << lToken->name << endl;
			statement();
			//cout << lToken->lexeme << endl;
		}
		}
		
	match(RC);
	currentST = currentST -> getParent();
/*
	}else{
		type();
		match(ID);
		match(LP);
		paramTypes();
		match(RP);
		match(LC);
		
		while (lToken->lexeme != "if"&&
		lToken->lexeme != "while"&&
		lToken->lexeme != "for"&&
		lToken->lexeme != "return"&&
		lToken->lexeme == "char"&& //essas duas linhas servem como first de assign pq é tudo id
		lToken->lexeme == "int"&&
		lToken->attribute != LC &&
		lToken->attribute != SEMICOLON
		)
		{
			type();
			varDeclaration();
			while (lToken->attribute != SEMICOLON)
			{
				match(COMMA);
				varDeclaration();
			}
			
		}
		while (lToken->attribute != RC)
		{
			cout << lToken->name << endl;
			statement();
		}
		match(RC);*/
	}
	
}

void
Parser::varDeclaration() // regra 4
{
	//cout << lToken->attribute << endl;
	match(ID);
	//cout << "oi" << endl;
	if (lToken->attribute == LB)
	{
		advance();
		match(INTEGER_LITERAL);
		match(RB);
	}
	
}

void
Parser::type() // regras 5 e 6
{
	//cout << lToken->name << endl;
	if (lToken->lexeme == "char"||
	lToken->lexeme == "int")
	{
		advance();
	}else{
		error("Tipo invalido de variável em " + lToken -> lexeme);
	}
}

void
Parser::paramTypes() //regras 7 e 8
{
	//cout << "oi" << endl;
	if (lToken->lexeme == "void")
	{
		advance();
	}else{
		type();
		match(ID);
		if (lToken->attribute == LB)
		{
			advance();
			match(RB);
		}
		while (lToken->attribute != RP)
		{
			match(COMMA);
			type();
			match(ID);
			if (lToken->attribute == LB)
			{
				advance();
				match(RB);
			}
			
		}
		
		
	}
	
}

void
Parser::statement() // regras 9 a 15
{
	if (lToken->lexeme == "if")
	{
		advance();
		match(LP);
		expression();
		match(RP);
		statement();
		if (lToken->lexeme == "else")
		{
			advance();
			statement();
		}
		
	}else if (lToken->lexeme == "while")
	{
		advance();
		match(LP);
		expression();
		match(RP);
		statement();
	}else if (lToken->lexeme == "for")
	{
		advance();
		match(LP);
		if (lToken->name == ID)
		{
			assign();
		}
		match(SEMICOLON);
		if (lToken->attribute != SEMICOLON) // mais pratico q pegar todos of first de expression
		{
			expression();
		}
		match(SEMICOLON);
		if (lToken->attribute != RP)
		{
			assign();
		}
		match(RP);
		statement();
	}else if (lToken->lexeme == "return")
	{
		advance();
		if (lToken->attribute != SEMICOLON)
		{
			expression();
		}
		match(SEMICOLON);
	}else if (lToken->attribute == LC)
	{
		currentST = new SymbolTable(currentST);
		advance();
		while (lToken->attribute != RC)
		{
			statement();
		}
		match(RC);
		currentST = currentST -> getParent();

	}else if (lToken->attribute == SEMICOLON)
	{
		advance();
	}else 
	{
		assign();
		match(SEMICOLON);
	}
}

void
Parser::assign() // regra 16
{
	//cout << lToken->attribute << endl;
	if(lToken->name == ID){
		
		globalST -> add(new STEntry(lToken, true));
		STEntry* obj = currentST -> get(lToken->lexeme);
		if(obj)
			cout << "Encontrei o símbolo " << obj->token->lexeme << endl;
		else
			cout << "Não encontrei o símbolo buscado" << endl;
		match(ID);
	}
	assignL();
}

void
Parser::assignL() /// regras 17 e 18
{
	if (lToken->attribute == LP)
	{
		advance();
		if (lToken->attribute =! RP)
		{
			expression();
			while (lToken->attribute != RP)
			{
				match(COMMA);
				expression();
			}
			
		}
		match(RP);
	}else{
		if (lToken->attribute == LB)
		{
			advance();
			expression();
			match(RB);
		}
		//cout << "te achei" << endl;
		//cout << lToken->name << endl;
		match(ATRIB);
		expression();
	}
}


void
Parser::expression() // regras 19 a 25
{
	if (lToken->attribute == SUB||
	lToken->attribute == NOT)
	{
		expression();
		term();
	}else if (lToken->name == ID)
	{
		advance();
		if (lToken->attribute == LP)
		{
			advance();
			if (lToken->attribute != RP)
			{
				expression();
				while (lToken->attribute != RP)
				{
					match(COMMA);
					expression();
				}
				
			}
			match(RP);

			
		}else if (lToken->attribute == LB)
		{
			advance();
			expression();
			match(RB);
		}
		term();
	}else if (lToken->attribute == LP)
	{
		advance();
		expression();
		match(RP);
		term();
	}else if (lToken->name == NUMBER||
	lToken->name == CHAR_CONSTANT||
	lToken->name == STRING_CONSTANT)
	{
		advance();
		term();
	}else
	{
		error("Erro na compilação de expressão");
	}
}

void
Parser::term() // regras 26 a 29
{
	if (lToken->name == BINOP)
	{
		binOp();
		expression();
		term();
	}else if (lToken->name == RELOP)
	{
		relOp();
		expression();
		term();
	}else if (lToken->name == LOGOP)
	{
		logOp();
		expression();
		term();
	}
}

void
Parser::binOp() // regras 30 a 33
{
	if (lToken->attribute == ADD||
	lToken->attribute == SUB||
	lToken->attribute == MULT||
	lToken->attribute == DIV)
	{
		advance();
	}else
	{
		error("Operação do tipo binária invalida");
	}
}

void
Parser::relOp() // regras 34 a 39
{
	if (lToken->attribute == EQ||
	lToken->attribute == NE||
	lToken->attribute == LE||
	lToken->attribute == LT||
	lToken->attribute == GE||
	lToken->attribute == GT)
	{
		advance();
	}else{
		error("Operação do tipo comparativa invalida");
	}
}

void
Parser::logOp() // regras 40 e 41
{
	if (lToken->attribute == AND||
	lToken->attribute == OR)
	{
		advance();
	}else{
		error("Operação do tipo lógica invalida");
	}

}

void
Parser::initSymbolTable()
{
	Token* t;

	t = new Token(WHILE, "while");
	globalST -> add(new STEntry(t, true));
	t = new Token(IF, "if");
	globalST -> add(new STEntry(t, true));
	t = new Token(FOR, "for");
	globalST -> add(new STEntry(t, true));
	t = new Token(RETURN, "return");
	globalST -> add(new STEntry(t, true));
	t = new Token(ELSE, "else");
	globalST -> add(new STEntry(t, true));
	t = new Token(VOID, "void");
	globalST -> add(new STEntry(t, true));
	t = new Token(INT, "int");
	globalST -> add(new STEntry(t, true));
	t = new Token(CHAR, "char");
	globalST -> add(new STEntry(t, true));
	t = new Token(INTEGER_LITERAL, "integerconstant");
	globalST -> add(new STEntry(t, true));
	t = new Token(CHAR_CONSTANT, "charconstant");
	globalST -> add(new STEntry(t, true));
	t = new Token(STRING_CONSTANT, "stringconstant");
	globalST -> add(new STEntry(t, true));
	//PREENCHER COM AS PALAVRAS RESERVADAS DA LINGUAGEM
}

void
Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
}
