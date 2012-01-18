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

			void addClass(const Class * clazz);

			void run(const Class * clazz);


		private:
			Q_DISABLE_COPY(VirtualMachine)

			QStack<Frame *> frames;
			QHash<QString, const Class *> classes;
	};


	inline VirtualMachine::~VirtualMachine() { }

	inline void VirtualMachine::addClass(const Class * clazz)
	{
		classes.insert(clazz->getName(), clazz);
	}
}
