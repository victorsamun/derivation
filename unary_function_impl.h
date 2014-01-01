#ifndef _UNARY_FUNCTION_IMPL_H_
#define _UNARY_FUNCTION_IMPL_H_

#include "base_function_impl.h"

namespace symbolic {

class unary_function : public function_impl {
protected:
	pfunction_impl arg;

	unary_function (const pfunction_impl & arg);

public:
	virtual bool is_const () const;
	const pfunction_impl & operand () const;

	virtual ~unary_function ();
};

class uminus : public unary_function {
public:
	uminus (const pfunction_impl & arg);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~uminus ();
};

class pow_v : public unary_function {
protected:
	double e;

public:
	pow_v (const pfunction_impl & arg, double e);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~pow_v ();
};

class exp_v : public unary_function {
protected:
	double e;

public:
	exp_v (double e, const pfunction_impl & arg);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~exp_v ();	
};

typedef double (* func_ptr) (double x);

template <typename T>
struct function_traits {
	static const char * const name;
	static func_ptr func;
};

template <typename traits>
class simple_function : public unary_function {
public:
	simple_function (const pfunction_impl & arg)
		: unary_function (arg) { }

	virtual double val (double x) const {
		return traits::func (x);
	}

	virtual pfunction_impl derivative () const;

	virtual void print (std::ostream & os) const {
		os << traits::name << '(';
		arg->print (os);
		os << ')';
	}

	virtual ~simple_function () { }
};

struct ln_op { };
struct abs_op { };

struct sin_op { };
struct cos_op { };
struct tg_op { };

struct arcsin_op { };
struct arccos_op { };
struct arctg_op { };

struct sh_op { };
struct ch_op { };
struct th_op { };

struct arsh_op { };
struct arch_op { };
struct arth_op { };

typedef simple_function <function_traits <ln_op>> ln_f;
typedef simple_function <function_traits <abs_op>> abs_f;

typedef simple_function <function_traits <sin_op>> sin_f;
typedef simple_function <function_traits <cos_op>> cos_f;
typedef simple_function <function_traits <tg_op>> tg_f;

typedef simple_function <function_traits <arcsin_op>> arcsin_f;
typedef simple_function <function_traits <arccos_op>> arccos_f;
typedef simple_function <function_traits <arctg_op>> arctg_f;

typedef simple_function <function_traits <sh_op>> sh_f;
typedef simple_function <function_traits <ch_op>> ch_f;
typedef simple_function <function_traits <th_op>> th_f;

typedef simple_function <function_traits <arsh_op>> arsh_f;
typedef simple_function <function_traits <arch_op>> arch_f;
typedef simple_function <function_traits <arth_op>> arth_f;
}

#endif

