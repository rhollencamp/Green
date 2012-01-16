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
			Class(const QString& name, const QString& package);

			const QString getName() const;
			const QString getPackage() const;

			void addField(const Field* const);
			const Field* getField(const QString&) const;

			void addMethod(const Method* const);
			const Method* getMethod(const QString& name) const;


		private:
			Q_DISABLE_COPY(Class)

			QString name;
			QString package;
			QHash<QString, const Field*> fields;
			QHash<QString, const Method*> methods;
	};

	inline Class::Class(const QString& name, const QString& package)
		: name(name), package(package)
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
		return methods.value(name, NULL);
	}
}
