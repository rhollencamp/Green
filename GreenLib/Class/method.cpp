#include "Frame.h"
#include "Method.h"
#include "Statement/Statement.h"


namespace Green
{
	ObjectInstance * Method::execute(Frame * frame) const
	{
		// if we have a static method body, call it
		if (staticBody != NULL) {
			return (*staticBody)(frame);
		}

		// execute dynamic body
		Statement * stmt;
		foreach (stmt, dynamicBody) {
			stmt->execute(frame);
		}
		return NULL;
	}
}
