#pragma once

#include <QLinkedList>
#include <QList>
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
			explicit Method(const QString& name, StaticMethodBody body, const AccessModifier access, bool isStatic);
			explicit Method(const QString& name, QLinkedList<Statement*> body, const AccessModifier access, bool isStatic);
			~Method();

			QString getName() const;
			bool getIsStatic() const;
			AccessModifier getAccessModifier() const;
			QList<QString> getParameters() const;

			void addParameter(const QString& param);

			ObjectInstance * execute(Frame * frame) const;


		private:
			Q_DISABLE_COPY(Method)

			QString name;
			bool isStatic;
			AccessModifier access;
			QList<QString> parameters;

			StaticMethodBody staticBody;
			QLinkedList<Statement*> dynamicBody;
	};


	inline Method::Method(const QString& name, QLinkedList<Statement *> body, const AccessModifier access, bool isStatic)
		: name(name), dynamicBody(body), staticBody(NULL), access(access), isStatic(isStatic)
	{
	}

	inline Method::Method(const QString& name, StaticMethodBody body, const AccessModifier access, bool isStatic)
		: name(name), staticBody(body), access(access), isStatic(isStatic)
	{
	}

	inline Method::~Method() { }

	inline QString Method::getName() const
	{
		return name;
	}

	inline bool Method::getIsStatic() const
	{
		return isStatic;
	}

	inline AccessModifier Method::getAccessModifier() const
	{
		return access;
	}

	inline void Method::addParameter(const QString& param)
	{
		parameters.append(param);
	}

	inline QList<QString> Method::getParameters() const
	{
		return parameters;
	}
}
