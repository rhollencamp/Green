%option C++ noyywrap yyclass="Scanner" nodefault never-interactive

%{
	#include "Scanner.h"
	#include "Tokens.h"
%}

string   \"[^\n"]+\"

ws       [ \t]+

alpha    [A-Za-z]
dig      [0-9]
name     ({alpha}|{dig}|\$)({alpha}|{dig}|\_|\.|\-|\/|\$)*
num1     [-+]?{dig}+\.?([eE][-+]?{dig}+)?
num2     [-+]?{dig}*\.{dig}+([eE][-+]?{dig}+)?
number   {num1}|{num2}

%%

{ws} /* skip blanks and tabs */

 /* C Style Block Comments */
"/*" {
	int c;

	while((c = yyinput()) != 0) {
		if(c == '\n') {
			++yylineno;
		} else if(c == '*') {
			if((c = yyinput()) == '/') {
				break;
			} else {
				unput(c);
			}
		}
	}
}

 /* Keywords */
var           return Green::KEYWORD_VAR;
package       return Green::KEYWORD_PACKAGE;
import        return Green::KEYWORD_IMPORT;
class         return Green::KEYWORD_CLASS;
public        return Green::KEYWORD_PUBLIC;
private       return Green::KEYWORD_PRIVATE;
function      return Green::KEYWORD_FUNCTION;
static        return Green::KEYWORD_STATIC;
echo          return Green::KEYWORD_ECHO;

 /* Symbols */
";"           return Green::SYM_SEMICOLON;
"{"           return Green::SYM_CURLY_OPEN;
"}"           return Green::SYM_CURLY_CLOSE;
"="           return Green::SYM_ASSIGNMENT;
"+"           return Green::SYM_PLUS;
"("           return Green::SYM_PAREN_OPEN;
")"           return Green::SYM_PAREN_CLOSE;
","           return Green::SYM_COMMA;
"-"           return Green::SYM_MINUS;
"*"           return Green::SYM_MULTIPLY;
"/"           return Green::SYM_DIVIDE;
"%"           return Green::SYM_MODULUS;
"."           return Green::SYM_PERIOD;
"::"          return Green::SYM_SCOPE_RESOLUTION;

 /* Constants */
{dig}+        return Green::CONSTANT_INT;

 /* Varaibles / Identifiers */
\${alpha}+[a-zA-Z0-9_]*		return Green::VARIABLE;
{alpha}+[a-zA-Z0-9_]*		return Green::IDENTIFIER;

 /* Keep track of what line we are on */
\n		yylineno++;


.		/* TODO */
