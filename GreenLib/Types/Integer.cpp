#include "Class/Class.h"
#include "Frame.h"
#include "Integer.h"
#include "String.h"


namespace Green
{
	namespace Type
	{
		namespace Integer
		{
			static Class clazz("Integer", "green.lang");

			/**
			 * toString method
			 */
			static ObjectInstance * toStringImpl(Frame * frame)
			{
				int * data = (int*)frame->getThis()->getData();
				QString str = QString::number(*data);
				return String::instantiate(str);
			}
			static Method toStringMethod("toString", &toStringImpl);

			/**
			 * constructor method
			 */
			static ObjectInstance * ctorImpl(Frame * frame)
			{
				ObjectInstance * thisPtr = frame->getThis();
				int * data = new int;
				*data = 0;
				thisPtr->setData(data);
				return thisPtr;
			}
			static Method ctorMethod("__construct", &ctorImpl);

			/**
			 * Build up and return class
			 */
			Class * createClass()
			{
				// ctor
				ctorMethod.setAccessModifier(PUBLIC_ACCESS);
				clazz.addMethod(&ctorMethod);

				// toString
				toStringMethod.setAccessModifier(PUBLIC_ACCESS);
				clazz.addMethod(&toStringMethod);

				return &clazz;
			}

			/**
			 * Create a new instance
			 */
			ObjectInstance * instantiate(int value)
			{
				ObjectInstance * ret = new ObjectInstance(&clazz);
				int * data = new int;
				*data = value;
				ret->setData(data);
				return ret;
			}

			/**
			 * get the value of an Integer object
			 */
			int getInt(ObjectInstance * object)
			{
				int * data = (int*)object->getData();
				return *data;
			}
		}
	}
}
