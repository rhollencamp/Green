#include "Types/Integer.h"
#include "Types/Object.h"
#include "Types/String.h"
#include "VirtualMachine.h"


namespace Green
{
	VirtualMachine::VirtualMachine()
	{
		addClass(Type::Object::createClass());
		addClass(Type::String::createClass());
		addClass(Type::Integer::createClass());
	}

	void VirtualMachine::run(const Class * clazz)
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

		// create frame and run
		Frame frame(this, clazz, mainMethod, NULL);
		frames.push(&frame);
		mainMethod->execute(&frame);
		frames.pop();
	}
}
