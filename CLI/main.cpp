#include "Class/Class.h"
#include "Parser/Parser.h"
#include "VirtualMachine.h"

#include <iostream>
using std::cout;
using std::endl;


int main()
{
	Green::Parser p("C:\\Users\\Robert Hollencamp\\Desktop\\test.txt");
	Green::Class * clazz = p.parse();

	// Virtual Machine
	Green::VirtualMachine vm;
	vm.addClass(clazz);
	vm.run(clazz);

	return 0;
}
