#include "parse_error.h"

using namespace symbolic;

parse_error::parse_error (const std::string & s)
	: s (s) { }

std::string parse_error::what () const {
	return s;
}

