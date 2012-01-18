#pragma once

#include "Expression.h"


namespace Green
{
	class InstanceMethodExpression : public Expression
	{
		public:
			InstanceMethodExpression(const QString& name, const Expression * thisPtrExpr);
			~InstanceMethodExpression();

			ObjectInstance * execute(Frame *frame) const;

			void addArgument(const Expression * expr);


		private:
			Q_DISABLE_COPY(InstanceMethodExpression)

			QString methodName;
			const Expression * thisPtrExpr;
			QList<const Expression*> arguments;
	};


	inline InstanceMethodExpression::InstanceMethodExpression(const QString& name, const Expression * thisPtrExpr)
		: methodName(name), thisPtrExpr(thisPtrExpr)
	{
		Q_ASSERT(thisPtrExpr != NULL);
		Q_ASSERT(methodName.isNull() == false);
		Q_ASSERT(methodName.isEmpty() == false);
	}

	inline InstanceMethodExpression::~InstanceMethodExpression() { }

	inline void InstanceMethodExpression::addArgument(const Expression* expr)
	{
		arguments.append(expr);
	}
}
