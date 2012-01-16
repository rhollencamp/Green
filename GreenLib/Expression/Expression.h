#pragma once

#include <QObject>


namespace Green
{
	class Frame;
	class ObjectInstance;


	class Expression
	{
		public:
			Expression();
			virtual ~Expression();

			virtual ObjectInstance * execute(Frame * frame) const = 0;


		private:
			Q_DISABLE_COPY(Expression)
	};


	inline Expression::Expression() { }

	inline Expression::~Expression() { }
}
