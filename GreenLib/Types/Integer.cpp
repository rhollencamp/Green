#include "Class/Class.h"
#include "Frame.h"
#include "Integer.h"
#include "Object.h"
#include "String.h"


namespace Green
{
	namespace Type
	{
		namespace Object
		{
			extern Class clazz;
		}


		namespace Integer
		{
			Class clazz("Integer", "green.lang", &Object::clazz);

			/**
			 * toString method
			 */
			static ObjectInstance * toStringImpl(Frame * frame)
			{
				int * data = (int*)frame->getThis()->getData(&clazz);
				QString str = QString::number(*data);
				return String::instantiate(str);
			}
			static Method toStringMethod("toString", &toStringImpl, PUBLIC_ACCESS, false);

			/**
			 * constructor method
			 */
			static ObjectInstance * ctorImpl(Frame * frame)
			{
				ObjectInstance * thisPtr = frame->getThis();
				int * data = new int;
				*data = 0;
				thisPtr->setData(&clazz, data);
				return thisPtr;
			}
			static Method ctorMethod("__construct", &ctorImpl, PUBLIC_ACCESS, false);

			/**
			 * operator+ method
			 */
			static ObjectInstance * operatorPlusImpl(Frame * frame)
			{
				int lhsInt = getInt(frame->getThis());
				ObjectInstance * rhs = frame->getLocalVar("rhs");
				const Class * rhsClass = rhs->getClass();

				// int
				if (rhsClass == &clazz) {
					int rhsInt = getInt(rhs);
					return instantiate(lhsInt + rhsInt);
				}

				Q_ASSERT(false); // @todo synatx error
			}
			static Method operatorPlusMethod("__operator+", &operatorPlusImpl, PUBLIC_ACCESS, false);

			/**
			 * operator- method
			 */
			static ObjectInstance * operatorMinusImpl(Frame * frame)
			{
				int lhsInt = getInt(frame->getThis());
				ObjectInstance * rhs = frame->getLocalVar("rhs");
				const Class * rhsClass = rhs->getClass();

				// int
				if (rhsClass == &clazz) {
					int rhsInt = getInt(rhs);
					return instantiate(lhsInt - rhsInt);
				}

				Q_ASSERT(false); // @todo syntax error
			}
			static Method operatorMinusMethod("__operator-", &operatorMinusImpl, PUBLIC_ACCESS, false);

			/**
			 * operator/ method
			 */
			static ObjectInstance * operatorDivImpl(Frame * frame)
			{
				int lhsInt = getInt(frame->getThis());
				ObjectInstance * rhs = frame->getLocalVar("rhs");
				const Class * rhsClass = rhs->getClass();

				// int
				if (rhsClass == &clazz) {
					int rhsInt = getInt(rhs);
					Q_ASSERT(rhsInt != 0);
					return instantiate(lhsInt / rhsInt);
				}

				Q_ASSERT(false); // @todo syntax error
			}
			static Method operatorDivMethod("__operator/", &operatorDivImpl, PUBLIC_ACCESS, false);

			/**
			 * operator* method
			 */
			static ObjectInstance * operatorMultImpl(Frame * frame)
			{
				int lhsInt = getInt(frame->getThis());
				ObjectInstance * rhs = frame->getLocalVar("rhs");
				const Class * rhsClass = rhs->getClass();

				// int
				if (rhsClass == &clazz) {
					int rhsInt = getInt(rhs);
					return instantiate(lhsInt * rhsInt);
				}

				Q_ASSERT(false); // @todo syntax error
			}
			static Method operatorMultMethod("__operator*", &operatorMultImpl, PUBLIC_ACCESS, false);

			/**
			 * operator% method
			 */
			static ObjectInstance * operatorModImpl(Frame * frame)
			{
				int lhsInt = getInt(frame->getThis());
				ObjectInstance * rhs = frame->getLocalVar("rhs");
				const Class * rhsClass = rhs->getClass();

				// int
				if (rhsClass == &clazz) {
					int rhsInt = getInt(rhs);
					return instantiate(lhsInt % rhsInt);
				}

				Q_ASSERT(false); // @todo syntax error
			}
			static Method operatorModMethod("__operator%", &operatorModImpl, PUBLIC_ACCESS, false);

			/**
			 * Build up and return class
			 */
			Class * createClass()
			{
				clazz.addMethod(&ctorMethod);
				clazz.addMethod(&toStringMethod);

				operatorPlusMethod.addParameter("rhs");
				clazz.addMethod(&operatorPlusMethod);

				operatorMinusMethod.addParameter("rhs");
				clazz.addMethod(&operatorMinusMethod);

				operatorDivMethod.addParameter("rhs");
				clazz.addMethod(&operatorDivMethod);

				operatorMultMethod.addParameter("rhs");
				clazz.addMethod(&operatorMultMethod);

				operatorModMethod.addParameter("rhs");
				clazz.addMethod(&operatorModMethod);

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
				ret->setData(&clazz, data);
				return ret;
			}

			/**
			 * get the value of an Integer object
			 */
			int getInt(ObjectInstance * object)
			{
				int * data = (int*)object->getData(&clazz);
				return *data;
			}
		}
	}
}
