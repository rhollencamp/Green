#include <iostream>

#include "Class/Class.h"
#include "EchoStatement.h"
#include "Expression/Expression.h"
#include "Frame.h"
#include "ObjectInstance.h"
#include "Types/String.h"
#include "VirtualMachine.h"


namespace Green
{
	void EchoStatement::execute(Frame * frame) const
	{
		ObjectInstance * rhsResult = rhs->execute(frame);

		const Method * toString = rhsResult->getClass()->getMethod("toString");
		Q_ASSERT(toString != NULL);

		Frame newFrame(frame->getVirtualMachine(), rhsResult->getClass(), toString, rhsResult);
		ObjectInstance * rhsResultString = toString->execute(&newFrame);
		Q_ASSERT(rhsResultString != NULL);
		QString result = Type::String::getQString(rhsResultString);

		std::cout << qPrintable(result) << std::endl;
	}
}
