#ifndef _SYMBOLIC_FUNCTION_H_
#define _SYMBOLIC_FUNCTION_H_

#include "function_impl.h"

namespace symbolic {

class function {
	pfunction_impl f;

	function ();
	function (const pfunction_impl & f);

public:
	static function var ();
	static function num (double v);

	function derivative () const;

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

