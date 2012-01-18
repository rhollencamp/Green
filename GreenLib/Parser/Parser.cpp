#include <cstdlib>

#include "Class/Class.h"
#include "Expression/AssignmentExpression.h"
#include "Expression/ConstantIntegerExpression.h"
#include "Expression/InstanceMethodExpression.h"
#include "Expression/VariableExpression.h"
#include "Parser.h"
#include "Statement/EchoStatement.h"
#include "Statement/ExpressionStatement.h"
#include "Tokens.h"


namespace Green
{
	Parser::Parser(const QString & newFileName)
	{
		inputStream = new ifstream(newFileName.toLatin1());
		if (!inputStream->good()) {
			throw QString("Unable to open input file");
		}
	}

	Parser::~Parser()
	{
		if (inputStream != 0) {
			delete inputStream;
		}
	}

	Class * Parser::parse()
	{
		// initialize lexical analysis
		fileScanner = new Scanner(inputStream);
		readNextToken();

		// set the package name
		expectToken(KEYWORD_PACKAGE, "Missing Package Name");
		if (currentToken != IDENTIFIER) {
			// TODO syntax error
			throw QString("Expedted identifier (Package Name)");
		}
		QString packageName = fileScanner->getText();
		readNextToken();
		expectToken(SYM_SEMICOLON, "Expected Semicolon");

		// read in imports
		while (currentToken == KEYWORD_IMPORT) {
			readNextToken();
		}

		// we should be looking at a class symbol now
		expectToken(KEYWORD_CLASS, "Expected 'class' keyword");

		// next token is identifier, class name
		if (currentToken != IDENTIFIER) {
			// TODO syntax error
			throw QString("Exptected identifier (Class Name)");
		}
		QString className = fileScanner->getText();
		readNextToken();

		// create new class structure
		newClass = new Class(className, packageName, NULL); // @todo parent

		// class declaration body
		expectToken(SYM_CURLY_OPEN, "Expected opening curly bracket");
		parseClassBody();
		expectToken(SYM_CURLY_CLOSE, "Expected closing curly bracket");

		return newClass;
	}

	void Parser::parseClassBody()
	{
		do {
			// member variable?
			if (acceptToken(KEYWORD_VAR)) {
				// @todo
			} else if (acceptToken(KEYWORD_FUNCTION)) {
				newClass->addMethod(parseMethod());
			} else {
				break;
			}
		} while (currentToken != 0);
	}

	Method * Parser::parseMethod()
	{
		// read in protection level / static
		bool isStatic = false;
		AccessModifier accessModifier = PUBLIC_ACCESS;
		while (true) {
			if (acceptToken(KEYWORD_PUBLIC)) {
				accessModifier = PUBLIC_ACCESS;
			} else if (acceptToken(KEYWORD_PRIVATE)) {
				accessModifier = PRIVATE_ACCESS;
			} else if (acceptToken(KEYWORD_STATIC)) {
				isStatic = true;
			} else {
				break;
			}
		}

		// function name
		if (currentToken != IDENTIFIER) {
			// TODO syntax error
			throw QString("Expected Identifier (Function Name)");
		}
		QString name(fileScanner->getText());
		readNextToken();

		// parameters
		expectToken(SYM_PAREN_OPEN, "Expected opening parenthesis");
		do {
			// @todo
		} while (acceptToken(SYM_COMMA));
		expectToken(SYM_PAREN_CLOSE, "Expected closing parenthesis");

		// function body
		expectToken(SYM_CURLY_OPEN, "Expected opening curly bracket");
		QLinkedList<Statement *> bodyStatements;
		while (true) {
			Statement * stmt = parseStatement();

			if (stmt == 0) {
				break;
			}
			bodyStatements.append(stmt);
		}
		expectToken(SYM_CURLY_CLOSE, "Expected closing curly bracket");

		Method * ret = new Method(name, bodyStatements, accessModifier, isStatic);
		return ret;
	}

	Statement * Parser::parseStatement()
	{
		// check for control keywords: for,while,do,etc
		// TODO
		if (acceptToken(KEYWORD_ECHO)) {
			Expression * expr = parseExpression(parseExpressionTerminal(), 0);
			expectToken(SYM_SEMICOLON, "Expected Semicolon");
			return new EchoStatement(expr);
		}

		// not a control statement; must be an expression
		Expression * expr = parseExpression(parseExpressionTerminal(), 0);
		if (expr != 0) {
			expectToken(SYM_SEMICOLON, "Expected Semicolon");
			return new ExpressionStatement(expr);
		}

		return NULL;
	}

	Expression * Parser::parseExpression(Expression * lhs, int minPrecedence)
	{
		while (isTokenOperator(currentToken) && getTokenPrecedence(currentToken) >= minPrecedence) {
			Token op = currentToken;
			readNextToken();

			Expression * rhs = parseExpressionTerminal();

			while (isTokenOperator(currentToken) && getTokenPrecedence(currentToken) > getTokenPrecedence(op)) {
				rhs = parseExpression(rhs, getTokenPrecedence(currentToken));
			}

			lhs = combineExpressionsOperator(lhs, rhs, op);
		}

		return lhs;
	}

