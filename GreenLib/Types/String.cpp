#include "String.h"
#include "Class/Class.h"
#include "Frame.h"


namespace Green
{
	namespace Type
	{
		namespace Object
		{
			extern Class clazz;
		}


		namespace String
		{
			static Class clazz("String", "green.lang", &Object::clazz);

			/**
			 * toString method
			 */
			static ObjectInstance * toStringImpl(Frame * frame)
			{
				return frame->getThis();
			}
			static Method toStringMethod("toString", &toStringImpl, PUBLIC_ACCESS, false);

			/**
			 * constructor method
			 */
			static ObjectInstance * ctorImpl(Frame * frame)
			{
				ObjectInstance * thisPtr = frame->getThis();
				thisPtr->setData(&clazz, new QString());
				return thisPtr;
			}
			static Method ctorMethod("__construct", &ctorImpl, PUBLIC_ACCESS, false);

			/**
			 * Build and return the String class instance
			 */
			Class * createClass()
			{
				clazz.addMethod(&ctorMethod);
				clazz.addMethod(&toStringMethod);

				return &clazz;
			}

			/**
			 * Get QString data from a String object instance
			 */
			QString getQString(ObjectInstance * object)
			{
				QString * data = (QString *)object->getData(&clazz);
				return QString(*data);
			}

			/**
			 * Instantiate a String object
			 */
			ObjectInstance * instantiate(const QString& initial)
			{
				ObjectInstance * ret = new ObjectInstance(&clazz);
				ret->setData(&clazz, new QString(initial));
				return ret;
			}
		}
	}
}
