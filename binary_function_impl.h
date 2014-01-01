#ifndef _BINARY_FUNCTION_IMPL_H_
#define _BINARY_FUNCTION_IMPL_H_

#include "base_function_impl.h"

namespace symbolic {

class binary_function : public function_impl {
protected:
	pfunction_impl lhs;
	pfunction_impl rhs;

	binary_function (const pfunction_impl & lhs, const pfunction_impl & rhs);

public:
	virtual bool is_const () const;
	const pfunction_impl & left () const;
	const pfunction_impl & right () const;

	virtual ~binary_function ();
};

class exp_f : public binary_function {
public:
	exp_f (const pfunction_impl & lhs, const pfunction_impl & rhs);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~exp_f ();
};

class plus : public binary_function {
public:
	plus (const pfunction_impl & lhs, const pfunction_impl & rhs);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~plus ();
};

class minus : public binary_function {
public:
	minus (const pfunction_impl & lhs, const pfunction_impl & rhs);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~minus ();
};

class mult : public binary_function {
public:
	mult (const pfunction_impl & lhs, const pfunction_impl & rhs);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~mult ();
};

class div : public binary_function {
public:
	div (const pfunction_impl & lhs, const pfunction_impl & rhs);

	virtual double val (double x) const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~div ();
};

}

#endif

