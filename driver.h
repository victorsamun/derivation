#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "parse_error.h"
#include "symbolic_function.h"
#include "scanner.h"
#include "parser.hpp"
#include <string>

namespace symbolic {

class driver {
	parser * m_parser;
	scanner * m_scanner;

	function m_value;

public:
	driver ();

	void parse (const std::string & str) throw (parse_error);

	void set (const function & f);
	function get () const;

	virtual ~driver ();
};

}

#endif

