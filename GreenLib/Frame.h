#pragma once

#include <QHash>
#include "ObjectInstance.h"


namespace Green
{
	class Class;
	class Method;
	class VirtualMachine;


	class Frame
	{
		public:
			Frame(VirtualMachine * vm, const Class * clazz, const Method * method, ObjectInstance * thisPtr);
			~Frame();

			VirtualMachine * getVirtualMachine() const;
			const Class * getClass() const;
			const Method * getMethod() const;
			ObjectInstance * getThis() const;

			void setLocalVar(const QString& name, ObjectInstance * val);
			ObjectInstance * getLocalVar(const QString& name) const;


		private:
			Q_DISABLE_COPY(Frame)

			VirtualMachine * vm;
			const Class * clazz;
			const Method * method;
			ObjectInstance * thisPtr;

			QHash<QString, ObjectInstance*> localVars;
	};


	inline Frame::Frame(VirtualMachine * vm, const Class * clazz, const Method * method, ObjectInstance * thisPtr)
		: vm(vm), clazz(clazz), method(method), thisPtr(thisPtr)
	{
	}

	inline Frame::~Frame() { }

	inline const Class * Frame::getClass() const
	{
		return clazz;
	}

	inline VirtualMachine * Frame::getVirtualMachine() const
	{
		return vm;
	}

	inline const Method * Frame::getMethod() const
	{
		return method;
	}

	inline ObjectInstance * Frame::getThis() const
	{
		return thisPtr;
	}

	inline void Frame::setLocalVar(const QString& name, ObjectInstance * val)
	{
		localVars.insert(name, val);
	}

	inline ObjectInstance * Frame::getLocalVar(const QString& name) const
	{
		return localVars.value(name, NULL);
	}
}
