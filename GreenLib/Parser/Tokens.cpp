#include <QString>

#include "Tokens.h"


namespace Green
{
	int getTokenPrecedence(const Token tok)
	{
		switch (tok) {
			case SYM_SCOPE_RESOLUTION:
				return 5;

			case SYM_PERIOD:
				return 4;

			case SYM_MULTIPLY:
			case SYM_DIVIDE:
			case SYM_MODULUS:
				return 3;

			case SYM_PLUS:
			case SYM_MINUS:
				return 2;

			case SYM_ASSIGNMENT:
				return 1;

			default:
				throw QString("Unknown Token");
		}
	}


	bool isTokenOperator(const Token tok)
	{
		switch (tok) {
			case SYM_PLUS:
			case SYM_MINUS:
			case SYM_MULTIPLY:
			case SYM_DIVIDE:
			case SYM_MODULUS:
			case SYM_ASSIGNMENT:
			case SYM_PERIOD:
			case SYM_SCOPE_RESOLUTION:
				return true;

			default:
				return false;
		}
	}
}
