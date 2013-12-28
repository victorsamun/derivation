#ifndef _PARSE_ERROR_H_
#define _PARSE_ERROR_H_

#include <string>

namespace symbolic {

class parse_error {
	std::string s;

public:
	parse_error (const std::string & s);

	std::string what () const;
};

}

#endif

