#include "AssignmentExpression.h"
#include "Frame.h"
#include "VariableExpression.h"


namespace Green
{
	AssignmentExpression::AssignmentExpression(const Expression * lhs, const Expression * rhs)
		: rhs(rhs)
	{
		Q_ASSERT(lhs != NULL);
		Q_ASSERT(rhs != NULL);

		this->lhs = dynamic_cast<const VariableExpression *>(lhs);
		Q_ASSERT(this->lhs != NULL); // @todo syntax error
	}

	AssignmentExpression::~AssignmentExpression()
	{
		Q_ASSERT(lhs != NULL);
		Q_ASSERT(rhs != NULL);

		delete lhs;
		delete rhs;
	}

	ObjectInstance * AssignmentExpression::execute(Frame * frame) const
	{
		Q_ASSERT(frame != NULL);
		ObjectInstance * val = rhs->execute(frame);

		QString varName = this->lhs->getName();
		frame->setLocalVar(varName, val);
		return val;
	}
}
