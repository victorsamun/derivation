#include "simplifyer.h"
#include <stdexcept>
#include <cmath>

using namespace symbolic;

const double eps = 1e-10;

inline bool eq (double a, double b) {
	return std::abs (a - b) < eps;
}

pfunction_impl constant_folder::simplify (exp_f * f) {
	pfunction_impl l = simplify (f->left ());
	pfunction_impl r = simplify (f->right ());

	if (l->is_const ()) {
		double v = l->val (0.0);

		if (eq (v, 0.0))
			return std::make_shared <value> (0.0);

		if (eq (v, 1.0))
			return std::make_shared <value> (1.0);
	}

	if (r->is_const ()) {
		double v = r->val (0.0);

		if (eq (v, 0.0))
			return std::make_shared <value> (1.0);

		if (eq (v, -1.0))
			return std::make_shared <div> (std::make_shared <value> (1.0), l);

		if (eq (v, 1.0))
			return l;

	}

	return std::make_shared <exp_f> (l, r);
}

pfunction_impl constant_folder::simplify (plus * f) {
	pfunction_impl l = simplify (f->left ());
	pfunction_impl r = simplify (f->right ());

	if (l->is_const () && eq (l->val (0.0), 0.0))
		return r;

	if (r->is_const () && eq (r->val (0.0), 0.0))
		return l;

	return std::make_shared <plus> (l, r);
}

pfunction_impl constant_folder::simplify (minus * f) {
	pfunction_impl l = simplify (f->left ());
	pfunction_impl r = simplify (f->right ());

	if (l->is_const () && eq (l->val (0.0), 0.0))
		return std::make_shared <uminus> (r);

	if (r->is_const () && eq (r->val (0.0), 0.0))
		return l;

	return std::make_shared <minus> (l, r);
}

pfunction_impl constant_folder::simplify (mult * f) {
	pfunction_impl l = simplify (f->left ());
	pfunction_impl r = simplify (f->right ());

	if (l->is_const ()) {
		double v = l->val (0.0);

		if (eq (v, 0.0))
			return std::make_shared <value> (0.0);

		if (eq (v, -1.0))
			return std::make_shared <uminus> (r);

		if (eq (v, 1.0))
			return r;
	}

	if (r->is_const ()) {
		double v = r->val (0.0);

		if (eq (v, 0.0))
			return std::make_shared <value> (0.0);

		if (eq (v, -1.0))
			return std::make_shared <uminus> (l);

		if (eq (v, 1.0))
			return l;
	}

	return std::make_shared <mult> (l, r);
}

pfunction_impl constant_folder::simplify (div * f) {
	pfunction_impl l = simplify (f->left ());
	pfunction_impl r = simplify (f->right ());

	if (l->is_const () && eq (l->val (0.0), 0.0))
		return std::make_shared <value> (0.0);

	if (r->is_const ()) {
		double v = r->val (0.0);

		if (eq (v, -1.0))
			return std::make_shared <uminus> (l);

		if (eq (v, 1.0))
			return l;
	}

	return std::make_shared <div> (l, r);
}

pfunction_impl constant_folder::simplify (const pfunction_impl & f) {
	if (f->is_const ())
		return std::make_shared <value> (f->val (0.0));

	if (binary_function * func = dynamic_cast <binary_function *> (f.get ())) {
		if (exp_f * _f = dynamic_cast <exp_f *> (func))
			return simplify (_f);
		else if (plus * _f = dynamic_cast <plus *> (func))
			return simplify (_f);
		else if (minus * _f = dynamic_cast <minus *> (func))
			return simplify (_f);
		else if (mult * _f = dynamic_cast <mult *> (func))
			return simplify (_f);
		else if (div * _f = dynamic_cast <div *> (func))
			return simplify (_f);
	}

	return f;
}

