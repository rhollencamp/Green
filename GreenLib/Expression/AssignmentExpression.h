#pragma once

#include "Expression.h"


namespace Green
{
	class VariableExpression;


	class AssignmentExpression : public Expression
	{
		public:
			AssignmentExpression(const Expression * lhs, const Expression * rhs);
			~AssignmentExpression();

			ObjectInstance * execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(AssignmentExpression)

			const VariableExpression * lhs;
			const Expression * rhs;
	};
}
