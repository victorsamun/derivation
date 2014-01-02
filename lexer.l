%{
	#include <cstdlib>
	#include <cmath>
	#include "parse_error.h"
	#include "scanner.h"

	typedef symbolic::parser::token token;

	#define yyterminate() return token::END
	#define YY_NO_UNISTD_H
%}

%option debug
%option yyclass="scanner"
%option noyywrap
%option c++

num	[0-9]
hnum	[0-9a-fA-F]
nchar	[a-zA-Z_0-9]
ws	[ \t]
nl	[\r\n]

%%

"+"	return token::PLUS;
"-"	return token::MINUS;
"*"	return token::MULT;
"/"	return token::DIV;
"^"	return token::POW;

"("	return token::LP;
")"	return token::RP;
"|"	return token::HP;

"abs"	return token::ABS;

"ln"	return token::LN;
"exp"	return token::EXP;

"sin"	return token::SIN;
"cos"	return token::COS;
"tg"	return token::TAN;

"asin"	return token::ASIN;
"acos"	return token::ACOS;
"atg"	return token::ATAN;

"sh"	return token::SH;
"ch"	return token::CH;
"th"	return token::TH;

"arsh"	return token::ARSH;
"arch"	return token::ARCH;
"arth"	return token::ARTH;

"x"	return token::X;

"Pi"	{
	yylval->dval = M_PI;
	return token::NUMBER;
}

(?:(?:{num}+|{num}*\.{num}+)(?:[eE][+-]?{num}+)?|0[xX](?:{hnum}+|{hnum}*\.{hnum}+)(?:[pP][+-]?{num}+)?|(?i:INFINITY|INF)|NAN(?:\({nchar}+\))?) {
	yylval->dval = std::atof (yytext);
	return token::NUMBER;
}

({nl}|{ws})+	/* ignore */
.	{
	throw symbolic::parse_error ("invalid character");
}

%%

