#pragma once

#include <QObject>
#include "AccessModifier.h"

namespace Green
{
	class Field
	{
		public:
			Field();
			~Field();

			QString getName() const;
			void setName(const QString& name);

			bool getIsStatic() const;
			void setIsStatic(const bool isStatic);

			AccessModifier getAccessModifier() const;
			void setAccessModifier(const AccessModifier access);

		private:
			Q_DISABLE_COPY(Field)

			QString name;
			bool isStatic;
			AccessModifier access;
	};


	inline Field::Field() { }

	inline Field::~Field() { }

	inline QString Field::getName() const
	{
		return name;
	}

	inline void Field::setName(const QString& name)
	{
		this->name = name;
	}

	inline bool Field::getIsStatic() const
	{
		return isStatic;
	}

	inline void Field::setIsStatic(const bool isStatic)
	{
		this->isStatic = isStatic;
	}

	inline AccessModifier Field::getAccessModifier() const
	{
		return access;
	}

	inline void Field::setAccessModifier(const AccessModifier access)
	{
		this->access = access;
	}
}
