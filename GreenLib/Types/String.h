#pragma once

#include <QString>


namespace Green
{
	class Class;
	class ObjectInstance;


	namespace Type
	{
		namespace String
		{
			Class * createClass();

			ObjectInstance * instantiate(const QString&);

			QString getQString(ObjectInstance * object);
		}
	}
}
