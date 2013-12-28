#ifndef _SCANNER_H_
#define _SCANNER_H_

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int symbolic::scanner::yylex ()

#include <istream>
#include "parser.hpp"

namespace symbolic {

class scanner : public yyFlexLexer {
	int yylex ();
	parser::semantic_type * yylval;

public:
	scanner (std::istream * in)
		: yyFlexLexer (in), yylval (nullptr)
	{ }

	int yylex (parser::semantic_type * lval) {
		yylval = lval;
		return yylex ();
	}
};

}

#endif

