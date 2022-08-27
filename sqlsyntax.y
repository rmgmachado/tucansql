%code {
/*****************************************************************************\
*  Copyright (c) 2022 Tucan Software Pty Ltd. All rights reserved.
*
*  MIT License
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to 
*  deal in the Software without restriction, including without limitation the 
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
*  sell copies of the Software, and to permit persons to whom the Software is 
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in 
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
*  IN THE SOFTWARE.
*
*  You should have received a copy of the MIT License along with this program.
*  If not, see https://opensource.org/licenses/MIT.
\*****************************************************************************/

/*****************************************************************************\
* 
*   Generate kmipparse.cpp file with the following bison statement:
*
*   bison -d --no-lines -o sqlsyntax.cpp -p sql_ sqlsyntax.y 
*
\*****************************************************************************/
}

%define api.pure
%parse-param {void* handle}
%lex-param {void* handle}
%start sql_commands
%verbose 

%code top {

#include "value.h"
#include "scanner.h"
#include "ptree.h"

using namespace tucan;
}


/* value type of Yacc structures and rules */
%union {
   ptree_t* ytree;
   token_t* ytoken;
}

%code {
int sql_lex(YYSTYPE *lvalp, void* handle);
void sql_error(void* handle, const char* s);
}

/*****************************************************************************\
*	Reserved words
\*****************************************************************************/
%token	<ytoken>	BOOLEAN_ INTEGER DECIMAL DATETIME TEXT BINARY  
%token	<ytoken>	CREATE DROP TABLE INSERT INTO VALUES
%token	<ytoken>	UPDATE SET WHERE SELECT FROM
%token	<ytoken>	NOT NULL_ OR AND AS IS

/*****************************************************************************\
*	Identifiers
\*****************************************************************************/
%token	<ytoken> IDENTIFIER NAME

/*****************************************************************************\
*	Literals
\*****************************************************************************/
%token	<ytoken>	BOOLEAN_LITERAL INTEGER_LITERAL DECIMAL_LITERAL 
%token	<ytoken> DATETIME_LITERAL TEXT_LITERAL BINARY_LITERAL  

/*****************************************************************************\
*	Relational operators
*	NE '<>' LE '<=' GE '>='
\*****************************************************************************/
%token	<ytoken>	NE LE GE 

/*****************************************************************************\
*	Production types
\*****************************************************************************/
%type		<ytree>	sql_commands sql_command 
%type		<ytree>	sql_column_definition_list sql_column_definition 
%type		<ytree>	sql_column_def_type sql_column_def_null_opt
%type		<ytree>	sql_column_pair_list sql_column_pair 
%type		<ytree>	sql_where_clause_opt sql_where_clause
%type		<ytree>	sql_column_name_list sql_expression_list sql_expression 
%type		<ytree>	sql_or_expression sql_and_expression sql_relational_expression
%type		<ytree>	sql_add_expression sql_mult_expression sql_unary_expression 
%type		<ytree>	sql_primary_expression sql_literal sql_identifier
%type		<ytree>	sql_select_expression_list sql_select_expression sql_select_as_opt

/*****************************************************************************\
*	Precedence rules
\*****************************************************************************/
%left '+' '-'
%left '*' '/'
%left SQL_UMINUS


/*****************************************************************************\
*	SQL Syntax definitions
\*****************************************************************************/
%%

sql_commands
	: sql_command
	| sql_commands ';' sql_command
	;
	
sql_command
	: CREATE TABLE IDENTIFIER '(' sql_column_definition_list ')'
	| INSERT INTO IDENTIFIER '(' sql_column_name_list ')' VALUES '(' sql_expression_list ')'
	| UPDATE IDENTIFIER SET sql_column_pair_list sql_where_clause_opt
	| SELECT sql_select_expression_list FROM IDENTIFIER sql_where_clause_opt 
	| DROP TABLE IDENTIFIER
	;
	
sql_select_expression_list
	: sql_select_expression
	| sql_select_expression_list ',' sql_select_expression
	;

sql_select_expression
	: '*'
	| sql_expression sql_select_as_opt
	;
	
sql_select_as_opt
	: 
	| AS IDENTIFIER
	| AS NAME
	;
	
sql_column_definition_list
	: sql_column_definition
	| sql_column_definition_list ',' sql_column_definition
	;
	
sql_column_definition
	:  IDENTIFIER sql_column_def_type sql_column_def_null_opt
	;
	
sql_column_def_type
	: BOOLEAN_
	| INTEGER
	| DECIMAL
	| DATETIME
	| TEXT
	| BINARY
	;
	
sql_column_def_null_opt
	:
	| NULL_
	| NOT NULL_
	;
	
sql_column_name_list
	: IDENTIFIER
	| sql_column_name_list ',' IDENTIFIER
	;
	
sql_column_pair_list 
	: sql_column_pair
	| sql_column_pair_list ',' sql_column_pair
	;
	
sql_column_pair
	: IDENTIFIER '=' sql_expression
	;

sql_where_clause_opt
	:
	| sql_where_clause
	;
	
sql_where_clause
	: WHERE sql_expression
	;
	
sql_expression_list
	: sql_expression
	| sql_expression_list ',' sql_expression
	;
	
sql_expression
	: sql_or_expression
	;
	
sql_or_expression
	: sql_and_expression
	| sql_or_expression OR sql_and_expression
	;
	
sql_and_expression
	: sql_relational_expression
	| sql_relational_expression AND sql_relational_expression
	;
	
sql_relational_expression
	: sql_add_expression
	| sql_relational_expression '=' sql_add_expression
	| sql_relational_expression NE sql_add_expression
	| sql_relational_expression '<' sql_add_expression
	| sql_relational_expression LE sql_add_expression
	| sql_relational_expression '>' sql_add_expression
	| sql_relational_expression GE sql_add_expression
	| sql_relational_expression IS NULL_
	| sql_relational_expression IS NOT NULL_
	;

sql_add_expression
	: sql_mult_expression
	| sql_add_expression '+' sql_mult_expression
	| sql_add_expression '-' sql_mult_expression
	;		
	
sql_mult_expression
	: sql_unary_expression
	| sql_mult_expression '*' sql_unary_expression
	| sql_mult_expression '/' sql_unary_expression
	;
	
sql_unary_expression
	: sql_primary_expression
	| '+' sql_primary_expression %prec SQL_UMINUS
	| '-' sql_primary_expression %prec SQL_UMINUS
	| NOT sql_primary_expression
	;
	
sql_primary_expression
	: sql_literal
	| sql_identifier
	| '(' sql_expression ')'
	;
	
sql_literal
	: BOOLEAN_LITERAL 
	| INTEGER_LITERAL 
	| DECIMAL_LITERAL  
	| DATETIME_LITERAL 
	| TEXT_LITERAL 
	| BINARY_LITERAL  
	| NULL_
	;
	
sql_identifier
	: IDENTIFIER
	| IDENTIFIER '.' IDENTIFIER
	;
	
%%
/*****************************************************************************\
*	Supporting parser code
\*****************************************************************************/

int sql_lex(YYSTYPE *lvalp, void* handle) 
{
	return 0;
}

void sql_error(void* handle, const char* s) 
{
}

void sql_set_error(void* handle, const char* s, int code)
{
}

int sql_parser(const char* stmt)
{
	return yyparse ((void*)stmt);
}