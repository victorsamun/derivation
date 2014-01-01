#include "symbolic_function.h"
#include "simplifyer.h"
#include "driver.h"

using namespace symbolic;

function::function () : f (std::make_shared <value> (0.0)) { }

function::function (const pfunction_impl & f) : f (f) { }

function function::parse (const std::string & s) {
	driver d;
	return d.parse (s);
}

function function::simplify () const {
	return function (constant_folder::simplify (f));
}

function function::var ()
	{ return function (std::make_shared <variable> ()); }

function function::num (double v)
	{ return function (std::make_shared <value> (v)); }

function function::derivative () const
	{ return function (f->derivative ()); }

double function::operator () (double x) const
	{ return f->val (x); }

function function::pow (double e) const
	{ return function (std::make_shared <pow_v> (f, e)); }

function function::pow (const function & g) const
	{ return function (std::make_shared <exp_f> (f, g.f)); }

function function::abs (const function & f)
	{ return function (std::make_shared <abs_f> (f.f)); }

function function::ln (const function & f)
	{ return function (std::make_shared <ln_f> (f.f)); }

function function::sin (const function & f)
	{ return function (std::make_shared <sin_f> (f.f)); }

function function::cos (const function & f)
	{ return function (std::make_shared <cos_f> (f.f)); }

function function::tg (const function & f)
	{ return function (std::make_shared <tg_f> (f.f)); }

function function::arcsin (const function & f)
	{ return function (std::make_shared <arcsin_f> (f.f)); }

function function::arccos (const function & f)
	{ return function (std::make_shared <arccos_f> (f.f)); }

function function::arctg (const function & f)
	{ return function (std::make_shared <arctg_f> (f.f)); }

function function::sh (const function & f)
	{ return function (std::make_shared <sh_f> (f.f)); }

function function::ch (const function & f)
	{ return function (std::make_shared <ch_f> (f.f)); }

function function::th (const function & f)
	{ return function (std::make_shared <th_f> (f.f)); }

function function::arsh (const function & f)
	{ return function (std::make_shared <arsh_f> (f.f)); }

function function::arch (const function & f)
	{ return function (std::make_shared <arch_f> (f.f)); }

function function::arth (const function & f)
	{ return function (std::make_shared <arth_f> (f.f)); }

function function::exp (double e, const function & f)
	{ return function (std::make_shared <exp_v> (e, f.f)); }

function & function::operator += (const function & rhs) {
	f = std::make_shared <plus> (f, rhs.f);
	return * this;
}

function & function::operator -= (const function & rhs) {
	f = std::make_shared <minus> (f, rhs.f);
	return * this;
}

function & function::operator *= (const function & rhs) {
	f = std::make_shared <mult> (f, rhs.f);
	return * this;
}

function & function::operator /= (const function & rhs) {
	f = std::make_shared <div> (f, rhs.f);
	return * this;
}

function symbolic::operator + (const function & lhs, const function & rhs)
	{ return function (lhs) += rhs; }

function symbolic::operator - (const function & lhs, const function & rhs)
	{ return function (lhs) -= rhs; }

function symbolic::operator * (const function & lhs, const function & rhs)
	{ return function (lhs) *= rhs; }

function symbolic::operator / (const function & lhs, const function & rhs)
	{ return function (lhs) /= rhs; }

function function::operator - () const
	{ return function (std::make_shared <uminus> (f)); }

std::ostream & symbolic::operator << (std::ostream & os, const function & f) {
	f.f->print (os);
	return os;
}

