#pragma once

#include <QHash>


namespace Green
{
	class Class;


	class ObjectInstance
	{
		public:
			explicit ObjectInstance(const Class * const);
			ObjectInstance(const Class * const c, ObjectInstance * parent);

			const Class * getClass() const;

			void * getData() const;
			void setData(void * data);

			ObjectInstance * getField(const QString& name) const;
			void setField(const QString& name, ObjectInstance * value);

			ObjectInstance * getParent() const;


		private:
			Q_DISABLE_COPY(ObjectInstance)

			const Class * const clazz;
			void * data;
			QHash<QString, ObjectInstance *> fields;
			ObjectInstance * parent;
	};


	inline ObjectInstance::ObjectInstance(const Class * const c)
		: clazz(c)
	{
	}

	inline ObjectInstance::ObjectInstance(const Class * const c, ObjectInstance * parent)
		:clazz(c), parent(parent)
	{
	}

	inline Class const * ObjectInstance::getClass() const
	{
		return clazz;
	}

	inline void * ObjectInstance::getData() const
	{
		return data;
	}

	inline void ObjectInstance::setData(void * data)
	{
		this->data = data;
	}

	inline ObjectInstance * ObjectInstance::getField(const QString& name) const
	{
		return fields.value(name, NULL);
	}

	inline void ObjectInstance::setField(const QString& name, ObjectInstance * value)
	{
		fields.insert(name, value);
	}

	inline ObjectInstance * ObjectInstance::getParent() const
	{
		return parent;
	}
}
