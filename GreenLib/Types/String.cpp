#include "String.h"
#include "Class/Class.h"
#include "Frame.h"


namespace Green
{
	namespace Type
	{
		namespace String
		{
			static Class clazz("String", "green.lang");

			/**
			 * toString method
			 */
			static ObjectInstance * toStringImpl(Frame * frame)
			{
				return frame->getThis();
			}
			static Method toStringMethod("toString", &toStringImpl);

			/**
			 * constructor method
			 */
			static ObjectInstance * ctorImpl(Frame * frame)
			{
				ObjectInstance * thisPtr = frame->getThis();
				thisPtr->setData(new QString());
				return thisPtr;
			}
			static Method ctorMethod("__construct", &ctorImpl);

			/**
			 * Build and return the String class instance
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
			 * Get QString data from a String object instance
			 */
			QString getQString(ObjectInstance * object)
			{
				QString * data = (QString *)object->getData();
				return QString(*data);
			}

			/**
			 * Instantiate a String object
			 */
			ObjectInstance * instantiate(const QString& initial)
			{
				ObjectInstance * ret = new ObjectInstance(&clazz);
				ret->setData(new QString(initial));
				return ret;
			}
		}
	}
}
