#include "ExpressionStatement.h"
#include "Frame.h"
#include "Expression/Expression.h"


namespace Green
{
	void ExpressionStatement::execute(Frame * frame) const
	{
		Q_ASSERT(frame != NULL);
		expression->execute(frame);
	}
}
