#include "driver.h"
#include <sstream>

using namespace symbolic;

driver::driver ()
	: m_parser (nullptr), m_scanner (nullptr) { }

void driver::parse (const std::string & str) throw (parse_error) {
	std::istringstream is (str);

	delete m_scanner;
	m_scanner = new scanner (& is);

	delete m_parser;
	m_parser = new parser (* m_scanner, * this);

	m_parser->parse ();
}

void driver::set (const function & f) {
	m_value = f;
}

function driver::get () const {
	return m_value;
}

driver::~driver () {
	delete m_scanner;
	delete m_parser;
}