	Expression * Parser::combineExpressionsOperator(Expression * lhs, Expression * rhs, Token op)
	{
		switch (op) {
			case SYM_ASSIGNMENT: {
				return new AssignmentExpression(lhs, rhs);
			}

			case SYM_PLUS: {
				InstanceMethodExpression * ret = new InstanceMethodExpression("__operator+", lhs);
				ret->addArgument(rhs);
				return ret;
			}

			case SYM_MINUS: {
				InstanceMethodExpression * ret = new InstanceMethodExpression("__operator-", lhs);
				ret->addArgument(rhs);
				return ret;
			}

			case SYM_MULTIPLY: {
				InstanceMethodExpression * ret = new InstanceMethodExpression("__operator*", lhs);
				ret->addArgument(rhs);
				return ret;
			}

			case SYM_DIVIDE: {
				InstanceMethodExpression * ret = new InstanceMethodExpression("__operator/", lhs);
				ret->addArgument(rhs);
				return ret;
			}

			case SYM_MODULUS: {
				InstanceMethodExpression * ret = new InstanceMethodExpression("__operator%", lhs);
				ret->addArgument(rhs);
				return ret;
			}

			case SYM_PERIOD: {
				// Period needs to do some heavy lifting
				//return ParseDotOperator(lhs, rhs);
			}

			case SYM_SCOPE_RESOLUTION: {
				// Scope resolution needs to do some heavy lifting
				//return ParseScopeResolutionOperator(lhs, rhs);
			}

			default:
				throw QString("Invalid Operator");
		}
	}

	Expression * Parser::parseScopeResolutionOperator(Expression * lhs, Expression * rhs)
	{
		// LHS must be an identifier
		//IdentifierExpression * lhsIdent = dynamic_cast<IdentifierExpression *>(lhs);
		//if (lhsIdent == 0) {
			// TODO compile time error
		//	throw QString("LHS of Scope Resolution Operator must be an identifier");
		//}

		// if RHS is a variable then this is static member variable access
		//VariableExpression * varRhs = dynamic_cast<VariableExpression *>(rhs);
		//if (varRhs != 0) {
		//	return new StaticVariableExpression(lhsIdent->GetIdentifier(), varRhs->GetVariableName());
		//}

		// if RHS is an identifier than this is static function access
		//IdentifierExpression * rhsIdent = dynamic_cast<IdentifierExpression *>(rhs);
		//if (rhsIdent == 0) {
			// TODO compile time error
		//	throw QString("Scope resolution operator with invalid operands");
		//}

		//ExpectToken(SYM_PAREN_OPEN, "Expected Opening Paren");
		//ArgumentListExpression * argList = new ArgumentListExpression();
		//do {
		//	Expression * arg = ParseExpression(ParseExpressionTerminal(), 0);
		//	if (arg == 0) {
		//		break;
		//	}

		//	argList->AddArgument(arg);
		//} while (AcceptToken(SYM_COMMA));

		//ExpectToken(SYM_PAREN_CLOSE, "Expected Closing Paren");

		//return new StaticFunctionExpression(lhs, rhsIdent->GetIdentifier(), argList);
		return NULL;
	}

	Expression * Parser::parseDotOperator(Expression * lhs, Expression * rhs)
	{
		// TODO check LHS to see what it is?

		// RHS has to be an identifier
		//IdentifierExpression * rhsIdent = dynamic_cast<IdentifierExpression *>(rhs);
		//if (rhsIdent == 0) {
			// TODO compile error
		//	throw QString("RHS Must be an identifier");
		//}

		// do we have an opening paren next?
		//if (AcceptToken(SYM_PAREN_OPEN)) {
		//	ArgumentListExpression * argList = new ArgumentListExpression();
		//	do {
		//		Expression * arg = ParseExpression(ParseExpressionTerminal(), 0);
		//		if (arg == 0) {
		//			break;
		//		}

		//		argList->AddArgument(arg);
		//	} while (AcceptToken(SYM_COMMA));

		//	ExpectToken(SYM_PAREN_CLOSE, "Expected Closing Paren");

		//	return new InstanceFunctionExpression(lhs, rhsIdent->GetIdentifier(), argList);
		//}

		// no paren, this must be member variable access
		// TODO
		//throw QString("Not Implemented Yet");
		return NULL;
	}

	Expression * Parser::parseExpressionTerminal()
	{
		Expression * ret = NULL;

		// variable
		if (currentToken == VARIABLE) {
			ret = new VariableExpression(fileScanner->getText().mid(1));
			readNextToken();
		}

		// identifier
		//if (currentToken == IDENTIFIER) {
		//	Expression * ret = new IdentifierExpression(fileScanner->GetText());
		//	ReadNextToken();
		//	return ret;
		//}

		// constant integer
		if (currentToken == CONSTANT_INT) {
			ret = new ConstantIntegerExpression(atoi(fileScanner->getText().toLatin1()));
			readNextToken();
		}

		// expression inside parens
		if (acceptToken(SYM_PAREN_OPEN)) {
			ret = parseExpression(parseExpressionTerminal(), 0);
			expectToken(SYM_PAREN_CLOSE, "Expected closing parenthesis");
		}

		return ret;
	}
}
