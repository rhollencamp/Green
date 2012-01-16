#pragma once

#include "Expression.h"


namespace Green
{
	class ConstantIntegerExpression : public Expression
	{
		public:
			explicit ConstantIntegerExpression(int value);
			~ConstantIntegerExpression();

			ObjectInstance * execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(ConstantIntegerExpression)

			int value;
	};


	inline ConstantIntegerExpression::ConstantIntegerExpression(int value)
		: value(value)
	{
	}

	inline ConstantIntegerExpression::~ConstantIntegerExpression() { }
}
