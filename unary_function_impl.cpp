#include "unary_function_impl.h"
#include "binary_function_impl.h"
#include <cmath>

using namespace symbolic;

/* Unary function */

unary_function::unary_function (const pfunction_impl & arg)
	: arg (arg) { }

bool unary_function::is_const () const {
	return arg->is_const ();
}

unary_function::~unary_function () { }


/* Uminus */

uminus::uminus (const pfunction_impl & arg)
	: unary_function (arg) { }

double uminus::val (double x) const {
	return - arg->val (x);
}

pfunction_impl uminus::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <uminus> (arg->derivative ());
}

void uminus::print (std::ostream & os) const {
	os << "-(";
	arg->print (os);
	os << ")";
}

uminus::~uminus () { }


/* Pow_v */

pow_v::pow_v (const pfunction_impl & arg, double e)
	: unary_function (arg), e (e) { }

double pow_v::val (double x) const {
	return std::pow (arg->val (x), e);
}

pfunction_impl pow_v::derivative () const {
	if (std::abs (e) < 1e-10)
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (
		std::make_shared <value> (e),
		std::make_shared <mult> (
			std::make_shared <pow_v> (arg, e - 1.0),
			arg->derivative ()
		)
	);
}

void pow_v::print (std::ostream & os) const {
	os << '(';
	arg->print (os);
	os << ")^" << e;
}

pow_v::~pow_v () { }


/* Exp_v */

exp_v::exp_v (double e, const pfunction_impl & arg)
	: unary_function (arg), e (e) { }

double exp_v::val (double x) const {
	return std::pow (e, arg->val (x));
}

pfunction_impl exp_v::derivative () const {
	return std::make_shared <mult> (
		std::make_shared <value> (std::log (e)),
		std::make_shared <mult> (
			std::make_shared <exp_v> (e, arg),
			arg->derivative ()
		)
	);
}

void exp_v::print (std::ostream & os) const {
	os << e << "^(";
	arg->print (os);
	os << ')';
}

exp_v::~exp_v () { }


/* simple_function */

template <> const char * const FunctionTraits <ln_op>::name = "ln";
template <> const char * const FunctionTraits <abs_op>::name = "abs";
template <> const char * const FunctionTraits <sin_op>::name = "sin";
template <> const char * const FunctionTraits <cos_op>::name = "cos";
template <> const char * const FunctionTraits <tg_op>::name = "tg";
template <> const char * const FunctionTraits <arcsin_op>::name = "arcsin";
template <> const char * const FunctionTraits <arccos_op>::name = "arccos";
template <> const char * const FunctionTraits <arctg_op>::name = "arctg";


template <> func_ptr FunctionTraits <ln_op>::func = std::log;
template <> func_ptr FunctionTraits <abs_op>::func = std::abs;
template <> func_ptr FunctionTraits <sin_op>::func = std::sin;
template <> func_ptr FunctionTraits <cos_op>::func = std::cos;
template <> func_ptr FunctionTraits <tg_op>::func = std::tan;
template <> func_ptr FunctionTraits <arcsin_op>::func = std::asin;
template <> func_ptr FunctionTraits <arccos_op>::func = std::acos;
template <> func_ptr FunctionTraits <arctg_op>::func = std::atan;

namespace symbolic {

template <>
pfunction_impl ln_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (arg->derivative (), arg);
}

template <>
pfunction_impl abs_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (
		std::make_shared <div> (arg, std::make_shared <abs_f> (arg)),
		arg->derivative ()
	);
}

template <>
pfunction_impl sin_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (
		std::make_shared <cos_f> (arg),
		arg->derivative ()
	);
}

template <>
pfunction_impl cos_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (
		std::make_shared <uminus> (std::make_shared <sin_f> (arg)),
		arg->derivative ()
	);
}

template <>
pfunction_impl tg_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		arg->derivative (),
		std::make_shared <pow_v> (std::make_shared <cos_f> (arg), 2.0)
	);
}

template <>
pfunction_impl arcsin_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		std::make_shared <value> (1.0),
		std::make_shared <pow_v> (
			std::make_shared <minus> (
				std::make_shared <value> (1.0),
				std::make_shared <pow_v> (arg, 2.0)
			), 0.5
		)
	);
}

template <>
pfunction_impl arccos_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <uminus> ((std::make_shared <arcsin_f> (arg))->derivative ());
}

template <>
pfunction_impl arctg_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		std::make_shared <value> (1.0),
		std::make_shared <plus> (
			std::make_shared <pow_v> (arg, 2.0),
			std::make_shared <value> (1.0)
		)
	);
}

}

