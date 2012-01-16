#pragma once

#include <QString>
#include "Expression.h"


namespace Green
{
	class VariableExpression : public Expression
	{
		public:
			explicit VariableExpression(const QString& name);
			~VariableExpression();

			QString getName() const;

			ObjectInstance * execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(VariableExpression)

			QString name;
	};


	inline VariableExpression::VariableExpression(const QString& name)
		: name(name)
	{
	}

	inline VariableExpression::~VariableExpression() { }

	inline QString VariableExpression::getName() const
	{
		return name;
	}
}
