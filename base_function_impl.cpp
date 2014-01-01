#include "base_function_impl.h"

using namespace symbolic;

/* Base class */

function_impl::~function_impl () { }


/* Variable */

double variable::val (double x) const {
	return x;
}

bool variable::is_const () const {
	return false;
}

pfunction_impl variable::derivative () const {
	return std::make_shared <value> (1.0);
}

void variable::print (std::ostream & os) const {
	os << "x";
}

variable::~variable () { }


/* Value */

value::value (double v) : v (v) { }

double value::val (double x) const {
	return v;
}

bool value::is_const () const {
	return true;
}

pfunction_impl value::derivative () const {
	return std::make_shared <value> (0.0);
}

void value::print (std::ostream & os) const {
	if (v < 0.0)
		os << '(' << v << ')';
	else
		os << v;
}

value::~value () { }

