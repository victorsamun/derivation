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
		f = function::parse (s).simplify ();
	}
	catch (const parse_error & e) {
		std::cerr << "Parse error: " << e.what () << std::endl;
		return 1;
	}

	function ans = f.derivative ().simplify ();

	std::cout << s << " -> " << f << std::endl;
	std::cout << "(" << s << ")' = " << ans << std::endl;

	return 0;
}

