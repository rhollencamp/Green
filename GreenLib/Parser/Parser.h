#pragma once

#include <QString>
#include <fstream>
using std::ifstream;

#include "Scanner.h"
#include "Tokens.h"


namespace Green
{
	class Class;
	class Expression;
	class Method;
	class Statement;


	class Parser
	{
		public:
			Parser();
			explicit Parser(const QString & newFileName);
			~Parser();

			Class * parse();


		private:
			Class * newClass;

			ifstream * inputStream;

			Scanner * fileScanner;
			Token currentToken;

			void parseClassBody();
			Method * parseMethod();
			Statement * parseStatement();

			Expression * parseExpression(Expression * lhs, int minPrecedence);
			Expression * parseExpressionTerminal();
			Expression * combineExpressionsOperator(Expression * lhs, Expression * rhs, Token op);
			Expression * parseDotOperator(Expression * lhs, Expression * rhs);
			Expression * parseScopeResolutionOperator(Expression * lhs, Expression * rhs);

			bool acceptToken(const Token tok);
			void expectToken(const Token tok, const QString & errorMessage);
			Token readNextToken();

			Q_DISABLE_COPY(Parser)
	};


	inline void Parser::expectToken(const Token tok, const QString & errorMessage)
	{
		if (currentToken != tok) {
			// TODO syntax error
			throw errorMessage;
		}

		currentToken = fileScanner->getToken();
	}

	inline Token Parser::readNextToken()
	{
		currentToken = fileScanner->getToken();
		return currentToken;
	}

	inline bool Parser::acceptToken(const Token tok)
	{
		if (currentToken == tok) {
			readNextToken();
			return true;
		}
		return false;
	}

	inline Parser::Parser()
		: inputStream(0)
	{
	}
}
