#include "MethodBody.h"


namespace Green
{
	ObjectInstance * MethodBody::execute(Frame * frame) const
	{
		// if we have a static method body, call it
		if (staticBody != NULL) {
			return (*staticBody)(frame);
		}

		// call dynamic method body
		return NULL;
	}
}
