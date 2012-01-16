#include "Types/Integer.h"
#include "Types/String.h"
#include "VirtualMachine.h"


namespace Green
{
	VirtualMachine::VirtualMachine()
	{
		addClass(Type::String::createClass());
		addClass(Type::Integer::createClass());
	}

	void VirtualMachine::run(Class * clazz)
	{
		Q_ASSERT(clazz != NULL);

		// find the main method
		const Method * mainMethod = clazz->getMethod("main");
		if (mainMethod == NULL) {
			return; // @todo exception?
		}

		// make sure is static
		if (mainMethod->getIsStatic() == false) {
			return; // @todo exception?
		}

		// make sure is public
		if (mainMethod->getAccessModifier() != PUBLIC_ACCESS) {
			return; // @todo exception?
		}

		runMethod(clazz, mainMethod);
	}

	void VirtualMachine::runMethod(const Class * clazz, const Method * method)
	{
		Q_ASSERT(clazz != NULL);
		Q_ASSERT(method != NULL);

		// create a frame
		Frame * frame = new Frame(this, clazz, method, NULL);
		frames.push(frame);
		method->execute(frame);
		frames.pop();
	}
}
