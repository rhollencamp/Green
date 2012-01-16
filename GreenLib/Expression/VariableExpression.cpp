#include "VariableExpression.h"
#include "Frame.h"


namespace Green
{
	ObjectInstance * VariableExpression::execute(Frame * frame) const
	{
		// look up local variable
		return frame->getLocalVar(name);
	}
}
