#ifndef _SYMBOLIC_FUNCTION_H_
#define _SYMBOLIC_FUNCTION_H_

#include "function_impl.h"
#include <string>

namespace symbolic {

class function {
	pfunction_impl f;

	function (const pfunction_impl & f);

public:
	function ();

	static function parse (const std::string & s);

	static function var ();
	static function num (double v);

	function derivative () const;
	function simplify () const;

	double operator () (double x) const;

	function pow (double e) const;
	function pow (const function & g) const;

	static function abs (const function & f);
	static function ln (const function & f);
	static function exp (double e, const function & f);

	static function sin (const function & f);
	static function cos (const function & f);
	static function tg (const function & f);

	static function arcsin (const function & f);
	static function arccos (const function & f);
	static function arctg (const function & f);

	static function sh (const function & f);
	static function ch (const function & f);
	static function th (const function & f);

	static function arsh (const function & f);
	static function arch (const function & f);
	static function arth (const function & f);

	function & operator += (const function & rhs);
	function & operator -= (const function & rhs);
	function & operator *= (const function & rhs);
	function & operator /= (const function & rhs);

	function operator - () const;

	friend std::ostream & operator << (std::ostream & os, const function & f);
};

function operator + (const function & lhs, const function & rhs);
function operator - (const function & lhs, const function & rhs);
function operator * (const function & lhs, const function & rhs);
function operator / (const function & lhs, const function & rhs);

std::ostream & operator << (std::ostream & os, const function & f);

}

#endif

