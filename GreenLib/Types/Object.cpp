#include <QTextStream>

#include "Class/Class.h"
#include "Frame.h"
#include "Object.h"
#include "String.h"


namespace Green
{
	namespace Type
	{
		namespace Object
		{
			Class clazz("Object", "green.lang", NULL);

			/**
			 * toString method
			 */
			static ObjectInstance * toStringImpl(Frame * frame)
			{
				const Class * clazz = frame->getClass();

				QString str;
				QTextStream stream(&str);
				stream << clazz->getPackage() << "." << clazz->getName() << "@" << frame->getThis();
				return String::instantiate(str);
			}
			Method toStringMethod("toString", &toStringImpl, PUBLIC_ACCESS, false);

			Class * createClass()
			{
				clazz.addMethod(&toStringMethod);

				return &clazz;
			}
		}
	}
}
