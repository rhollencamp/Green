#pragma once

#include "Statement.h"


namespace Green
{
	class Expression;


	class EchoStatement : public Statement
	{
		public:
			explicit EchoStatement(const Expression * rhs);
			~EchoStatement();

			void execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(EchoStatement)

			const Expression * rhs;
	};


	inline EchoStatement::EchoStatement(const Expression * rhs)
		: rhs(rhs)
	{
		Q_ASSERT(rhs != NULL);
	}

	inline EchoStatement::~EchoStatement() { }
}
