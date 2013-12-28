#include "symbolic_function.h"
#include "driver.h"
#include <iostream>
#include <string>

using symbolic::driver;
using symbolic::function;

int main () {
	std::string s;

	std::getline (std::cin, s);

	driver d;
	d.parse (s);

	std::cout << s << " -> " << d.get () << std::endl;
	std::cout << "(" << s << ")' = " << d.get ().derivative () << std::endl;

	return 0;
}

