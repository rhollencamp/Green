#pragma once

#include "Tokens.h"

#include <QString>

// Only include FlexLexer.h if it hasn't been already included
#if ! defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

// Windows doesn't have unistd.h and it doesn't appear to be necessary
#define YY_NO_UNISTD_H

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int Green::Scanner::yylex()


namespace Green
{
	class Scanner : private yyFlexLexer
	{
		public:
			Scanner();
			explicit Scanner(std::istream * in);

			Token getToken();
			QString getText();


		private:
			int yylex();

			Q_DISABLE_COPY(Scanner)
	};


	inline Scanner::Scanner()
		: yyFlexLexer(0, 0)
	{
	}

	inline Scanner::Scanner(std::istream * in)
		: yyFlexLexer(in, 0)
	{
	}

	inline Token Scanner::getToken()
	{
		return (Token)yylex();
	}

	inline QString Scanner::getText()
	{
		return QString(YYText());
	}
}
