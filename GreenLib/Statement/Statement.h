#pragma once

#include <QObject>


namespace Green
{
	class Frame;


	class Statement
	{
		public:
			Statement();
			virtual ~Statement();

			virtual void execute(Frame * frame) const = 0;


		private:
			Q_DISABLE_COPY(Statement)
	};


	inline Statement::Statement() { }

	inline Statement::~Statement() { }
}
