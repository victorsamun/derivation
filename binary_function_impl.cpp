#include "binary_function_impl.h"
#include "unary_function_impl.h"
#include <cmath>

using namespace symbolic;

/* Binary function */

binary_function::binary_function (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: lhs (lhs), rhs (rhs) { }

bool binary_function::is_const () const {
	return lhs->is_const () && rhs->is_const ();
}

binary_function::~binary_function () { }


/* Exp_f */

exp_f::exp_f (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: binary_function (lhs, rhs) { }

double exp_f::val (double x) const {
	return std::pow (lhs->val (x), rhs->val (x));
}

pfunction_impl exp_f::derivative () const {
	if (is_const ())
		return std::make_shared <value> (0.0);

	if (lhs->is_const ())
		return (std::make_shared <exp_v> (lhs->val (0), rhs))->derivative ();

	if (rhs->is_const ())
		return (std::make_shared <pow_v> (lhs, rhs->val (0)))->derivative ();

	return std::make_shared <mult> (
		std::make_shared <exp_f> (lhs, rhs),
		(std::make_shared <mult> (std::make_shared <ln_f> (lhs), rhs))->derivative ()
	);
}

void exp_f::print (std::ostream & os) const {
	os << '(';
	lhs->print (os);
	os << ")^(";
	rhs->print (os);
	os << ')';
}

exp_f::~exp_f () { }


/* Plus */

plus::plus (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: binary_function (lhs, rhs) { }

double plus::val (double x) const {
	return lhs->val (x) + rhs->val (x);
}

pfunction_impl plus::derivative () const {
	if (is_const ())
		return std::make_shared <value> (0.0);

	if (lhs->is_const ())
		return rhs->derivative ();

	if (rhs->is_const ())
		return lhs->derivative ();

	return std::make_shared <plus> (lhs->derivative (), rhs->derivative ());
}

void plus::print (std::ostream & os) const {
	os << '(';
	lhs->print (os);
	os << ")+(";
	rhs->print (os);
	os << ')';
}

plus::~plus () { }


/* Minus */

minus::minus (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: binary_function (lhs, rhs) { }

double minus::val (double x) const {
	return lhs->val (x) - rhs->val (x);
}

pfunction_impl minus::derivative () const {
	if (is_const ())
		return std::make_shared <value> (0.0);

	if (lhs->is_const ())
		return std::make_shared <uminus> (rhs->derivative ());

	if (rhs->is_const ())
		return lhs->derivative ();

	return std::make_shared <minus> (lhs->derivative (), rhs->derivative ());
}

void minus::print (std::ostream & os) const {
	os << '(';
	lhs->print (os);
	os << ")-(";
	rhs->print (os);
	os << ')';
}

minus::~minus () { }


/* Mult */

mult::mult (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: binary_function (lhs, rhs) { }

double mult::val (double x) const {
	return lhs->val (x) * rhs->val (x);
}

pfunction_impl mult::derivative () const {
	if (is_const ())
		return std::make_shared <value> (0.0);

	if (lhs->is_const ())
		return std::make_shared <mult> (lhs, rhs->derivative ());

	if (rhs->is_const ())
		return std::make_shared <mult> (rhs, lhs->derivative ());

	return std::make_shared <plus> (
		std::make_shared <mult> (lhs, rhs->derivative ()),
		std::make_shared <mult> (rhs, lhs->derivative ())
	);
}

void mult::print (std::ostream & os) const {
	lhs->print (os);
	os << '*';
	rhs->print (os);
}

mult::~mult () { }


/* Div */

div::div (const pfunction_impl & lhs, const pfunction_impl & rhs)
	: binary_function (lhs, rhs) { }

double div::val (double x) const {
	return lhs->val (x) / rhs->val (x);
}

pfunction_impl div::derivative () const {
	if (is_const ())
		return std::make_shared <value> (0.0);

	if (lhs->is_const ())
		return std::make_shared <uminus> (
			std::make_shared <div> (
				rhs->derivative (), std::make_shared <pow_v> (rhs, 2.0)
			)
		);

	if (rhs->is_const ())
		return std::make_shared <div> (lhs->derivative (), rhs);

	return std::make_shared <div> (
		std::make_shared <minus> (
			std::make_shared <mult> (lhs->derivative (), rhs),
			std::make_shared <mult> (lhs, rhs->derivative ())
		),
		std::make_shared <pow_v> (rhs, 2.0)
	);
}

void div::print (std::ostream & os) const {
	os << '(';
	lhs->print (os);
	os << ")/(";
	rhs->print (os);
	os << ')';
}

div::~div () { }

