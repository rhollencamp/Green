#pragma once

#include <QObject>
#include <QHash>
#include "Field.h"
#include "Method.h"


namespace Green
{
	class Class
	{
		public:
			Class(const QString& name, const QString& package, const Class * parent);

			const QString getName() const;
			const QString getPackage() const;

			void addField(const Field* const);
			const Field* getField(const QString&) const;

			void addMethod(const Method* const);
			const Method* getMethod(const QString& name) const;

			const Class * getParent() const;


		private:
			Q_DISABLE_COPY(Class)

			QString name;
			QString package;
			const Class * parent;
			QHash<QString, const Field*> fields;
			QHash<QString, const Method*> methods;
	};

	inline Class::Class(const QString& name, const QString& package, const Class * parent)
		: name(name), package(package), parent(parent)
	{
	}

	inline QString const Class::getName() const
	{
		return name;
	}

	inline QString const Class::getPackage() const
	{
		return package;
	}

	inline void Class::addField(const Field* const field)
	{
		fields.insert(field->getName(), field);
	}

	inline const Field* Class::getField(const QString& fieldName) const
	{
		return fields.value(fieldName, NULL);
	}

	inline void Class::addMethod(const Method* const method)
	{
		methods.insert(method->getName(), method);
	}

	inline const Method* Class::getMethod(const QString& name) const
	{
		const Method * ret = methods.value(name, NULL);
		if (ret == NULL && parent != NULL) {
			ret = parent->getMethod(name);
		}
		return ret;
	}

	inline const Class * Class::getParent() const
	{
		return parent;
	}
}
