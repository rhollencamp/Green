/**
 * Virtual Machine holds all of the state for an execution
 *
 * @todo static variables
 */

#pragma once

#include <QStack>
#include <QHash>
#include "Frame.h"
#include "Class/Class.h"


namespace Green
{
	class VirtualMachine
	{
		public:
			VirtualMachine();
			~VirtualMachine();

			void addClass(Class * clazz);

			void run(Class * clazz);


		private:
			Q_DISABLE_COPY(VirtualMachine)

			QStack<Frame*> frames;
			QHash<QString, Class*> classes;

			void runMethod(const Class * clazz, const Method * method);
	};


	inline VirtualMachine::~VirtualMachine() { }

	inline void VirtualMachine::addClass(Class * clazz)
	{
		classes.insert(clazz->getName(), clazz);
	}
}
