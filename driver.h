#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "symbolic_function.h"
#include "scanner.h"
#include "parser.hpp"
#include <string>

namespace symbolic {

class driver {
	parser * p;
	scanner * s;

	function v;

public:
	driver ()
		: p (nullptr), s (nullptr)
	{ }

	void parse (const std::string & str);

	void set (const function & f);
	function get () const;

	virtual ~driver ();
};

}

#endif

