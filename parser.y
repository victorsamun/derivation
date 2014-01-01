%skeleton "lalr1.cc"
%require "2.5"
%defines
%define namespace "symbolic"
%define parser_class_name "parser"

%code requires {
	#include "symbolic_function.h"

	namespace symbolic {
		class driver;
		class scanner;
	}
}

%lex-param { scanner & s }
%parse-param { scanner & s }

%lex-param { driver & d }
%parse-param { driver & d }

%code {
	#include <iostream>
	#include <string>
	#include "driver.h"

	static int yylex (
		symbolic::parser::semantic_type * yylval,
		symbolic::scanner & s,
		symbolic::driver & d
	);
}

%union {
	function * val;
	double dval;
}

%token END 0 "end of string"
%token LP RP HP
%token PLUS MINUS MULT DIV POW
%token ABS LN EXP
%token SIN COS TAN ASIN ACOS ATAN
%token SH CH TH ARSH ARCH ARTH
%token X
%token <dval> NUMBER

%type <val> expression expr

%destructor { delete $$; } <val>

%%

expression
	:	expr
		{ d.set (* ($$ = $1)); }
	;

%left PLUS MINUS;
%left MULT DIV;
%right POW;

expr
	:	expr PLUS expr
		{ $$ = new function ((* $1) + (* $3)); }
	|	expr MINUS expr
		{ $$ = new function ((* $1) - (* $3)); }
	|	expr MULT expr
		{ $$ = new function ((* $1) * (* $3)); }
	|	expr DIV expr
		{ $$ = new function ((* $1) / (* $3)); }
	| 	expr POW expr
		{ $$ = new function ($1->pow (* $3)); }
	|	MINUS expr
		{ $$ = new function (- * $2); }
	|	LP expr RP
		{ $$ = new function (* $2); }
	|	HP expr HP
		{ $$ = new function (function::abs (* $2)); }
	|	ABS LP expr RP
		{ $$ = new function (function::abs (* $3)); }
	|	LN LP expr RP
		{ $$ = new function (function::ln (* $3)); }
	|	EXP LP expr RP
		{ $$ = new function (function::exp (2.718281828459045, * $3)); }
	|	SIN LP expr RP
		{ $$ = new function (function::sin (* $3)); }
	|	COS LP expr RP
		{ $$ = new function (function::cos (* $3)); }
	|	TAN LP expr RP
		{ $$ = new function (function::tg (* $3)); }
	|	ASIN LP expr RP
		{ $$ = new function (function::arcsin (* $3)); }
	|	ACOS LP expr RP
		{ $$ = new function (function::arccos (* $3)); }
	|	ATAN LP expr RP
		{ $$ = new function (function::arctg (* $3)); }
	|	SH LP expr RP
		{ $$ = new function (function::sh (* $3)); }
	|	CH LP expr RP
		{ $$ = new function (function::ch (* $3)); }
	|	TH LP expr RP
		{ $$ = new function (function::th (* $3)); }
	|	ARSH LP expr RP
		{ $$ = new function (function::arsh (* $3)); }
	|	ARCH LP expr RP
		{ $$ = new function (function::arch (* $3)); }
	|	ARTH LP expr RP
		{ $$ = new function (function::arth (* $3)); }
	|	NUMBER
		{ $$ = new function (function::num ($1)); }
	|	X
		{ $$ = new function (function::var ()); }
	;

%%

void symbolic::parser::error (const symbolic::location & l, const std::string & msg) {
	throw symbolic::parse_error (msg);
}

#include "scanner.h"

static int yylex (
	symbolic::parser::semantic_type * yylval,
	symbolic::scanner & s,
	symbolic::driver & d) {
	return s.yylex (yylval);
}

