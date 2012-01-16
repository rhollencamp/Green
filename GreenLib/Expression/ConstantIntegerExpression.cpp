#include "ConstantIntegerExpression.h"
#include "Types/Integer.h"


namespace Green
{
	ObjectInstance * ConstantIntegerExpression::execute(Frame *) const
	{
		return Type::Integer::instantiate(value);
	}
}
