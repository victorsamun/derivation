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

const pfunction_impl & unary_function::operand () const {
	return arg;
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
		std::make_shared <ln_f> (std::make_shared <value> (e)),
		std::make_shared <mult> (
			std::make_shared <exp_v> (e, arg),
			arg->derivative ()
		)
	);
}

void exp_v::print (std::ostream & os) const {
	if (e < 0.0)
		os << '(' << e << ')';
	else
		os << e;
	os << "^(";
	arg->print (os);
	os << ')';
}

exp_v::~exp_v () { }


/* simple_function */

template <> const char * const function_traits <ln_op>::name = "ln";
template <> const char * const function_traits <abs_op>::name = "abs";
template <> const char * const function_traits <sin_op>::name = "sin";
template <> const char * const function_traits <cos_op>::name = "cos";
template <> const char * const function_traits <tg_op>::name = "tg";
template <> const char * const function_traits <arcsin_op>::name = "arcsin";
template <> const char * const function_traits <arccos_op>::name = "arccos";
template <> const char * const function_traits <arctg_op>::name = "arctg";
template <> const char * const function_traits <sh_op>::name = "sh";
template <> const char * const function_traits <ch_op>::name = "ch";
template <> const char * const function_traits <th_op>::name = "th";
template <> const char * const function_traits <arsh_op>::name = "arsh";
template <> const char * const function_traits <arch_op>::name = "arch";
template <> const char * const function_traits <arth_op>::name = "arth";

template <> func_ptr function_traits <ln_op>::func = std::log;
template <> func_ptr function_traits <abs_op>::func = std::abs;
template <> func_ptr function_traits <sin_op>::func = std::sin;
template <> func_ptr function_traits <cos_op>::func = std::cos;
template <> func_ptr function_traits <tg_op>::func = std::tan;
template <> func_ptr function_traits <arcsin_op>::func = std::asin;
template <> func_ptr function_traits <arccos_op>::func = std::acos;
template <> func_ptr function_traits <arctg_op>::func = std::atan;
template <> func_ptr function_traits <sh_op>::func = std::sinh;
template <> func_ptr function_traits <ch_op>::func = std::cosh;
template <> func_ptr function_traits <th_op>::func = std::tanh;
template <> func_ptr function_traits <arsh_op>::func = std::asinh;
template <> func_ptr function_traits <arch_op>::func = std::acosh;
template <> func_ptr function_traits <arth_op>::func = std::atanh;

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

	return std::make_shared <mult> (arg->derivative (), std::make_shared <cos_f> (arg));
}

template <>
pfunction_impl cos_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (
		arg->derivative (),
		std::make_shared <uminus> (std::make_shared <sin_f> (arg))
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
		arg->derivative (),
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
		arg->derivative (),
		std::make_shared <plus> (
			std::make_shared <pow_v> (arg, 2.0),
			std::make_shared <value> (1.0)
		)
	);
}

template <>
pfunction_impl sh_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (arg->derivative (), std::make_shared <ch_f> (arg));
}

template <>
pfunction_impl ch_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <mult> (arg->derivative (), std::make_shared <sh_f> (arg));
}

template <>
pfunction_impl th_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		arg->derivative (),
		std::make_shared <pow_v> (std::make_shared <ch_f> (arg), 2.0)
	);
}

template <>
pfunction_impl arsh_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		arg->derivative (),
		std::make_shared <pow_v> (
			std::make_shared <plus> (
				std::make_shared <pow_v> (arg, 2.0),
				std::make_shared <value> (1.0)
			), 0.5
		)
	);
}

template <>
pfunction_impl arch_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		arg->derivative (),
		std::make_shared <pow_v> (
			std::make_shared <minus> (
				std::make_shared <pow_v> (arg, 2.0),
				std::make_shared <value> (1.0)
			), 0.5
		)
	);
}

template <>
pfunction_impl arth_f::derivative () const {
	if (arg->is_const ())
		return std::make_shared <value> (0.0);

	return std::make_shared <div> (
		arg->derivative (),
		std::make_shared <minus> (
			std::make_shared <value> (1.0),
			std::make_shared <pow_v> (arg, 2.0)
		)
	);
}

}

