#ifndef _BASE_FUNCTION_IMPL_H_
#define _BASE_FUNCTION_IMPL_H_

#include <memory>
#include <ostream>

namespace symbolic {

class function_impl {
public:
	virtual double val (double x) const = 0;
	virtual bool is_const () const = 0;
	virtual std::shared_ptr <function_impl> derivative () const = 0;
	virtual void print (std::ostream & os) const = 0;

	virtual ~function_impl ();
};

typedef std::shared_ptr <function_impl> pfunction_impl;

class variable : public function_impl {
public:
	virtual double val (double x) const;
	virtual bool is_const () const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~variable ();
};

class value : public function_impl {
	double v;

public:
	value (double v);

	virtual double val (double x) const;
	virtual bool is_const () const;
	virtual pfunction_impl derivative () const;
	virtual void print (std::ostream & os) const;

	virtual ~value ();
};

}

#endif

