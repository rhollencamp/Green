#include "Class/Class.h"
#include "Expression.h"
#include "Frame.h"
#include "InstanceMethodExpression.h"


namespace Green
{
	ObjectInstance * InstanceMethodExpression::execute(Frame * frame) const
	{
		// get this
		ObjectInstance * thisPtr = thisPtrExpr->execute(frame);
		Q_ASSERT(thisPtr != NULL);
		const Class * clazz = thisPtr->getClass();

		// find method in question
		const Method * method = clazz->getMethod(methodName);
		Q_ASSERT(method != NULL);

		// create frame
		Frame newFrame(frame->getVirtualMachine(), clazz, method, thisPtr);
		// set args
		QList<QString> parameters = method->getParameters();
		Q_ASSERT(parameters.size() == arguments.size());
		for (int i = 0; i < arguments.size(); i++) {
			ObjectInstance * value = arguments.at(i)->execute(frame);
			newFrame.setLocalVar(parameters.at(i), value);
		}


		return method->execute(&newFrame);
	}
}
