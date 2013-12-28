#include "symbolic_function.h"
#include <iostream>

using symbolic::function;

int main () {
	/*
	function f = function::num (2) * function::var ().pow (3) + function::var ();
	std::cout << f << std::endl;

	function f1 = f.derivative ();
	function f2 = f1.derivative ();
	function f3 = f2.derivative ();
	function f4 = f3.derivative ();

	std::cout << f1 << std::endl <<
		f2 << std::endl <<
		f3 << std::endl <<
		f4 << std::endl;
	*/

	function f = function::ln (function::abs (function::sin (function::var ())));
	std::cout << f << " -> " << f.derivative () << std::endl;

	return 0;
}
