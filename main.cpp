#include "symbolic_function.h"
#include "parse_error.h"
#include <iostream>
#include <string>

using symbolic::parse_error;
using symbolic::function;

int main () {
	std::string s;
	std::getline (std::cin, s);

	function f;
	try {
		f = function::parse (s);
	}
	catch (const parse_error & e) {
		std::cerr << "Parse error: " << e.what () << std::endl;
		return 1;
	}

	std::cout << s << " -> " << f << std::endl;
	std::cout << "(" << s << ")' = " << f.derivative () << std::endl;

	return 0;
}

