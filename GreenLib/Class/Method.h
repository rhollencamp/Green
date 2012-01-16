#pragma once

#include <QLinkedList>
#include <QString>
#include "AccessModifier.h"


namespace Green
{
	class ObjectInstance;
	class Frame;
	class Statement;


	// typedef a function pointer to a statical method body
	typedef
		ObjectInstance*       // return value
		(*StaticMethodBody)   // typedef name
		(Frame *);            // arg list


	class Method
	{
		public:
			explicit Method(const QString& name, StaticMethodBody body);
			explicit Method(const QString& name, QLinkedList<Statement*> body);
			~Method();

			QString getName() const;

			void setIsStatic(const bool isStatic);
			bool getIsStatic() const;

			void setAccessModifier(const AccessModifier access);
			AccessModifier getAccessModifier() const;

			ObjectInstance * execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(Method)

			QString name;
			bool isStatic;
			AccessModifier access;

			StaticMethodBody staticBody;
			QLinkedList<Statement*> dynamicBody;
	};


	inline Method::Method(const QString& name, QLinkedList<Statement *> body)
		: name(name), dynamicBody(body), staticBody(NULL)
	{
	}

	inline Method::Method(const QString& name, StaticMethodBody body)
		: name(name), staticBody(body)
	{
	}

	inline Method::~Method() { }

	inline QString Method::getName() const
	{
		return name;
	}

	inline void Method::setIsStatic(const bool isStatic)
	{
		this->isStatic = isStatic;
	}

	inline bool Method::getIsStatic() const
	{
		return isStatic;
	}

	inline void Method::setAccessModifier(const AccessModifier access)
	{
		this->access = access;
	}

	inline AccessModifier Method::getAccessModifier() const
	{
		return access;
	}
}
