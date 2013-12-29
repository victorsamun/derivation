#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "parse_error.h"
#include "symbolic_function.h"
#include "scanner.h"
#include "parser.hpp"
#include <string>

namespace symbolic {

class driver {
	function value;

public:
	function parse (const std::string & str) throw (parse_error);

	void set (const function & f);
};

}

#endif

