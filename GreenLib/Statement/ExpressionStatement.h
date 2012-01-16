#pragma once

#include "Statement.h"

namespace Green
{
	class Frame;
	class Expression;


	class ExpressionStatement : public Statement
	{
		public:
			explicit ExpressionStatement(const Expression * expr);
			~ExpressionStatement();

			void execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(ExpressionStatement)

			const Expression * expression;
	};


	inline ExpressionStatement::ExpressionStatement(const Expression * expr)
		: expression(expr)
	{
		Q_ASSERT(expr != NULL);
	}

	inline ExpressionStatement::~ExpressionStatement() { }
}
