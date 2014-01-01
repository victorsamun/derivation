#ifndef _SIMPLIFYER_H_
#define _SIMPLIFYER_H_

#include "function_impl.h"

namespace symbolic {

class constant_folder {
	static pfunction_impl simplify (exp_f * f);
	static pfunction_impl simplify (plus * f);
	static pfunction_impl simplify (minus * f);
	static pfunction_impl simplify (mult * f);
	static pfunction_impl simplify (div * f);

public:
	static pfunction_impl simplify (const pfunction_impl & f);
};

}

#endif

