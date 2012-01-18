!include( ../Common.pri ) {
		error( Could not open Common.pri )
}

QT       -= gui

TARGET = GreenLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
	Parser/Scanner.cpp \
	Parser/Tokens.cpp \
	VirtualMachine.cpp \
    Statement/ExpressionStatement.cpp \
    Expression/VariableExpression.cpp \
    Parser/Parser.cpp \
    Expression/AssignmentExpression.cpp \
    Types/String.cpp \
    Class/Method.cpp \
    Statement/EchoStatement.cpp \
    Types/Integer.cpp \
    Expression/ConstantIntegerExpression.cpp \
    Expression/InstanceMethodExpression.cpp \
    Types/Object.cpp

HEADERS += \
	Parser/Scanner.h \
	Parser/Tokens.h \
	Parser/FlexLexer.h \
	ObjectInstance.h \
	Class/Class.h \
	Class/Field.h \
	Class/Method.h \
	Class/AccessModifier.h \
	VirtualMachine.h \
	Frame.h \
	Statement/Statement.h \
    Statement/ExpressionStatement.h \
    Expression/Expression.h \
    Expression/IdentifierExpression.h \
    Expression/VariableExpression.h \
    Parser/Parser.h \
    Expression/AssignmentExpression.h \
    Types/String.h \
    Statement/EchoStatement.h \
    Types/Integer.h \
    Expression/ConstantIntegerExpression.h \
    Expression/InstanceMethodExpression.h \
    Types/Object.h

OTHER_FILES += \
	Parser/Scanner.l
