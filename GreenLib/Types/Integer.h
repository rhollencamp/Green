#pragma once


namespace Green
{
	class Class;
	class ObjectInstance;


	namespace Type
	{
		namespace Integer
		{
			Class * createClass();

			ObjectInstance * instantiate(int);

			int getInt(ObjectInstance *);
		}
	}
}
