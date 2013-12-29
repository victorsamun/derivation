#include "driver.h"
#include <sstream>

using namespace symbolic;

function driver::parse (const std::string & str) throw (parse_error) {
	std::istringstream is (str);

	scanner s (& is);
	parser (s, * this).parse ();

	return value;
}

void driver::set (const function & f) {
	value = f;
}

