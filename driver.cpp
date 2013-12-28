#include "driver.h"
#include <sstream>

using namespace symbolic;

void driver::parse (const std::string & str) {
	std::istringstream is (str);

	delete s;
	s = new scanner (& is);

	delete p;
	p = new parser (* s, * this);

	p->parse ();
}

void driver::set (const function & f) {
	v = f;
}

function driver::get () const {
	return v;
}

driver::~driver () {
	delete s;
	delete p;
}

